#!/usr/bin/python3#!/usr/bin/python3

"""
Packs REL module(s) into a GameCube GCI file.
"""

import argparse
from dataclasses import dataclass
from io import BufferedReader
import sys
import os
import struct
import ctypes
import math
from datetime import datetime
from typing import ByteString, List, Tuple

__author__ = "PistonMiner, and kipcode66"
__copyright__ = "Copyright 2018, PistonMiner"
__credits__ = ["PistonMiner", "kipcode66"]
__license__ = "GPL3"
__version__ = "1.1.0"


def main():
    @dataclass
    class ParserArguments():
        data: BufferedReader
        filename: str
        comment1: str
        comment2: str
        banner: BufferedReader
        icon: BufferedReader
        code: str
        rel: List[BufferedReader]

    # Parsing functions
    def parseFilename(string: str):
        string = string.strip()
        if not string or len(string) > 32:
            raise argparse.ArgumentError(None, "Wrong filename size")
        return string

    def parseComment(string: str):
        if len(string) > 32:
            raise argparse.ArgumentError(None, "Comment too long")
        return string

    def parseGamecode(string: str):
        if len(string) != 4:
            raise argparse.ArgumentError(
                None, "Invalid Game code (wrong size, expecting 4 characters)")
        return string

    parser = argparse.ArgumentParser(
        sys.argv[0], description="Packs data into a GCI file.")
    parser.add_argument("data", type=argparse.FileType(
        "rb"), help="The input file containing the data to pack.")
    parser.add_argument("filename", type=parseFilename,
                        help="The internal name of the file in the GCI")
    parser.add_argument("comment1", type=parseComment,
                        help="First line of comment")
    parser.add_argument("comment2", type=parseComment,
                        help="Second line of comment")
    parser.add_argument("banner", type=argparse.FileType(
        "rb"), help="Banner file for the GCI")
    parser.add_argument("icon", type=argparse.FileType(
        "rb"), help="Icon file for the GCI")
    parser.add_argument("code", type=parseGamecode,
                        help="The 4 character game code (ex: GZ2E for Twilight Princess)")
    parser.add_argument("--rel", type=argparse.FileType("rb"), action="append",
                        help="Additional REL module(s) to add to the GCI file")
    args: ParserArguments = parser.parse_args()

    if args.rel and len(args.rel) > 37:
        raise argparse.ArgumentError(None, "Too many REL modules.")

    with args.data as inputFile:
        inputBuffer = ctypes.create_string_buffer(inputFile.read())[:-1]

    rels: List[Tuple[int, ByteString]] = []
    if args.rel:
        for rel in args.rel:
            with rel as r:
                data = r.read()
                rels.append((struct.unpack(">I", data[:4])[0], data))
    rels.sort(key=lambda t: t[0])
    relative_offset = 0
    offsets = [0, *[relative_offset :=
                    (relative_offset + len(data)) for id, data in rels]][:-1]

    # Load banner and icon
    with args.banner as bannerFile:
        bannerBuffer = ctypes.create_string_buffer(bannerFile.read())[:-1]
        if len(bannerBuffer) != 0x1800:
            if len(bannerBuffer) == 0x1820:
                # Remove the bti header
                bannerBuffer = bannerBuffer[0x20:]
            else:
                print("Warning: banner size mismatch (should be 96x32 RGB5A3)")

    with args.icon as iconFile:
        iconBuffer = ctypes.create_string_buffer(iconFile.read())[:-1]
        if len(iconBuffer) != 0x800:
            if len(iconBuffer) == 0x820:
                # Remove the bti header
                iconBuffer = iconBuffer[0x20:]
            else:
                print("Warning: icon size mismatch %d (should be 32x32 RGB5A3)" %
                      len(iconBuffer))

    # Comment
    commentBuffer = ctypes.create_string_buffer(0x40)
    struct.pack_into("32s", commentBuffer, 0x00, args.comment1.encode())
    struct.pack_into("32s", commentBuffer, 0x20, args.comment2.encode())

    # File info
    fileInfoBuffer = ctypes.create_string_buffer(0x200 - 0x40)
    struct.pack_into(">L", fileInfoBuffer, 0, len(inputBuffer))

    # Additional rels info
    relStartOffset = len(bannerBuffer) + len(iconBuffer) + \
        len(commentBuffer) + len(fileInfoBuffer) + len(inputBuffer)
    offsets = [offset + relStartOffset for offset in offsets]
    for i, (offset, (id, data)) in enumerate(zip(offsets, rels)):
        struct.pack_into(">III", fileInfoBuffer, 4 +
                         i * 0xC, id, len(data), offset)

    # Additional rels data
    relsBuffer = b''.join(data for _, data in rels)

    # CARDRead padding (technically redundant)
    fileLength = len(bannerBuffer) + len(iconBuffer) + \
        len(commentBuffer) + len(fileInfoBuffer) + \
        len(inputBuffer) + len(relsBuffer)
    cardBlockCound = math.ceil(fileLength / 0x200)
    cardPaddingLength = cardBlockCound * 0x200 - fileLength
    cardPaddingBuffer = ctypes.create_string_buffer(cardPaddingLength)

    # Pad to block boundary
    fileLength = len(bannerBuffer) + len(iconBuffer) + \
        len(commentBuffer) + len(fileInfoBuffer) + \
        len(inputBuffer) + len(relsBuffer) + len(cardPaddingBuffer)
    blockCount = math.ceil(fileLength / 0x2000)
    paddingLength = blockCount * 0x2000 - fileLength
    paddingBuffer = ctypes.create_string_buffer(paddingLength)

    # Create header
    headerBuffer = ctypes.create_string_buffer(0x40)
    struct.pack_into("4s",  headerBuffer,  0x00,
                     args.code.encode())  # game code
    struct.pack_into(">H",  headerBuffer,  0x04, 0x3031)		# maker code
    struct.pack_into(">B",  headerBuffer,  0x06, 0xFF)			# unused
    struct.pack_into(">B",  headerBuffer,  0x07, 2)				# banner flags (RGB5A3)
    struct.pack_into("32s", headerBuffer,  0x08,
                     args.filename.encode())  # filename
    struct.pack_into(">L",  headerBuffer,  0x28, int(
        (datetime.utcnow() - datetime(2000, 1, 1)).total_seconds()))  # modified time
    struct.pack_into(">L",  headerBuffer,  0x2C, 0)				# image offset
    struct.pack_into(">H",  headerBuffer,  0x30, 2)				# icon format
    # animation speed (1 icon for 12 frames)
    struct.pack_into(">H",  headerBuffer,  0x32, 3)
    struct.pack_into(">B",  headerBuffer,  0x34, 4)				# permissions
    struct.pack_into(">B",  headerBuffer,  0x35, 0)				# copy counter
    struct.pack_into(">H",  headerBuffer,  0x36, 0)				# first block number
    struct.pack_into(">H",  headerBuffer,  0x38, blockCount)  # block count
    struct.pack_into(">H",  headerBuffer,  0x3A, 0xFF)			# unused
    struct.pack_into(">L",  headerBuffer,  0x3C, 0x2000)		# comment address

    outputFilename = os.path.splitext(args.data.name)[0] + ".gci"
    with open(outputFilename, "wb") as outputFile:
        outputFile.write(bytearray(headerBuffer))
        outputFile.write(bytearray(bannerBuffer))
        outputFile.write(bytearray(iconBuffer))
        outputFile.write(bytearray(commentBuffer))
        outputFile.write(bytearray(fileInfoBuffer))
        outputFile.write(bytearray(inputBuffer))
        outputFile.write(bytearray(relsBuffer))
        outputFile.write(bytearray(cardPaddingBuffer))
        outputFile.write(bytearray(paddingBuffer))


if __name__ == "__main__":
    main()
