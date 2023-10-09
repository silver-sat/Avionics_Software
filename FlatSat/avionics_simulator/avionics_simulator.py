"""
    Avionics Command Simulator

    Simulate the SilverSat Avonics Interface for Ground Commands

    Lee A. Congdon (lee@silversat.org)
    5 October 2023

    Based in part on Adafruit state machine https://learn.adafruit.com/circuitpython-101-state-machines/code

"""
import usb_cdc

## KISS special characters

FEND = b"\xC0"  # frame end
FESC = b"\xDB"  # frame escape
TFEND = b"\xDC"  # transposed frame end
TFESC = b"\xDD"  # transposed frame escape

## KISS frame types

LOCAL_FRAME = b"\x00"
REMOTE_FRAME = b"\xAA"
BEACON = b"\x07"
DIGITALIO_RELEASE = b"\x08"
STATUS = b"\x09"
HALT = b"\x0a"
MODIFY_FREQ = b"\x0B"
MODIFY_MODE = b"\x0C"
ADJUST_FREQ = b"\x0D"
TRANSMIT_CARRIER = b"\x17"
BACKGROUND_RSSI = b"\x18"
CURRENT_RSSI = b"\x19"
SWEEP_TRANSMITTER = b"\x1A"
SWEEP_RECEIVER = b"\x1B"
QUERY_REGISTER = b"\x1C"
RADIO_PING = b"\x33"

## Command acknowledgements

ACK = "ACK"
NACK = "NACK"
RES = "RES"

## Command responses

responses = {
    "SetClock": "SRC",
    "BeaconSP": "SBI",
    "PicTimes": "SPT",
    "ClearPicTimes": "CPT",
    "UnsetClock": "URC",
    "ReportT": "GRC 2020-01-01T01:01:01",
    "GetPicTimes": "GPT 2020-01-01T01:01:01",
    "GetTelemetry": "GTY AX 1.000 AY 1.000 AZ 1.000 RX 1.000 RY 1.000 RZ 1.000 T 1.000",
    "GetPower": "GPW BBV 1.000 BBC 1.000 TS1 1.000 TS2 1.000 5VC 1.000 L5V 1.000 H1S 1 H2S 1 H3S 1",
    "GetComms": "GRS radio status",
    "GetBeaconInterval": "GBI 180",
    "NoOperate": "NOP",
    "SendTestPacket": "STP test packet",
    "PayComms": "PYC",
    "TweeSlee": "TSL",
    "ExternalWatchdog": "WDG",
    "ModifyFrequency": "RMF 123456789",
    "ModifyMode": "RMM 1",
    "AdjustFrequency": "RAF 123456",
    "TransmitCW": "RTC CW mode complete",
    "BackgroundRSSI": "RBR 123",
    "CurrentRSSI": "RCR 123",
    "SweepTransmitter": "RST sweep done",
    "SweepReceiver": "RSR 123 123456789 123",
    "QueryRegister": "RQR 123",
}

## Serial data link

serial_data = usb_cdc.data

# Message class


class Message(object):
    def __init__(self):
        self.content = bytearray()
        self.tokens = list()
        pass

    def process(self):
        self.tokens = self.content.decode("utf-8").split()
        print(f"tokens: {self.tokens}")
        if responses.get(self.tokens[0]):
            print('Sending ACK')
            serial_data.write(FEND + REMOTE_FRAME + ACK + FEND)
            print(f'Sending response {responses.get(self.tokens[0])}')
            serial_data.write(
                FEND + REMOTE_FRAME + RES + f" {responses.get(self.tokens[0])}" + FEND
            )
        else:
            print('Sending NACK')
            serial_data.write(FEND + REMOTE_FRAME + NACK + FEND)
        self.content = bytearray()


# Machine class


