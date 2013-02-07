FILES := $(wildcard test_files/*.cpp)

UINCLUDE := untested
INCLUDE := tested

build: $(FILES)
	g++ -I $(UINCLUDE) -I $(INCLUDE) $(FILES) -lrt
