#scripts/kconfig/Makefile

# File name: Makefile (GpioTestDriver/)
# Code author: Ramana R (github@Rr42)
# Code version: v1.0
# Application: GPIO test driver module
# Description: 
# 	This code ficitilates easy compilation, testing and deploynment for the GPIO test driver module.
# License:
#   Copyright (C) 2019  Ramana R (github@Rr42)
#   
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#   
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#   
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.

obj-m     += GpioDriverMod.o
GpioDriverMod-y := GpioDriver.o gpioCore.o

KERNEL_DIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

MAJOR_NUM := $(shell cat /proc/devices | grep GpioDriver | grep -oEi "([0-9]+)")

SUBDIRS := $(wildcard */)

TOPTARGETS := all clean

all: $(SUBDIRS) GpioDriverMod.ko

$(TOPTARGETS): $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

GpioDriverMod.ko:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

load:
	@sh gpiodriverRun.sh 1 0 
	@sleep 2

install: load
	$(eval MAJOR_NUM := $(shell cat /proc/devices | grep GpioDriver | grep -oEi "([0-9]+)") )

	@mknod /dev/GpioDriver c $(shell cat /proc/devices | grep GpioDriver | grep -oEi "([0-9]+)") 0
	@echo Device file created

	@chmod 777 /dev/GpioDriver
	@echo Device file permission granted

uninstall:
	@sh gpiodriverRun.sh 2 0
	@rm /dev/GpioDriver
	@echo Device file removed

clean:
	rm -rf *.o *.ko *.mod *.symvers *.order .*.cmd *.mod.c .tmp_versions .cache.mk

.PHONY: $(TOPTARGETS) $(SUBDIRS)
