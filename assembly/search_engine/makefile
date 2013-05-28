################################################################################
################################################################################
#
# Author: Jarret Shook
#
# Module: makefile
#
# Modifications:
#
# 26-April-13: Last Updated
# 26-April-13: Created
#
# Timeperiod: ev6
#
# Notes: makefile for nasm (assembly) files
#
################################################################################
################################################################################

FILES := $(wildcard *.asm)
OBJ := $(FILES:.asm=.o)

INCLUDE := include

all: debug link clean

debug: $(FILES)
	nasm -g -i $(INCLUDE)/ -f elf64 $(FILES)

link: $(OBJ)
	ld -o a.out $(OBJ)

clean: $(FILES)
	rm -rf *.o include/*.o
