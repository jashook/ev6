FILES := $(wildcard src/*.s)
TESTFILES := $(wildcard test/src/*.s)

INCLUDE := include
TESTINCLUDE := test/include

all: debug clean

test-as: $(TESTFILES)

	as -I $(TESTINCLUDE) -g $(TESTSRC)

debug: $(FILES)

	arm-thumb-elf-as -I include -o boot.o boot.s
	arm-thumb-elf-ld -Ttext=0x0 -o boot.elf boot.o
	arm-thumb-elf-objcopy -O binary boot.elf boot.bin
	dd if=/dev/zero of=flash.bin bs=4096 count=4096
	dd if=boot.bin of=flash.bin bs=4096 conv=notrunc

clean:

	rm -rf *.o
