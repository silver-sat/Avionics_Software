#!/usr/bin/python3
##
# @file verify_command.py
# @brief Verify command
# @author Lee A. Congdon (lee@silversat.org)
# @version 1.0.0
# @date 1 September 2022

"""Verify command"""

import argparse
import os
import hashlib
import hmac

##
#
# @param str string string to sign
# @param str secret secret for signing
# @param int sequence optioanl sequence number, default = 1
# @param str separator optional separator, default = ':'
#


def get_args():
    """Parse arguments"""

    parser = argparse.ArgumentParser(
        description="Validate HMAC authentication string",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument("message", type=str, help="Command to be authenticated")
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
        default=":",
        help="Field separator",
    )

    args = parser.parse_args()

    if os.path.isfile(args.secret):
        args.secret = open(args.secret, 'rb').read()

    return args


def main():
    """Validate authentication string"""

    args = get_args()
    args.message = args.message.split(args.separator)
# todo: no os exit
    if len(args.message) != 4:
        print("Invalid separator")
        os.exit()
# todo: no os exit
    if int(args.message[0]) != args.sequence:
        print("Invalid sequence number")
        os.exit()

    sequence = repr(args.sequence).encode("utf-8")
    salt = args.message[1].encode("utf-8")
    separator = args.separator.encode("utf-8")
    command = args.message[2].encode("utf-8")
    command_hmac = hmac.new(args.secret, digestmod=hashlib.blake2s)
    command_hmac.update(sequence)
    command_hmac.update(separator)
    command_hmac.update(salt)
    command_hmac.update(separator)
    command_hmac.update(command)
    if hmac.compare_digest(command_hmac.hexdigest(), args.message[3]):
        print("Command validated")
    else:
        print("Command not valid")

if __name__ == "__main__":
    main()
