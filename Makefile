CFLAGS = -Wall -Wextra -Iinclude
BUILD = build
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:%.c=$(BUILD)/%.o)

all: $(BUILD)/vis

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/vis: $(OBJECTS) | $(BUILD)
	gcc $(CFLAGS) $(OBJECTS) -o $(BUILD)/vis -lm `sdl2-config --cflags --libs`
	chmod +x $(BUILD)/vis

$(BUILD)/%.o: %.c | $(BUILD)
	gcc $(CFLAGS) -c $< -o $@
# 	$< -> input file name
#   $@ -> target file name

clean:
	rm -rf $(BUILD)/*
