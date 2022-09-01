#!/usr/bin/env python3
"""Test for sign_ciommand.py"""

import os
from subprocess import getstatusoutput, getoutput

prg = "./sign_command.py"

class TestSignCommand:
    """Test command signing"""


    def test_exists():
        """exists"""

        assert os.path.isfile(prg)


    def test_usage():
        """usage"""

        for flag in ["-h", "--help"]:
            rv, out = getstatusoutput(f"{prg} {flag}")
            assert rv == 0
            assert out.lower().startswith("usage")


    def test_no_operate():
        """NoOperate"""

        arg = "'NoOperate' './secret.txt'"
        out = getoutput(f"{prg} {arg}")
        assert out.strip() == "????????????????"

    def test_beacon_sp():
        """BeaconSp"""

        arg = "'BeaconSp 10' './secret.txt'" 
        out = getoutput(f"{prg} {arg}")
        assert out.strip() == "????????????????"


    def test_sequence():
        """sequence number"""

        arg = "'No Operate' './secret.txt' '-q 2'" 
        out = getoutput(f"{prg} {arg}")
        assert out.strip() == "????????????????"


    def test_separator():
        """field separator"""

        arg = "'No Operate' './secret.txt' '-p +'" 
        out = getoutput(f"{prg} {arg}")
        assert out.strip() == "????????????????"

