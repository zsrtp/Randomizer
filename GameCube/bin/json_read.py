#!/usr/bin/python3

"""
Command line tool to extract data from simple JSON files.
"""

import argparse
import json
import sys

__author__ = "kipcode66"
__copyright__ = "Copyright 2022, kipcode66"
__credits__ = ["kipcode66"]
__license__ = "GPL3"
__version__ = "0.1.0"


def main():

    parser = argparse.ArgumentParser(
        sys.argv[0], description="Tool to extract the symbols from an ELF file.")
    parser.add_argument("file", type=argparse.FileType("r"),
                        help="The JSON file to read")
    parser.add_argument("field", type=str, help="The field's name to fetch")
    args = parser.parse_args()

    with args.file as f:
        j = json.load(f)
        print(j[args.field])


if __name__ == "__main__":
    main()
