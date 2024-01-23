#!/usr/bin/python3

# Copyright 2022 kipcode66
from PIL import Image, ImageDraw
import argparse
import struct
import io
import os


def toRGB5A3(r, g, b, a):
    if a == 255:
        return 0x8000 | ((int(r * 0x1f / 255 + 0.5) & 0x1f) << 10) | ((int(g * 0x1f / 255 + 0.5) & 0x1f) << 5) | ((int(b * 0x1f / 255 + 0.5) & 0x1f))
    else:
        return ((int(a * 0x7 / 255 + 0.5) & 0x7) << 12) | ((int(r * 0xf / 255 + 0.5) & 0xf) << 8) | ((int(g * 0xf / 255 + 0.5) & 0xf) << 4) | ((int(b * 0xf / 255 + 0.5) & 0xf))


def fromRGB5A3(val):
    if val & 0x8000 != 0:
        return (int(((val >> 10) & 0x1f) * 0xff / 0x1f), int(((val >> 5) & 0x1f) * 0xff / 0x1f), int(((val) & 0x1f) * 0xff / 0x1f), 255)
    else:
        return (int(((val >> 8) & 0xf) * 0xff / 0xf), int(((val >> 4) & 0xf) * 0xff / 0xf), int(((val) & 0xf) * 0xff / 0xf), int(((val >> 12) & 0x7) * 0xff / 0x7))


def read_banner_header(file):
    flags, anim_speed, *title_arrays = struct.unpack('>4xIH22x64H', file.read(0xA0))
    title_array, subtitle_array = "".join([chr(c) for c in title_arrays[:32]]), "".join([chr(c) for c in title_arrays[32:]])
    title_end = title_array.find('\0')
    subtitle_end = subtitle_array.find('\0')
    title = title_array[:title_end if title_end >= 0 else len(title_array)]
    subtitle = subtitle_array[:subtitle_end if subtitle_end >= 0 else len(subtitle_array)]
    return (flags, anim_speed, title, subtitle)


def read_tile(file):
    image = Image.new('RGBA', (4 ,4))
    img = ImageDraw.Draw(image)
    for j in range(4):
        for i in range(4):
            img.point([(i, j)], fromRGB5A3(*struct.unpack('>H', file.read(0x2))))
    return image


def read_banner_data(file):
    img = Image.new('RGBA', (192, 64))
    for j in range(img.height // 4):
        for i in range(img.width // 4):
            tile = read_tile(file)
            img.paste(tile, (i * 4, j * 4))
    return img


def read_banner_icons(file: io.BufferedReader):
    icons = []
    while len(file.peek(1)) > 0:
        img = Image.new('RGBA', (48, 48))
        for j in range(img.height // 4):
            for i in range(img.width // 4):
                tile = read_tile(file)
                img.paste(tile, (i * 4, j * 4))
        icons.append(img)
    return icons


def read_banner(file):
    header = read_banner_header(file)
    banner = read_banner_data(file)
    icons = read_banner_icons(file)
    return header, banner, icons

def directoryPathParser(string):
    if os.path.exists(string):
        if os.path.isfile(string):
            raise argparse.ArgumentTypeError(
                "The output has to be an existing directory or a new directory; Got a file")
    return string

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='Extracts a banner file into component images')
    parser.add_argument('-V', '--version', action='version',
                        version='%(prog)s 0.1.0')
    parser.add_argument('banner', type=argparse.FileType('rb'),
                        help='Path to the image file')
    parser.add_argument('out_dir', type=directoryPathParser,
                        help='Name of the output folder')
    params = parser.parse_args()

    header, banner, icons = read_banner(params.banner)

    print("flags: {}; anim_speed: {}; title: \"{}\", subtitle: \"{}\"".format(*header))

    if not os.path.exists(params.out_dir):
        os.makedirs(params.out_dir, exist_ok=True)

    file_handle = open(params.out_dir + os.path.sep + "banner.png", 'wb')
    banner.save(file_handle)
    file_handle.close()

    for i, icon in enumerate(icons):
        file_handle = open(params.out_dir + os.path.sep + "icon{}.png".format(i), 'wb')
        icon.save(file_handle)
        file_handle.close()