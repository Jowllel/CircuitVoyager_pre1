# GUI design
import tkinter as tk
from tkinter import scrolledtext

import time

# Communication with serial port
import serial
from serial.tools import list_ports

# Multi-threading
import threading

# Get path
import os


class GUI:
    # GUI main class
    def __init__(self, title):

        self.t = time.time()

        self.voltageText = None
        self.currentText = None
        self.powerText = None
        self.timerText = None
        self.VRangeText = None
        self.ARangeText = None
        self.stringOld = None
        self.stringNew = None
        self.portNamesList = []
        self.timeoutNum = 0

        self.isAnyPortAvailable = False
        self.isStarted = False
        self.serialPortName = None
        self.serialPortBaud = 115200

        self.serialPortManager = SerialPortManager(self.serialPortBaud)
        self.get_available_serial_ports()

        self.guiUpdateInterval = 40

        self.window = tk.Tk()
        # Title of application window
        self.window.title(title)
        # Icon of application window

        self.topFrame = tk.Frame(self.window, bg="#cccccc")

        self.scanButton = tk.Button(
            self.topFrame,
            text="Scan Serial Ports",
            bg="#0051ff",
            fg="#ffffff",
            border=0,
            highlightbackground="#ffffff",
            highlightthickness=2,
            activebackground="#1f7cff",
            activeforeground="#ffffff",
            font=("Consolas", "10", "bold"),
            command=self.scan_button_command,
        )

        # Define a tk.StringVar for storing selected item in OptionMenu
        self.selectedPort = tk.StringVar()
        # Set default value of selectedPort
        if self.isAnyPortAvailable == False:
            self.portNamesList = ["No ports available"]
        self.selectedPort.set(self.portNamesList[0])

        self.portsOptionMenu = tk.OptionMenu(
            self.topFrame, self.selectedPort, *self.portNamesList
        )

        self.portsOptionMenu.configure(
            bg="#ffffff",
            fg="#222222",
            border=0,
            highlightbackground="#aaaaaa",
            activebackground="#eeeeee",
            activeforeground="#111111",
            font=("Consolas", "10", "bold"),
        )
        if self.isAnyPortAvailable == False:
            self.portsOptionMenu.configure(state="disabled")

        # Define a tk.IntVar for storing selected item in OptionMenu
        self.selectedBaudRate = tk.IntVar()
        # Set default value of selectedBaudRate
        self.selectedBaudRate.set(115200)

        self.connectButton = tk.Button(
            self.topFrame,
            text="Connect",
            bg="#00a832",
            fg="#ffffff",
            border=0,
            highlightbackground="#ffffff",
            highlightthickness=2,
            activebackground="#3fcc69",
            activeforeground="#ffffff",
            font=("Consolas", "10", "bold"),
            command=self.start_button_command,
        )
        if self.isAnyPortAvailable == False:
            self.connectButton.configure(
                state="disabled", bg="#bbbbbb", highlightbackground="#aaaaaa"
            )

        self.textBox = tk.Text(
            self.topFrame,
            bg="#222222",
            fg="#eeeeee",
            border=0,
            wrap="none",
            highlightbackground="#aaaaaa",
            highlightthickness=2,
            font=("Consolas", "72", "bold"),
        )

        self.voltageText = tk.StringVar(value="-")
        self.voltageLabel = tk.Label(
            self.topFrame,
            textvariable=self.voltageText,
            font=("Consolas", "42", "bold"),
            bg="#cccccc",
            fg="#444444"
        )

        self.currentText = tk.StringVar(value="-")
        self.currentLabel = tk.Label(
            self.topFrame,
            textvariable=self.currentText,
            font=("Consolas", "42", "bold"),
            bg="#cccccc",
            fg="#444444"
        )

        self.powerText = tk.StringVar(value="-")
        self.powerLabel = tk.Label(
            self.topFrame,
            textvariable=self.powerText,
            font=("Consolas", "42", "bold"),
            bg="#cccccc",
            fg="#444444"
        )

        self.timerText = tk.StringVar(value="Timeout: -")
        self.timerLabel = tk.Label(
            self.topFrame,
            textvariable=self.timerText,
            font=("Consolas", "10"),
            bg="#cccccc",
            fg="#444444"
        )

        self.voltageNameLabel = tk.Label(
            self.topFrame,
            text="\nVoltage:",
            font=("Consolas", "32"),
            bg="#cccccc",
            fg="#444444"
        )

        self.currentNameLabel = tk.Label(
            self.topFrame,
            text="\nCurrent:",
            font=("Consolas", "32"),
            bg="#cccccc",
            fg="#444444"
        )

        self.powerNameLabel = tk.Label(
            self.topFrame,
            text="\nPower:",
            font=("Consolas", "32"),
            bg="#cccccc",
            fg="#444444"
        )

        self.VRangeText = tk.StringVar(value="Range: -")
        self.VRangeLabel = tk.Label(
            self.topFrame,
            textvariable=self.VRangeText,
            font=("Consolas", "10"),
            bg="#cccccc",
            fg="#444444"
        )

        self.ARangeText = tk.StringVar(value="Range: -")
        self.ARangeLabel = tk.Label(
            self.topFrame,
            textvariable=self.ARangeText,
            font=("Consolas", "10"),
            bg="#cccccc",
            fg="#444444"
        )

        # Start updating textbox in GUI
        self.recursive_update_textbox()

        ###############################
        ## Widgets size and position ##
        ###############################

        padding = 10
        window_width = 770
        window_height = 290

        # Size of application window
        self.window.geometry("{}x{}".format(window_width, window_height))
        # Don't allow resizing in the x or y direction
        self.window.resizable(False, False)

        self.topFrame.configure(padx=padding, pady=padding)
        self.topFrame.place(x=0, y=0, width=window_width, height=window_height)

        self.scanButton.configure(width=30)
        self.scanButton.grid(column=0, row=0, padx=padding, pady=padding)

        self.portsOptionMenu.configure(width=30)
        self.portsOptionMenu.grid(column=1, row=0, padx=padding, pady=padding)

        self.connectButton.configure(width=30)
        self.connectButton.grid(column=2, row=0, padx=padding, pady=padding)

        self.voltageNameLabel.grid(column=0, row=2)
        self.currentNameLabel.grid(column=1, row=2)
        self.powerNameLabel.grid(column=2, row=2)

        self.voltageLabel.grid(column=0, row=3)
        self.currentLabel.grid(column=1, row=3)
        self.powerLabel.grid(column=2, row=3)

        self.timerLabel.grid(column=2, row=1)

        self.VRangeLabel.grid(column=0, row=4)
        self.ARangeLabel.grid(column=1, row=4)

        self.window.protocol("WM_DELETE_WINDOW", self.close_window)
        # Blocking loop for GUI (Always put at the end)

        self.scan_button_command()

        self.window.mainloop()

    def getTimeoutNumber(self):
        return self.timeoutNum

    def start_button_command(self):

        if self.isStarted == False:
            self.isStarted = True
            self.connectButton.configure(
                bg="#ba0020",
                highlightbackground="#ffffff",
                activebackground="#cf324d",
                text="Disconnect",
            )
            # Get desired serial port name
            self.serialPortName = self.selectedPort.get()
            # Get desired serial port baud rate
            self.serialPortBaud = self.selectedBaudRate.get()
            # Start Serial Port Communication
            self.serialPortManager.set_name(self.serialPortName)
            self.serialPortManager.set_baud(self.serialPortBaud)
            self.serialPortManager.start()
            # Start updating textbox in GUI
            self.recursive_update_textbox()

        else:
            self.isStarted = False
            self.connectButton.configure(
                bg="#00a832",
                highlightbackground="#ffffff",
                activebackground="#3fcc69",
                text="Connect",
            )
            self.timerText.set("Timeout: -")
            self.voltageText.set("-")
            self.currentText.set("-")
            self.powerText.set("-")
            self.VRangeText.set("Range: -")
            self.ARangeText.set("Range: -")

            self.serialPortManager.stop()

    def scan_button_command(self):
        self.portNamesList = self.get_available_serial_ports()

        if len(self.portNamesList) == 0:
            self.isAnyPortAvailable = False
            self.portNamesList = ["No ports available"]
            self.portsOptionMenu.configure(state="disabled")
            self.connectButton.configure(
                state="disabled", bg="#bbbbbb", highlightbackground="#aaaaaa"
            )
        else:
            self.isAnyPortAvailable = True
            self.portsOptionMenu.configure(state="normal")
            if self.isStarted:
                self.connectButton.configure(
                    bg="#ba0020",
                    highlightbackground="#ffffff",
                    activebackground="#cf324d",
                    state="normal",
                )
            else:
                self.connectButton.configure(
                    bg="#00a832",
                    highlightbackground="#ffffff",
                    activebackground="#3fcc69",
                    state="normal",
                )

        self.update_option_menu(self.portNamesList)

    def get_available_serial_ports(self):
        # Clear portNames list
        portNames = []
        # Get a list of available serial ports
        portsList = list_ports.comports()
        # Sort based on port names
        portsList = sorted(portsList)

        for port in portsList:
            portNames.append(port.device)

        return portNames

    def update_option_menu(self, portNames):
        # Remove old items
        self.portsOptionMenu["menu"].delete(0, "end")
        # Add new items
        for portName in portNames:
            self.portsOptionMenu["menu"].add_command(
                label=portName, command=tk._setit(self.selectedPort, portName)
            )
        # Set default value of selectedPort
        self.selectedPort.set(portNames[0])

    def recursive_update_textbox(self):
        serialPortBuffer = self.serialPortManager.read_buffer()
        # Update textbox in a kind of recursive function using Tkinter after() method
        self.textBox.insert(tk.INSERT, serialPortBuffer.decode("ascii"))

        if self.timerText.get() != "Timeout: -":
            self.timeoutNum = int(time.time() - self.t)
            self.timerText.set(f"Timeout: {self.timeoutNum}s")

        self.stringOld = self.stringNew
        self.stringNew = serialPortBuffer.decode("ascii")

        print(self.stringNew, end="")

        if not self.stringOld == self.stringNew:
            if len(self.stringNew) == 28:
                splitString = self.stringNew.split("\t")
                self.voltageText.set(splitString[0])
                self.currentText.set(splitString[1])
                self.powerText.set(splitString[2])
                self.VRangeText.set(splitString[3])
                self.ARangeText.set(splitString[4])
                self.t = time.time()
                self.timerText.set(f"Timeout: {self.timeoutNum}s")

                if self.VRangeText.get() == "VR:1":
                    self.VRangeText.set("Range: 4.9V")
                if self.VRangeText.get() == "VR:2":
                    self.VRangeText.set("Range: 10.35V")
                if self.ARangeText.get() == "AR:1\n":
                    self.ARangeText.set("Range: 330mA")
                if self.ARangeText.get() == "AR:2\n":
                    self.ARangeText.set("Range: 1.32A")

        # autoscroll to the bottom
        self.textBox.see(tk.END)
        # Recursively call recursive_update_textbox using Tkinter after() method
        if self.serialPortManager.isRunning:
            self.window.after(self.guiUpdateInterval, self.recursive_update_textbox)

    def close_window(self):
        if self.isStarted:
            self.serialPortManager.stop()
        self.window.destroy()


