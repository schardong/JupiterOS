# BUILD SETTINGS ##################################

TARGET := kernel

# BUILD FLAGS #####################################

CFLAGS := -m32 -Wall -Werror -Wextra -Wno-unused -fstrength-reduce -fomit-frame-pointer -fno-stack-protector -finline-functions -nostdinc -nostdlib -fno-builtin
LDFLAGS := -T linker.ld -melf_i386
ASFLAGS := -f elf32
AS := nasm
CC := gcc
LD := ld

ifneq ($(MAKECMDGOALS), release)
    CONFIG := debug
    CFLAGS += -g3 -O0 -D_DEBUG
else
    CONFIG := release
    CFLAGS += -g0 -O2 -DNDEBUG
endif

###################################################

TARGET := bin/$(TARGET)
JUNK_DIR := bin/obj-$(CONFIG)
STRIP := strip
CFLAGS += -MMD -Iinclude

OBJS := $(shell find src -name *.c | sed "s/^src\///")
OBJS := $(foreach obj, $(OBJS:.c=.o), $(JUNK_DIR)$(obj))
ASM_OBJS := $(shell find src -name *.asm | sed "s/^src\///")
ASM_OBJS := $(foreach obj, $(ASM_OBJS:.asm=.ao), $(JUNK_DIR)$(obj))

# RULES ###########################################

.PHONY : all release clean

all: $(TARGET)

release: all
	@$(STRIP) $(TARGET)

clean:
	@rm -Rf bin/*

ifneq ($(MAKECMDGOALS), clean)
	-include $(OBJS:.o=.d)
endif

$(TARGET): $(OBJS) $(ASM_OBJS)
	@$(LD) -o $@ $(LDFLAGS) $^

$(JUNK_DIR)%.o: src/%.c
	@mkdir -p "$(dir $@)"
	@$(CC) -c -o $@ $(CFLAGS) $<

$(JUNK_DIR)%.ao: src/%.asm
	@mkdir -p "$(dir $@)"
	@$(AS) -o $@ $(ASFLAGS) $<
