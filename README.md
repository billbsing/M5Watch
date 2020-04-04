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
+   Add your `watch/private.h` file with you WiFI connection details.
```bash
$ vi watch/private.h
```
+   Build the project
```bash
$ make
```
+   Upload to the M5StickC
```bash
$ make upload
```

### WiFi Connection

This project uses the file `watch/private.h` file. This include file
contains the SSID and password of your WiFi network.

For example `watch/private.h`:

```c
// Private WiFi details

#define WIFI_SSID                           "MY-WIFI-SSID"
#define WIFI_PASSWORD                       "MY-WIFI-PASSWORD"

```
### Libraries

This project use the following libraries:

+   [M5StickC](https://github.com/m5stack/M5StickC.git)

+   [NTPClient](https://github.com/arduino-libraries/NTPClient.git)

+   [TimeLib](https://github.com/PaulStoffregen/Time.git)
