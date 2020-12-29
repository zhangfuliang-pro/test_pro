CONFIG_SYS_CONFIG_NAME := $(subst ",,$(CONFIG_SYS_CONFIG_NAME))

ccflags-y += -I$(srctree)/$(src)/drv/inc
ccflags-y += -I$(srctree)/$(src)/drv/pub
ccflags-y += -I$(srctree)/$(src)/drv/src/api/hdmitx
ccflags-y += -I$(srctree)/$(src)/drv/src/drv/hdmitx/include
ccflags-y += -I$(srctree)/$(src)/hal/$(CONFIG_SYS_CONFIG_NAME)/hdmitx/include
ccflags-y += -I$(srctree)/$(src)/hal/$(CONFIG_SYS_CONFIG_NAME)/hdmitx
ccflags-y += -I$(srctree)/$(src)/hal/$(CONFIG_SYS_CONFIG_NAME)/hdcp
ccflags-y += -I$(srctree)/$(src)/../common

ccflags-y += -DHDMITX_OS_TYPE_UBOOT

obj-y +=./drv/src/uboot/drv_hdmitx_os.o
obj-y +=./drv/src/drv/hdmitx/drvHDMITx.o
obj-y +=./drv/src/api/hdmitx/apiHDMITx.o
obj-y +=./hal/$(CONFIG_SYS_CONFIG_NAME)/hdmitx/halHDMIUtilTx.o
obj-y +=./hal/$(CONFIG_SYS_CONFIG_NAME)/hdmitx/hal_hdmitx_top_tbl.o
obj-y +=./hal/$(CONFIG_SYS_CONFIG_NAME)/hdmitx/halHDMITx.o
obj-y +=./hal/$(CONFIG_SYS_CONFIG_NAME)/hdmitx/halHDCPTx.o
obj-y +=./hal/$(CONFIG_SYS_CONFIG_NAME)/hdcp/halHDCP.o