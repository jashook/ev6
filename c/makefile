FILES := $(wildcard testing/*.c)

INCLUDE := include

debug: $(FILES)
	gcc -I $(INCLUDE) $(FILES)

debug-full: $(FILES)
	gcc -I $(INCLUDE) -g $(FILES)

release: $(FILES)
	gcc -I $(INCLUDE) -O2 $(FILES)


