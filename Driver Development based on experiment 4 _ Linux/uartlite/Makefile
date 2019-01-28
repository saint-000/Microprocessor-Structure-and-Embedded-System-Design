
ifneq ($(KERNELRELEASE),)
obj-m	:= uartlite.o

else
ifeq ($(TARGET),)
TARGET := $(shell uname -r)
endif
PWD := $(shell pwd)
CC = $(CROSS_COMPILE)gcc
KDIR ?= /home/zynq/Downloads/2016.3/linux-xlnx-xilinx-v2016.3

default:
	@echo $(TARGET) > module.target
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	@rm -f *.ko *.o modules.order Module.symvers *.mod.? .uartlite*.* *~
	@rm -rf .tmp_versions module.target

install: uartlite.ko
	install --mode 0644 uartlite.ko /lib/modules/$(shell cat module.target)/kernel/drivers/char/
	/sbin/depmod -a $(shell cat module.target)
uartlite.ko:
	$(MAKE)
endif
