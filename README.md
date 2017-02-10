# About

The he853-remote project provides a library and CLI programm for the
[homeeasy he853 433.92MHz USB RF remote control sender](http://www.elro.eu/en/products/category/home_automation/home_easy/zenders2/pc_afstandsbediening_usb_dongle).
The sender is used for toggling RF controlled power sockets.

VID:PID 04d9:1357 Holtek Semiconductor, Inc.

The library was is extracted from [roseasy](http://ros.org/wiki/roseasy)
which is a part of the [ROS (Robot Operating System)](http://www.ros.org/wiki/) project.

Another project that provides a C# Windows SDK for the dongle is
the [HE853 Control Project](http://he853control.sourceforge.net/).

## Usage

You can build the CLI programm by simply running

  `make`

The default protocol is `EU` - you can adjust this in the `main.cpp`
or pass it in over the command line - see parameters below.

```ShellSession
Usage: ./he853 [<DeviceID> <Command> [<Protocol>]]
  DeviceID - ID of the device to act on
  Command  - 0=OFF, 1=ON
    NOTE: AnBan has also values > 1
  Protocol - A=AnBan, U=UK, E=EU, K=KAKU, N=KAKUNEW, L=ALL
    Default protocol is 'E'
    NOTE: Protocol ALL is meant for tests and sends out with all protocols!
    Without parameters the device status will be shown
```

NOTE: You have to have proper access rigths to the USB stick to use it
but the program will tell you if it doesn't work.

The command is either a *0* for *OFF* or anything > 0 for *ON*.
To program the power socket you have to place the power socket into learning
mode and send the *ON* command to it:

  `./he853 2001 1`

After that you can use the deviceId *2001* for toggling the power socket.

### Requirements

* libusb development headers (debian: *libusb-1.0-0-dev*)

### Compile Notes

`he853.h` allows setting of RUN_DRY and DEBUG

### Known Issues

* doesn't compile on OSX
