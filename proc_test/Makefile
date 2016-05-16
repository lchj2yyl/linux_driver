obj-m += proc_test.o
CURRENT_PATH := $(shell pwd)
LINUX_KERNEL := $(shell uname -r)
LINUX_KERNEL_PATH := /usr/src/linux-headers-$(LINUX_KERNEL)
all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:uninstall
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
install:
	sudo insmod proc_test.ko
uninstall:
	sudo rmmod proc_test
log:
	dmesg
read:
	cat /proc/proc_test_file
write:
	echo ${str} > /proc/proc_test_file