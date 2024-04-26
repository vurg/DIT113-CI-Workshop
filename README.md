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

## Local build process with arduino-cli: issues and limitations

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

**Questions:**
1. What are the advantages of setting up an automated build process?
2. Can you see the challenges & limitations of doing this locally in a distributed team? (CI solves these problems.)

## Continuous Integration (CI)
### What is .gitlab-ci.yml?:

Configuration file for GitLab's CI/CD pipeline containing instructions to execute when triggered by a specific event, such as a commit, a merge request, or a release.

A "pipeline" refers to a series of automated steps or stages which your code passed through from development to production.

Example:

```yaml
stages:
  - build
  - test
  - deploy

build:
  stage: build
  script:
    - echo "Building the project..."

test:
  stage: test
  script:
    - echo "Running tests..."

deploy:
  stage: deploy
  script:
    - echo "Deploying the project..."

```
You can also add pre-build and post-deployment instructions. Many customizations possible, we are only scratching the surface here.

#### .gitlab-ci.yml
https://git.chalmers.se/nasit/dit113-ci-workshop/-/blob/main/.gitlab-ci.yml?ref_type=heads

#### pre-build script:
https://git.chalmers.se/nasit/dit113-ci-workshop/-/blob/main/setup-build-env.sh?ref_type=heads

### Fix a broken CI pipeline - triggering the CI automated build process
```bash
git checkout 9-fix-broken-CI-pipeline
```
Requirement 1 has been implemented by your colleague, but there is a problem. The pipeline is failing! He asks you to take a look and to fix it.

**Instructions:**
1. Analyze the broken pipeline logs.
2. Modify the pipeline to install the missing library.
3. Commit the changes.
4. Observe the pipeline in action.

**Questions:**
1. What should you do when the pipeline fails?
2. Is setting up a CI/CD pipeline easy? Why or why not?

### Use environment variables which are injected at runtime into the CI/CD environment
```bash
git checkout 10-custom-deployment-message
```
Requirement 2 has been added to the product backlog. The customer wants you to add a custom message to the UI whenever a new release takes place.

**Instructions:**
1. Modify the source code to add the missing functionality.
3. Commit the changes. 
3. The pipeline will fail! Why?
4. Go to settings > CI/CD > variables to add missing environment variables.
5. Observe the automated build process!

**Questions:**
1. Why is this necessary?
2. What are the benefits?

## Continuous Deployment (CD)
### Deploy software to a physical device from CI/CD pipeline
```bash
git checkout 10-custom-deployment-message
```
Your software is working. What about the hardware? The customer wants to see a demo of your project.

**Instructions:**
1. Create a tag to deploy your software to the device.
2. Observe the deploy process.

**Questions:**
1. What is different about this?
2. What are some challenges?

### Deploy software variants without the need to change your source code
```bash
git checkout main
```
The customer calls and wants you to change the MQTT broker API_key, URI and password. It is urgent. You don't have time to change the source code.

**Questions:**
1. How would you approach this?
2. Why is this useful?

## Authors and acknowledgment
Nasit Vurgun (Nas)

## Project status
TODO:
- add build artifacts to CI/CD pipeline
- use docker for local runner