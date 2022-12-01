#!/usr/bin/python3
##
# @file make_secret.py
# @brief Make a secret for command signing
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 2 September 2022

"""Make secret"""

import argparse
import secrets

##
# Command line arguments
# file optional filename, default is stdout
#


def get_args():
    """Parse arguments"""

    parser = argparse.ArgumentParser(
        description="Create secret for command validation",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument(
        "-f",
        "--file",
        type=argparse.FileType("wb", 0),
        metavar="file",
        default="./secret.txt",
        help="File for secret",
    )

    args = parser.parse_args()
    return args


def main():
    """Generate secret and write to file"""

    args = get_args()
    with args.file as f:
        f.write(secrets.token_bytes(16))
        f.close()


if __name__ == "__main__":
    main()
