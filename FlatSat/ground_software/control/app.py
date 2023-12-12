"""

    Initialization for SilverSat ground control software
    Lee A. Congdon
    10 October 2023
    
"""

from flask import Flask, render_template, request
import serial
import datetime

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
        command_link.write(FEND + REMOTE_FRAME + command.encode("utf-8") + FEND)
    except:
        pass


# Application

app = Flask(__name__)


command_link = serial.Serial("/dev/tty.usbserial-A10MHKWZ", 57600, timeout=0.5)
transmissions = []


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
            case "CallSign":
                command_link.write("Call Sign".encode("utf-8"))
            case "Refresh":
                pass
            case _:
                pass

    transmission = (
        command_link.read_until(expected=FEND) + command_link.read_until(expected=FEND)
    )[1:-1]
    while transmission:
        # timestamp = datetime.datetime.utcnow().replace(microsecond=0).isoformat()
        if transmission[0] == 0x07:
            transmissions.append(
                f"Beacon: {transmission[1:].decode('utf-8')}"
            )
        else:
            transmissions.append(f"{transmission[1:].decode('utf-8')}")
        transmission = (
            command_link.read_until(expected=FEND)
            + command_link.read_until(expected=FEND)
        )[1:-1]
    return render_template("control.html", transmissions=transmissions[-7:])
