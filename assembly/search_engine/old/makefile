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

FILES := $(wildcard include/*.asm)

MAIN := $(wildcard *.asm)

FILES += $(MAIN)

OBJ = $(FILES:.asm=.o)

all : $(OBJ) link clean

$(OBJ): $(FILES)
	nasm -g -f elf64 $*.asm

link: $(OBJ)
	ld -o a.out $(OBJ)

clean: $(OBJ)
	rm -rf *.o include/*.o
