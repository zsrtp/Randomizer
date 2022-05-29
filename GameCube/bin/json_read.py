#!/usr/bin/python3

import argparse
import json
import sys


def main():

    parser = argparse.ArgumentParser(
        sys.argv[0], description="Tool to extract the symbols from an ELF file.")
    parser.add_argument("file", type=argparse.FileType("r"), help="The JSON file to read")
    parser.add_argument("field", type=str, help="The field's name to fetch")
    args = parser.parse_args()

    with args.file as f:
        j = json.load(f)
        print(j[args.field])


if __name__ == "__main__":
    main()
