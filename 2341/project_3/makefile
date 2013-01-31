FILES := $(wildcard src/*.c)
MAPFILES := $(wildcard maps/*.c)
TESTSRC := $(wildcard linked_list/*.c)
TESTALSRC := $(wildcard array_list/*.c)
TESTFILES := $(wildcard test/*.c)

P := include
T := test

build: $(FILES)
	gcc -I $(P) $(FILES) $(TESTALSRC) -I $(T) $(TESTFILES)

clean: 
	cd include; rm -f *o
	cd test; rm -f *o
