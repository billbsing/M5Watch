#!/bin/bash

rm -rf buildEnvironment
mkdir buildEnvironment
cd buildEnvironment

git clone https://github.com/plerup/makeEspArduino.git
git clone https://github.com/espressif/arduino-esp32.git esp32Arduino
echo "get esp32Arduino"
cd esp32Arduino/tools
python get.py
