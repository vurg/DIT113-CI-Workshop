# DIT113-CI-Workshop


## Getting started

Continuous integration is a powerful process for automating the testing and integration of code into a remote git repository. Continuous deployment is the next step where the software artifacts are deployed to production environments. CI allows software teams to efficiently work together, and CD reduces the time to deploy projects, making stakeholders and customers happy.

The objective of this workshop is to practice CI and CD, and to demonstrate its usefulness in a software development project. We will use the Wio Terminal as our target platform, for which we will write software, build it in the GitLab CI/CD cloud environment, and deploy it by way of a local machine which has a physical connection to the device.

## Getting Started
- Please fork this project and give access to your team members.
- Please install arduino-cli: https://arduino.github.io/arduino-cli/0.35/installation/
At least one person in each team should have arduino-cli.


## Requirements
FR1. The system shall display a timestamp of when the device was last updated. #3
FR2. The system shall display a message from the author who triggered the software release. #4

## Continuous Integration (CI)

1) Local build process with arduino-cli: issues and limitations

2) Fixing a CI pipeline - what is .gitlab-ci.yml?

3) Implement new features and make commits - triggering CI automated build process

4) Use environment variables which you can inject at runtime into the CI/CD environment

## Continuous Deployment (CD)

5) Deploying software to a physical device from your CI/CD pipeline on the cloud

6) Deploying software variants to a physical device without needing to change your source code

## Authors and acknowledgment
Nasit Vurgun (Nas)

## Project status
TODO:
- add build artifacts to CI/CD pipeline
- use docker for local runner