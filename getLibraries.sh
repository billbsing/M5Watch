#!/bin/bash

cd libraries
rm -rf M5StickC
git clone https://github.com/m5stack/M5StickC.git
rm -rf M5StickC/examples
rm -rf M5StickC/.git

rm -rf NTPClient
git clone https://github.com/arduino-libraries/NTPClient.git
rm -rf NTPClient/.git

rm -rf TimeLib
git clone https://github.com/PaulStoffregen/Time.git TimeLib
rm -rf TimeLib/.git

if [ -d pubsubclient ]; then
	rm -rf pubsubclient
fi
git clone https://github.com/knolleary/pubsubclient.git
rm -rf pubsubclient/.git
