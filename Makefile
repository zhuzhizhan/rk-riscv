#====================================================================
# File		 : Makefile
# Change Logs:
# Date			Author			Notes
# 2019.3.18		never			the first version
#====================================================================

TARGET := riscv.elf

export CROSS_COMPILE ?= /home/zzz/code/hifive-riscv-tool-chain/riscv32-unknown-elf-gcc/bin/riscv32-unknown-elf-
DEVICE := -march=rv32imc -mabi=ilp32 -nostartfiles -Wl,--no-relax,-Bstatic -ffreestanding -lgcc -gdwarf-2 -D__riscv -Wl,--defsym=__comrv_cache_size=1536 -Wl,--defsym=__comrv_cache_alignment_size=512
export CCFLAGS := -O0
CCFLAGS += $(DEVICE)
CCFLAGS += -g
export ASFLAGS := -c
ASFLAGS += $(DEVICE)
export LDFLAGS := $(DEVICE)
LDFLAGS += -T link.ld

export CC := $(CROSS_COMPILE)gcc
export AR := $(CROSS_COMPILE)ar
export LD := $(CROSS_COMPILE)ld
export CP := ${CROSS_COMPILE}objcopy
export DP := ${CROSS_COMPILE}objdump
export NM := ${CROSS_COMPILE}nm

#--------------------------------------------------------------------
# echo option
#--------------------------------------------------------------------
ifeq ("$(origin V)", "command line")
KBUILD_V
RBOSE = $(V)
endif
ifndef KBUILD_VERBOSE
KBUILD_VERBOSE = 0
endif
ifeq ($(KBUILD_VERBOSE),1)
Q =
MAKE_SILENT =
else
Q = @
MAKE_SILENT = -s
endif
export Q KBUILD_VERBOSE MAKE_SILENT

#--------------------------------------------------------------------
# output file
#--------------------------------------------------------------------
O ?= out
export O

D ?= dump

srcdir := $(CURDIR)

ifeq ($(O),)
objdir := $(srcdir)
rm-dir :=
else
objdir := $(O)
rm-dir := $(objdir)
endif

ifeq ($(D),)
dumpdir := $(D)
rm-dir +=
else
dumpdir := $(D)
rm-dir += $(dumpdir)
endif

#--------------------------------------------------------------------
# make all
#--------------------------------------------------------------------
target_deps := $(objdir)/built-in.o
OLDTARGET := $(TARGET)
DUMPTARGET := $(dumpdir)/$(OLDTARGET)
TARGET := $(objdir)/$(TARGET)

all: $(TARGET)
	$(Q)echo "GEN $(DUMPTARGET).dump"
	$(Q)$(DP) -d $(TARGET) >$(DUMPTARGET).dump
	$(Q)echo "GEN $(DUMPTARGET).sym"
	$(Q)$(NM) $(TARGET) | sort >$(DUMPTARGET).sym
	$(Q)echo "GEN $(DUMPTARGET).map"
	$(Q)$(DP) -h $(TARGET) >$(DUMPTARGET).map

ifeq ($(Baremetal), y)
$(TARGET): $(target_deps) | $(objdir) $(dumpdir)
	$(Q)echo "GEN $(TARGET)"
	$(Q)$(CC) $(LDFLAGS) $(target_deps) -o $@
	$(Q)echo "GEN $(TARGET).bin"
	$(Q)$(CP) -O binary $(TARGET) $(TARGET).bin
else
$(TARGET): $(target_deps) | $(objdir) $(dumpdir)
	$(Q)echo "GEN $(TARGET)"
	$(Q)$(CROSS_COMPILE)gcc $(LDFLAGS) $(target_deps) -o $@
endif

ifneq ($(O),)
$(objdir):
	$(Q)if [ ! -d $@ ]; then mkdir -p $(objdir); fi
endif

ifneq ($(D),)
$(dumpdir):
	$(Q)if [ ! -d $@ ]; then mkdir -p $(dumpdir); fi
endif

$(sort $(target_deps)): $(srcdir);
$(srcdir):
	$(Q)make $(MAKE_SILENT) -f Makefile.build obj=$(srcdir)

clean:
	$(Q)echo "CLEAN"
	$(Q)set -e
	$(Q)make $(MAKE_SILENT) -f Makefile.build obj=$(srcdir) clean
	$(Q)rm -rf $(TARGET) $(rm-dir)

.PHONY: all clean FORCE $(srcdir) $(dumpdir)
