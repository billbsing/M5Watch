#!/bin/bash

rm -rf buildEnvironment
mkdir buildEnvironment
cd buildEnvironment

echo "get makeEspArduino"
git clone https://github.com/plerup/makeEspArduino.git
echo "get arduno-esp32"
git clone https://github.com/espressif/arduino-esp32.git esp32Arduino
cd esp32Arduino/tools
echo "build arduno-esp32"
python get.py


# cd ../../
# git clone --recursive https://github.com/espressif/esp-idf.git
# cd esp-idf/tools
# instal..sh
