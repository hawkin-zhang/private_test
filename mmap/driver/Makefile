ARCH := arm
CROSS_COMPILE := arm-linux-gnueabihf-
TARGET_MODULE:=mmap
$(TARGET_MODULE)-objs := mmap_driver.o
obj-m := $(TARGET_MODULE).o

KDIR := /opt/hawkin/sac/nps-hmi/linux
PWD := $(shell pwd)
topdir := $(shell cd $(src)/.. && pwd)
EXTRA_CFLAGS := -I$(topdir)/include 
EXTRA_CFLAGS += -Wno-unused-variable

EXTRA_CFLAGS += -Wno-unused-value

EXTRA_CFLAGS += -Wno-unused-label

EXTRA_CFLAGS += -Wno-unused-parameter
EXTRA_CFLAGS += -Wno-unused-function

EXTRA_CFLAGS += -Wno-unused
EXTRA_CFLAGS += -Wno-date-time 
MAKEARCH := $(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)
default:
	        $(MAKEARCH) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	        $(MAKEARCH) -C $(KDIR) SUBDIRS=$(PWD) clean
