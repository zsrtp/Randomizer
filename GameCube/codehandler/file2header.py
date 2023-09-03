#!/usr/bin/env python3
__copyright__ = """
Licenced under MIT license.

Authors:
- kipcode66 2023
"""

import argparse
import sys
import os
import re


def main(argv=sys.argv):
    name_pattern = re.compile(r"[a-zA-Z0-9_]", re.I)
    entry_per_line_pattern = re.compile(r"[0-9]+", re.I)

    def var_name_type(s: str):
        if not name_pattern.match(s):
            raise argparse.ArgumentTypeError(
                f"Invalid variable name (\"{s}\")")
        return s

    def entry_per_line_type(s: str):
        if not entry_per_line_pattern.match(s):
            raise argparse.ArgumentTypeError(
                f"Expected positive base 10 integer (got \"{s}\")")
        return int(s, 10)

    parser = argparse.ArgumentParser(
        description="Converts any file into a c/c++ statically defined array in a header file.")
    parser.add_argument("file", help="File to convert",
                        type=argparse.FileType("rb"))
    parser.add_argument("-n", "--name", help="Provides a custom name for the variable containing the file's data",
                        type=var_name_type, default="data")
    parser.add_argument(
        "-N", "--size-name", help="Provide a custom name for the variable containing the size of the data", type=var_name_type)
    parser.add_argument("-c", "--count", help="Number of bytes per line. Set to 0 to have all bytes in one line. (default: 16)",
                        type=entry_per_line_type, default=16)
    parser.add_argument(
        "-t", "--tabs", help="Tabulation size. Use negative to use tabs instead of spaces. (default: 4)", type=int, default=4)
    parser.add_argument("-i", "--include-local", help="Other \"headers\" to include in the output file", action="append")
    parser.add_argument("-I", "--include-global", help="Other <headers> to include in the output file", action="append")
    parser.add_argument(
        "-o", "--output", help="Provide a path to put the output file", type=argparse.FileType("w"))
    args = parser.parse_args(argv[1:])

    def chunks(l, n):
        """Yield n number of sequential chunks from l."""
        ll = len(l)
        for i in range(ll // n + (1 if ll % n != 0 else 0)):
            yield l[i*n:(i+1)*n]

    data: bytes = args.file.read()
    data_size = len(data)
    data = [f"0x{c:02x}" for c in data]
    tab_caracter = "\t"
    data = f",\n{(' ' if args.tabs >= 0 else tab_caracter)*abs(args.tabs)}".join([", ".join(a)
                          for a in chunks(data, args.count if args.count > 0 else len(data))])

    include_list = []

    if not args.include_local is None:
        include_list.extend([f"#include \"{i}\"" for i in args.include_local])

    if not args.include_global is None:
        include_list.extend([f"#include <{i}>" for i in args.include_global])

    includes = "\n".join(include_list)
    if len(include_list) > 0:
        includes += "\n\n"

    output_data = f"""{includes}const uint8_t {args.name}[] = {{
{(' ' if args.tabs >= 0 else tab_caracter)*abs(args.tabs)}{data}
}};
const uint32_t {args.size_name if not args.size_name is None else args.name + "_size"} = sizeof({args.name});
"""

    if args.output is None:
        args.output = open(os.path.splitext(args.file.name)[0] + ".h", "w")
    args.output.write(output_data)


if __name__ == "__main__":
    main()
