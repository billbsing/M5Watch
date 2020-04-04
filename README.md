# M5Watch

Based on ESP32

M5StickC ESP32-PICO Mini IoT Development Kit

see [M5Watch](https://m5stack.com/collections/m5-core/products/stick-c?variant=17203451265114)

### Build

+   Git clone this repo
```bash
$ git clone https://github.com/billbsing/M5Watch.git
```
+   Donwload the arduino build environment.
```bash
$ ./getBuidEnvironment.sh
```
+   Download the third party external libraries
```bash
$ ./getLibraries.sh
```
+   Build the project
```bash
$ make
```
+   Upload to the M5StickC
```bash
$ make upload
```

### Libraries

This project use the following libraries:

+   [M5StickC](https://github.com/m5stack/M5StickC.git)

+   [NTPClient](https://github.com/arduino-libraries/NTPClient.git)

+   [TimeLib](https://github.com/PaulStoffregen/Time.git)
