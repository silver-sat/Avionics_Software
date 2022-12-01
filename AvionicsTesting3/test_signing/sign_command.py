#!/usr/bin/env python3
##
# @file sign_command.py
# @brief Sign command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 1 September 2022

"""Sign command"""

import argparse
import os
import hashlib
import hmac
import secrets

##
# Command line arguments
# string string to sign
# secret secret for signing
# sequence optional sequence number, default = 1
# separator optional separator, default = '|'
#


def get_args():
    """Parse arguments"""

    parser = argparse.ArgumentParser(
        description="Create HMAC authentication string",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument("command", type=str, help="Command to be authenticated")
    parser.add_argument("secret", help="Shared secret string or file name")
    parser.add_argument(
        "-q",
        "--sequence",
        type=int,
        metavar="sequence",
        default=1,
        help="Sequence number",
    )
    parser.add_argument(
        "-p",
        "--separator",
        type=str,
        metavar="separator",
        default="|",
        help="Field separator",
    )

    args = parser.parse_args()

    if os.path.isfile(args.secret):
        args.secret = open(args.secret, "rb").read()
    args.command = args.command.encode("utf-8")
    args.sequence = repr(args.sequence).encode("utf-8")
    args.separator = args.separator.encode("utf-8")

    return args


def main():
    """Generate and display authentication string"""
    args = get_args()
    salt = secrets.token_bytes(16)
    command_hmac = hmac.new(args.secret, digestmod=hashlib.blake2s)
    command_hmac.update(args.sequence)
    command_hmac.update(args.separator)
    command_hmac.update(salt)
    command_hmac.update(args.separator)
    command_hmac.update(args.command)
    print(
        f"{args.sequence.decode(encoding='utf-8')}"
        f"{args.separator.decode(encoding='utf-8')}"
        f"{salt.hex()}"
        f"{args.separator.decode(encoding='utf-8')}"
        f"{args.command.decode(encoding='utf-8')}"
        f"{args.separator.decode(encoding='utf-8')}"
        f"{command_hmac.hexdigest()}"
    )


if __name__ == "__main__":
    main()
