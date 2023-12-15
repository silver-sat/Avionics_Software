"""

    Initialization for SilverSat ground control software
    Lee A. Congdon
    10 October 2023
    
"""

from flask import Flask, render_template, request
import serial
import datetime
import threading

## KISS special characters

FEND = b"\xC0"  # frame end
REMOTE_FRAME = b"\xAA"

# Lock for serial link

serial_link = threading.Lock()

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


# Get command responses


def get_responses():
    transmissions = []
    try:
        transmission = (
            command_link.read_until(expected=FEND)
            + command_link.read_until(expected=FEND)
        )[1:-1]
    except:
        pass
    while transmission:
        if transmission[0] == 0x07:
            transmissions.append(
                f"Beacon: {transmission[1:].decode('utf-8', errors='replace')}"
            )
        else:
            transmissions.append(
                f"{transmission[1:].decode('utf-8', errors='replace')}"
            )
        try:
            transmission = (
                command_link.read_until(expected=FEND)
                + command_link.read_until(expected=FEND)
            )[1:-1]
        except:
            pass
    return transmissions


# Application

app = Flask(__name__)

command_link = serial.Serial("/dev/tty.usbserial-A10MHKWZ", 57600, timeout=0.5)


@app.route("/", methods=["GET", "POST"])
def index():
    button = request.form.get("clicked_button")
    serial_link.acquire()

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
    transmissions = get_responses()
    serial_link.release()
    return render_template("control.html", transmissions=transmissions)


@app.post("/radio")
def adjust_frequency():
    frequency = request.form.get("frequency")
    serial_link.acquire()
    issue(f"ModifyFrequency {frequency}")
    get_responses()
    serial_link.release()
    return {}
