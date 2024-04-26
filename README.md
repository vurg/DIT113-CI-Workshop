# DIT113-CI-Workshop


## Getting started

Continuous integration is a powerful process for automating the testing and integration of code into a remote git repository. Continuous deployment is the next step where the software artifacts are deployed to production environments. CI allows software teams to efficiently work together, and CD reduces the time to deploy projects, making stakeholders and customers happy.

The objective of this workshop is to practice CI and CD, and to demonstrate its usefulness in a software development project. We will use the Wio Terminal as our target platform, for which we will write software, build it in the GitLab CI/CD cloud environment, and deploy it by way of a local machine which has a physical connection to the device.

## Getting Started
1. Please fork this project and give access to your team members.
2. Please install arduino-cli: https://arduino.github.io/arduino-cli/0.35/installation/. At least one person in each team should have arduino-cli.


## Requirements
1. The system shall display a timestamp of when the device was last updated.
2. The system shall display a message from the author who triggered the software release.

## Continuous Integration (CI)
### Local build process with arduino-cli: issues and limitations

Arduino-cli is a command line tool to manage Arduino projects. It can manage dependencies (package manager, configuration files), automate the build process (compile code, link libraries), and upload firmware to the physical device. First, let us launch arduino-cli from terminal:
```bash
arduino-cli -h
```
With the wio terminal connected, and powered on, run:
```bash
arduino-cli board list
```
Here, you can see the serial port (USB) and the board name. Some of you might not see the board name yet. That's because we are missing the core libraries for this specific flavor of Arduino. To get the board to show up, we need to update the package manager to the latest index, and to download these core libraries:
```bash
printf "board_manager:\n  additional_urls:\n    - https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json\n" > .arduino-cli.yaml
arduino-cli core update-index --config-file .arduino-cli.yaml
arduino-cli core install Seeeduino:samd --config-file .arduino-cli.yaml
```
However, some libraries are not included with the core libraries. How do we get those??

Suppose we want to install the libraries for: 
https://wiki.seeedstudio.com/Wio-Terminal-RTC/#example-code

We can search the package manager index using a search key:
```bash
arduino lib search RTC_SAMD51
```
It prints:
```bash
Name: "Seeed Arduino RTC"
  Author: Seeed Studio
  Maintainer: Seeed Studio <techsupport@seeed.cc>
  Sentence: RTC library for SAMD21 and SAMD51.
  Paragraph: When your project needs to be unplugged, how to keep the time counting? This library can help you keep the current time
  Website: https://github.com/Seeed-Studio/Seeed_Arduino_RTC
  Category: Timing
  Architecture: samd
  Types: Contributed
  Versions: [1.0.0, 2.0.0]

```

We can install indexed libraries using their name and version:
```bash
# Install 'native' packages (libraries that do not come with the core)
arduino-cli lib install "Seeed Arduino rpcWiFi@1.0.6"
arduino-cli lib install "PubSubClient@2.8"
```
If a library is not indexed by the package manager, we can clone them from GitHub:
```bash
# Install 'third-party' packages / libraries: find proper location and 'git clone'
apt-get install git -y
cd `arduino-cli config dump | grep sketchbook | sed 's/.*\ //'`/libraries
git clone https://github.com/me-no-dev/AsyncTCP.git
git clone https://github.com/RoboticsBrno/ESP32-Arduino-Servo-Library.git
```
We do not need to install these, they are shown as examples.

What next?

Compile the code: 
```bash
arduino-cli compile --fqbn Seeeduino:samd:seeed_wio_terminal
```
`--fqbn` flag is for fully-qualified board name

Finally, upload the code to the Wio Terminal device:
```bash
arduino-cli board list # check device connection
arduino-cli upload -p $COM_PORT --fqbn Seeeduino:samd:seeed_wio_terminal
```
where `$COM_PORT`should be replaced with the USB serial communication port for your device (e.g. COM3, COM6, /dev/tty/ACM0, etc.)

### Fix a broken CI pipeline - what is .gitlab-ci.yml?

### Implement new features and make commits - triggering the CI automated build process

### Use environment variables which are injected at runtime into the CI/CD environment

## Continuous Deployment (CD)
### Deploy software to a physical device from CI/CD pipeline

### Deploy software variants without the need to change your source code

## Authors and acknowledgment
Nasit Vurgun (Nas)

## Project status
TODO:
- add build artifacts to CI/CD pipeline
- use docker for local runner

TODO: 
- 3 branches:
  - Source code (main)
  - Broken pipeline, missing RTC library, need to fetch dependencies so arduino-cli can build project
  - Working pipeline, want to use environment variables in CI/CD pipeline