CONFIG_SYS_CONFIG_NAME := $(subst ",,$(CONFIG_SYS_CONFIG_NAME))

ccflags-y += -I$(srctree)/$(src)/hal/$(CONFIG_SYS_CONFIG_NAME)

obj-$(CONFIG_MS_USB) += drvhostlib.o ubootglue.o
obj-$(CONFIG_MS_ENABLE_USB_LAN_MODULE) += usb_lan.o ax88772a.o rtl8150.o pegasus.o
