obj-y += arch/
obj-y += app/
obj-y += drv/
obj-y += component/
CCFLAGS += -Iinclude/ \
	-Icomponent/coremark/ \
	-Icomponent/coremark/barebones/

