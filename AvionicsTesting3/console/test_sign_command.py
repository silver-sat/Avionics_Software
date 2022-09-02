#!/usr/bin/env python3
"""Test for sign_ciommand.py"""

import os
from subprocess import getstatusoutput, getoutput

sign_prg = "./sign_command.py"
verify_prg = "./verify_command.py"
secret = "./secret.txt"


class TestSignCommand:
    """Test command signing"""

    def test_sign_exists(self):
        """sign program exists"""

        assert os.path.isfile(sign_prg)

    def test_verify_exists(self):
        """verify program exists"""

        assert os.path.isfile(verify_prg)

    def test_sign_usage(self):
        """sign program usage"""

        for flag in ["-h", "--help"]:
            rv, out = getstatusoutput(f"{sign_prg} {flag}")
            assert rv == 0
            assert out.lower().startswith("usage")

    def test_verify_usage(self):
        """verify program usage"""

        for flag in ["-h", "--help"]:
            rv, out = getstatusoutput(f"{verify_prg} {flag}")
            assert rv == 0
            assert out.lower().startswith("usage")

    def test_no_operate(self):
        """NoOperate"""

        command = "NoOperate"
        signed_message = getoutput(f"{sign_prg} '{command}' {secret}")
        out = getoutput(f"{verify_prg} '{signed_message}' {secret}")
        assert out.strip() == "Command validated"

    def test_beacon_sp(self):
        """BeaconSp"""

        command = "BeaconSp 10"
        signed_message = getoutput(f"{sign_prg} '{command}' {secret}")
        out = getoutput(f"{verify_prg} '{signed_message}' {secret}")
        assert out.strip() == "Command validated"

    def test_sequence(self):
        """sequence number"""

        command = "NoOperate"
        flag = "-q 5"
        signed_message = getoutput(f"{sign_prg} {flag} '{command}' {secret}")
        out = getoutput(f"{verify_prg} {flag} '{signed_message}' {secret}")
        assert out.strip() == "Command validated"


    def test_separator(self):
        """field separator"""

        command = "BeaconSp 10"
        flag = "--separator \|" # backslash to disable shell treatment of pipe
        signed_message = getoutput(f"{sign_prg} {flag} '{command}' {secret}")
        out = getoutput(f"{verify_prg} {flag} '{signed_message}' {secret}")
        assert out.strip() == "Command validated"