class SerialPortManager:
    # A class for management of serial port data in a separate thread
    def __init__(self, serialPortBaud=115200):
        self.isRunning = False
        self.serialPortName = None
        self.serialPortBaud = serialPortBaud
        self.serialPort = serial.Serial()
        # Create a byte array to store incoming data
        self.serialPortBuffer = bytearray()

    def set_name(self, serialPortName):
        self.serialPortName = serialPortName

    def set_baud(self, serialPortBaud):
        self.serialPortBaud = serialPortBaud

    def start(self):
        self.isRunning = True
        self.serialPortThread = threading.Thread(target=self.thread_handler)
        self.serialPortThread.start()

    def stop(self):
        self.isRunning = False

    def thread_handler(self):

        while self.isRunning:

            if not self.serialPort.isOpen():

                self.serialPort = serial.Serial(
                    port=self.serialPortName,
                    baudrate=self.serialPortBaud,
                    bytesize=8,
                    timeout=99999,
                    stopbits=serial.STOPBITS_ONE,
                )
            else:
                self.serialPort.write(b"1")
                # Wait until there is data waiting in the serial buffer
                while self.serialPort.in_waiting > 0:
                    # Read only one byte from serial port
                    serialPortByte = self.serialPort.read(1)
                    self.serialPortBuffer.append(int.from_bytes(serialPortByte, byteorder='big'))
                    # Process incoming bytes
                    self.main_process(serialPortByte)

        if self.serialPort.isOpen():
            self.serialPort.close()

    def read_buffer(self):
        # Return a copy of serial port buffer
        buffer = self.serialPortBuffer
        # Clear serial port buffer
        self.serialPortBuffer = bytearray()
        return buffer

    def __del__(self):
        if self.serialPort.isOpen():
            self.serialPort.close()

    def main_process(self, inputByte):
        # Print the received byte in Python terminal
        try:
            character = inputByte.decode("ascii")
        except UnicodeDecodeError:
            pass


if __name__ == "__main__":
    # Create the GUI
    gui = GUI("CircuitVoyager pre1 UI")
