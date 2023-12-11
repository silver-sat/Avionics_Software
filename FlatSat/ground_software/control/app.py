"""

    Initialization for SilverSat ground control software
    Lee A. Congdon
    10 October 2023
    
"""

from flask import Flask, render_template, request
import serial
import datetime
import time

## KISS special characters

FEND = b"\xC0"  # frame end
REMOTE_FRAME = b"\xAA"

# GMT time formatted for command


def now():
    return datetime.datetime.now(datetime.timezone.utc).strftime("%Y %m %d %H %M %S")


# GMT time in one minute


def now1m():
    return (
        datetime.datetime.now(datetime.timezone.utc) + datetime.timedelta(seconds=60)
    ).strftime("%Y %m %d %H %M %S")


# Issue command


def issue(command):
    try:
        data_link.write(FEND + REMOTE_FRAME + command.encode("utf-8") + FEND)
    except:
        pass


# Application

app = Flask(__name__)
data_link = serial.Serial("/dev/tty.usbserial-A10MHKWZ", 57600)

@app.route("/", methods=["GET", "POST"])
def index():
    button = request.form.get("clicked_button")
    if button == None:
        command = request.form.get("command")
        issue(command)
    else:
        match button:
            case "NOP":
                issue("NoOperate")
            case "STP":
                issue("SendTestPacket")
            case "SRC":
                issue(f"SetClock {now()}")
            case "GRC":
                issue("ReportT")
            case "PYC":
                issue("PayComms")
            case "SPT1":
                issue(f"PicTimes {now1m()}")
            case "SBI1":
                issue("BeaconSp 60")
            case "SBI3":
                issue("BeaconSp 180")
            case "GTY":
                issue("GetTelemetry")
            case "GPW":
                issue("GetPower")
            case _:
                pass
    ack = b"No data"
    res = b"No data"
    time.sleep()
    try:
        ack = (
            data_link.read_until(expected=FEND) + data_link.read_until(expected=FEND)
        )[2:-1]
    except:
        pass
    if ack == b"ACK":
        try:
            res = (
                data_link.read_until(expected=FEND)
                + data_link.read_until(expected=FEND)
            )[2:-1]
        except:
            pass
    messages = [ack.decode("utf-8"), res.decode("utf-8")]
    return render_template("control.html", messages=messages)