class StateMachine(object):
    def __init__(self):
        self.state = None
        self.states = {}

    def add_state(self, state):
        self.states[state.name] = state

    def go_to_state(self, state_name):
        if self.state:
            print(f"Exiting {self.state.name}")
            self.state.exit(self)
        self.state = self.states[state_name]
        print(f"Entering {self.state.name}")
        self.state.enter(self)

    def update(self):
        if self.state:
            # print(f'Updating {self.state.name}')
            self.state.update(self)


## State classes

## Abstract base class


class State(object):
    # shared among all instances of subclasses
    data_byte = b""
    message = Message()

    def __init__(self):
        pass

    @property
    def name(self):
        return ""

    def enter(self, machine):
        pass

    def exit(self, machine):
        pass

    def update(self, machine):
        if serial_data.in_waiting:
            State.data_byte = serial_data.read(1)
            print(f"data_byte: {State.data_byte}")
            return True
        return False


## Waiting for transmission


class Waiting(State):
    def __init__(self):
        super().__init__()

    @property
    def name(self):
        return "waiting"

    def enter(self, machine):
        State.enter(self, machine)

    def exit(self, machine):
        State.exit(self, machine)

    def update(self, machine):
        if State.update(self, machine):
            if State.data_byte == FEND:
                machine.go_to_state("start_received")
            else:
                machine.go_to_state("waiting")


# Start received


class StartReceived(State):
    def __init__(self):
        super().__init__()

    @property
    def name(self):
        return "start_received"

    def enter(self, machine):
        State.enter(self, machine)

    def exit(self, machine):
        State.exit(self, machine)

    def update(self, machine):
        if State.update(self, machine):
            if State.data_byte == FEND:
                machine.go_to_state("start_received")
            elif State.data_byte == REMOTE_FRAME:
                machine.go_to_state("command_received")
            else:
                machine.go_to_state("waiting")


# Command received


class CommandReceived(State):
    def __init__(self):
        super().__init__()

    @property
    def name(self):
        return "command_received"

    def enter(self, machine):
        State.enter(self, machine)

    def exit(self, machine):
        State.exit(self, machine)

    def update(self, machine):
        if State.update(self, machine):
            if State.data_byte == FESC:
                machine.go_to_state("escape_received")
            elif State.data_byte == FEND:
                # zero length message ignored
                machine.go_to_state("waiting")
            else:
                machine.go_to_state("byte_received")


# Byte received


class ByteReceived(State):
    def __init__(self):
        super().__init__()

    @property
    def name(self):
        return "byte_received"

    def enter(self, machine):
        State.enter(self, machine)
        # ignore long messages
        if len(State.message.content) > 255:
            machine.go_to_state("waiting")
        State.message.content += State.data_byte

    def exit(self, machine):
        State.exit(self, machine)

    def update(self, machine):
        if State.update(self, machine):
            if State.data_byte == FESC:
                machine.go_to_state("escape_received")
            elif State.data_byte == FEND:
                State.message.process()
                machine.go_to_state("waiting")
            else:
                machine.go_to_state("byte_received")


# Escape received


class EscapeReceived(State):
    def __init__(self):
        super().__init__()

    @property
    def name(self):
        return "escape_received"

    def enter(self, machine):
        State.enter(self, machine)

    def exit(self, machine):
        State.exit(self, machine)

    def update(self, machine):
        if State.update(self, machine):
            if State.data_byte == TFEND:
                State.data_byte == FEND
                machine.go_to_state("byte_received")
            elif State.data_byte == TFESC:
                State.data_byte == FESC
                machine.go_to_state("byte_received")
            else:
                machine.go_to_state("waiting")


# Initialize

print("Starting Avionics Command simulator")
state_machine = StateMachine()
state_machine.add_state(Waiting())
state_machine.add_state(StartReceived())
state_machine.add_state(CommandReceived())
state_machine.add_state(ByteReceived())
state_machine.add_state(EscapeReceived())

# Process transmissions

state_machine.go_to_state("waiting")

while True:
    state_machine.update()
