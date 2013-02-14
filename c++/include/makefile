FILES := $(wildcard test_files/*.cpp)

UINCLUDE := untested
INCLUDE := tested

debug: $(FILES)
	g++ -I $(UINCLUDE) -I $(INCLUDE) $(FILES) -lrt

debug-full: $(FILES)
	g++ -I $(UINCLUDE) -I $(INCLUDE) -g $(FILES) -lrt

release: $(FILES)
	g++ -I $(UINCLUDE) -I $(INCLUDE) -O2 $(FILES) -lrt


