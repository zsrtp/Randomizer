#!/usr/bin/python3

# Copyright 2022 kipcode66
from ctypes import ArgumentError
from typing import Tuple
from PIL import Image
import argparse
import struct


def write_banner_header(out_file, flags, animspeed, title, subtitle):
    title_array = [ord(c) for c in title]
    subtitle_array = [ord(c) for c in subtitle]
    out_file.write(struct.pack('>4sIH22x64h', "WIBN".encode("ascii"), flags, animspeed,
                               *(title_array[:32] + ([0] * 32)
                                 [len(title_array):]),
                               *(subtitle_array[:32] + ([0] * 32)[len(subtitle_array):])))


def toRGB5A3(r, g, b, a):
    if a == 255:
        return 0x8000 | ((int(r * 0x1f / 255 + 0.5) & 0x1f) << 10) | ((int(g * 0x1f / 255 + 0.5) & 0x1f) << 5) | ((int(b * 0x1f / 255 + 0.5) & 0x1f))
    else:
        return ((int(a * 0x7 / 255 + 0.5) & 0x7) << 12) | ((int(r * 0xf / 255 + 0.5) & 0xf) << 8) | ((int(g * 0xf / 255 + 0.5) & 0xf) << 4) | ((int(b * 0xf / 255 + 0.5) & 0xf))


def write_rgb5a3(out_file, pixel: Tuple[int]):
    out_file.write(struct.pack(">H", toRGB5A3(*pixel)))


def write_tile(out_file, img):
    for j in range(4):
        for i in range(4):
            write_rgb5a3(out_file, img.getpixel((i, j)))


def write_banner_data(out_file, image: Image):
    image = image.convert('RGBA')
    for j in range(image.height // 4):
        for i in range(image.width // 4):
            tile = image.crop((i * 4, j * 4, (i + 1) * 4, (j + 1) * 4))
            write_tile(out_file, tile)


def write_banner_icons(out_file, *args: Image):
    if len(args) == 0:
        raise ArgumentError("Banner require at least 1 icon")
    for icon in args[:8]:
        for j in range(icon.height // 4):
            for i in range(icon.width // 4):
                tile = icon.crop((i * 4, j * 4, (i + 1) * 4, (j + 1) * 4))
                write_tile(out_file, tile)


def write_banner(out_buf, img: Image, title, subtitle, flags, anim_speed, *icons: Image):
    write_banner_header(out_buf, flags, anim_speed, title, subtitle)
    write_banner_data(out_buf, img)
    write_banner_icons(out_buf, *icons)


def flagNumber(string):
    val = int(string)
    if val < 0 or val > 0xffff:
        raise argparse.ArgumentTypeError(
            "File number can only have integer values between 0 and 65535")
    return val


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='Combines a banner image and icon(s) into a banner file.')
    parser.add_argument('-V', '--version', action='version',
                        version='%(prog)s 0.1.0')
    parser.add_argument('out_file', type=argparse.FileType('wb'),
                        help='Name of the output file')
    parser.add_argument('image_file', type=argparse.FileType('rb'),
                        help='Path to the image file')
    parser.add_argument('icons', type=argparse.FileType('rb'), nargs='+', default="banner2.raw",
                        help='Path to the icon(s) (up to 8)')
    parser.add_argument('-t', '--title', type=str,
                        default="Custom Title", help="Title of the game")
    parser.add_argument('-s', '--subtitle', type=str,
                        default="", help="Subtitle of the game")
    parser.add_argument('-f', '--flags', type=flagNumber, default=0x10,
                        help="Flags to apply to the save file (unsigned short)")
    parser.add_argument('-a', '--anim-speed', type=flagNumber, default=0,
                        help="Animation speed for the icons (unsigned short)")
    params = parser.parse_args()

    # We fetch the picture, and make sure that it has a valid size
    image = Image.open(params.image_file).convert(
        'RGBA').resize((192, 64), resample=Image.BICUBIC)
    icons = [Image.open(icon).convert('RGBA').resize(
        (48, 48), resample=Image.BICUBIC) for icon in params.icons[:8]]
    write_banner(params.out_file, image, params.title, params.subtitle, params.flags, params.anim_speed, *icons)