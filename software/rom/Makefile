###############################################################################
# Project Info

PROJECT = rom
MCU = DEMOSYSTEM

###############################################################################

###############################################################################
# Directories

SRCS = 		$(wildcard src/*.c) $(wildcard lib/*.c)
OBJ = 		obj/
OBJS = 		$(addprefix $(OBJ), $(notdir $(SRCS:.c=.o)))
LD_SCRIPT =     ld/$(MCU)_FLASH.ld
INC = 		-Iinc -Ilib
STARTUP =       crt0

###############################################################################
# Toolchain

RV_PREFIX = /opt/riscv/bin/riscv64-unknown-elf-

32BITCCFLAGS = -march=rv32im_zicsr_zifencei -mabi=ilp32
32BITLDFLAGS = -melf32lriscv
32BITODFLAGS = -mriscv:rv32

CC = $(RV_PREFIX)gcc $(32BITCCFLAGS)
LD = $(RV_PREFIX)ld $(32BITLDFLAGS)
OBJDUMP = $(RV_PREFIX)objdump $(32BITODFLAGS)
OBJCOPY = $(RV_PREFIX)objcopy

CFLAGS = -O0 -c
LDFLAGS = -nostdlib -T$(LD_SCRIPT)

###############################################################################

###############################################################################
# Misc

RM      = rm -rf 				# Remove recursively command
MKDIR   = @mkdir -p $(@D) 			# Creates folders if not present

###############################################################################

all: bin/$(PROJECT).bin

$(OBJ)%.o: src/%.c
	@echo "\n[OBJ]	Creating OBJs from src"
	$(MKDIR)
	$(CC) -o $@ $^ $(INC) $(CFLAGS)

$(OBJ)%.o: lib/%.c
	@echo "\n[OBJ]	Creating OBJs from libs"
	$(MKDIR)
	$(CC) -o $@ $^ $(INC) $(CFLAGS)

obj/$(STARTUP).o: src/$(STARTUP).s
	@echo "\n[OBJ]	Creating OBJs from $(STARTUP).s"
	$(MKDIR)
	$(CC) -o obj/$(STARTUP).o src/$(STARTUP).s $(INC) $(CFLAGS)

bin/$(PROJECT).elf: $(OBJS) obj/$(STARTUP).o
	@echo "\n[ELF]	Creating elf file"
	$(MKDIR)
	$(LD) -o $@ $^ $(LDFLAGS)

bin/$(PROJECT).bin: bin/$(PROJECT).elf
	@echo "\n[ELF]	Creating bin file"
	$(OBJCOPY) -O binary bin/$(PROJECT).elf bin/$(PROJECT).bin
	srec_cat bin/$(PROJECT).bin -binary -offset 0x0000 -byte-swap 4 -o bin/$(PROJECT).mem -vmem
	# xxd -g 4 -c 4 -e bin/$(PROJECT).bin | awk '{print $$2}'

clean:
	-$(RM) obj
	-$(RM) bin

.PHONY: all clean
