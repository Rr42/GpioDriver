#scripts/kconfig/Makefile

# gcc -Wall -o GpioDriver.o GpioDriver.c -L$(WIRDIR)/wiringPi

obj-m     += GpioDriverMod.o
GpioDriverMod-y := GpioDriver.o gpioCore.o

KERNEL_DIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

MAJOR_NUM := $(shell cat /proc/devices | grep GpioDriver | grep -oEi "([0-9]+)")

all:
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
