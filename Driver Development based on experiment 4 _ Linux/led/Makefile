
ifneq ($(KERNELRELEASE),)
obj-m	:= ees331_led.o

else
ifeq ($(TARGET),)
TARGET := $(shell uname -r)
endif
PWD := $(shell pwd)

##   CC =$£¨CROSS_COMPILE£©gcc 
KDIR ?=/home/zynq/downloads/2016.3/linux-xlnx-xilix-v2016.3 


 default:
	@echo $(TARGET) > module.target
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	@rm -f *.ko *.o modules.order Module.symvers *.mod.? .ees331_led*.* *~
	@rm -rf .tmp_versions module.target

install: ees331_led.ko
	install --mode 0644 ees331_led.ko /lib/modules/$(shell cat module.target)/kernel/drivers/char/
	/sbin/depmod -a $(shell cat module.target)
ees331_led.ko:
	$(MAKE)
endif
