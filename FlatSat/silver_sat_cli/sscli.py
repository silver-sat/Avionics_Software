#!/usr/bin/env python3
"""
 @file sscli.py
 @author Lee A. Congdon (lee@silversat.org)
 @brief SilverSat Command Line Interface
 @version 1.0.0
 @date 2023-06-10
"""

import argparse

# will also need pyserial, see utility.py in test_avionics for example


def get_args():
    """Parse arguments"""

# read the documentation for argparse at python.org

    parser = argparse.ArgumentParser(
        description="SilverSat Command Line Interface",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument(
        "port", help="serial port for satellite commands"
    )  # required argument for serial port
    # -h/--help is provided by argparse
    # add a -v/--verbose argument provide additional detail

    return parser.parse_args()


def main():
    """SiverSat Interface"""

    args = get_args()


# commands for the satellite are listed in commands.h
# need a way to issue each command with a keystroke
# need a way to frame the commands correctly (e.g. fend, remote data, command, fend)
# for commands that require a time, e.g. SetClock and PicTimes, need a way to access GMT
# for PicTimes, may want a way to set an interval in the future
# for each command, need to see the results
# for signed commands, need a way to generate the sequence and the signature and format correctly
# need a way to see the output of the command: ACKs, NACKs, and RESponses
# may want to format the output since some bytes are not printable
# do not need to handle beacons (but need to set the beacon spacing with BeaconSp)
# assess using redirection of stdin for batch processing of commands created in advance
# assess using an optional input file for batch processing of commands created in advance

if __name__ == "__main__":
    main()
