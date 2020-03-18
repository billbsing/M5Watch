
# THIS_DIR := $(realpath $(dir $(realpath $(lastword $(MAKEFILE_LIST)))))

UNAME := $(shell uname)

ENV_DIR = $(THIS_DIR)../buildEnvironment
# ENV_DIR = $(HOME)/Apps/ESP8266Development/buildEnvironment
ENV_DIR = ../buildEnvironment
ESP_ROOT = $(ENV_DIR)/esp32Arduino
ESP_LIBS = $(ESP_ROOT)/libraries
SHARE_LIBS = ../libraries
LOCAL_LIBS = ../local_libraries

SKETCH = main.ino
# VERBOSE = 0
SINGLE_THREAD = 1

LIBS = \
	$(ESP_LIBS)/ESP32					\
	$(ESP_LIBS)/WebServer				\
	$(ESP_LIBS)/WiFi			   		\
	$(ESP_LIBS)/ArduinoOTA				\
	$(ESP_LIBS)/SPI						\
	$(ESP_LIBS)/FS						\
	$(ESP_LIBS)/Wire					\
	$(ESP_LIBS)/SPIFFS					\
	$(SHARE_LIBS)/M5StickC				\
	$(SHARE_LIBS)/TimeLib				\
	$(LOCAL_LIBS)/Events				\
	$(LOCAL_LIBS)/Persistent



#	$(SHARE_LIBS)/TimeLib

CHIP=esp32
BOARD=m5stick-c
FLASH_DEF=4MB

# BOARD ?= $(BOARD_$(DEVICE))
# FLASH_DEF ?= $(FLASH_DEF_$(DEVICE))
# BUILD_TYPE ?= $(BUILD_TYPE_$(DEVICE))

ifeq ($(FLASH_DEF),)
FLASH_DEF := 4M3M
endif

ifeq ($(BOARD),)
BOARD := esp32
endif

ifeq ($(BUILD_TYPE),)
BUILD_TYPE := ESP32
endif

# ifndef DEVICE
# @echo "No device specified"
# exit 0
# endif

CPP_EXTRA ?= -DDEVICE_$(DEVICE) -DBUILD_TYPE_$(BUILD_TYPE)

# VERBOSE=1
# make ota OTA_ADDR=192.168.44.15

ifeq ($(UNAME), Linux)
	UPLOAD_PORT=/dev/ttyUSB0
endif
ifeq ($(UNAME), Darwin)
#	UPLOAD_PORT=/dev/cu.usbserial-1410
	UPLOAD_PORT=$(shell ls -1 /dev/tty.usbserial-*)
#	UPLOAD_PORT=/dev/tty.usbserial
#	UPLOAD_PORT=/dev/tty.SLAB_USBtoUART

endif

print-%  : ; @echo $* = $($*)

build:
	@echo "Board: $(BOARD)"
	@echo "Device: $(DEVICE)"
	@echo "Flash type: $(FLASH_DEF)"
	@echo "Build type: $(BUILD_TYPE)"
	# make



include $(ENV_DIR)/makeEspArduino/makeEspArduino.mk
