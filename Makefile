CFLAGS = -Wall -Wextra -Iinclude
BUILD = build
SRC = src
SOURCES = $(wildcard $(SRC)/*.c)
OBJECTS = $(SOURCES:$(SRC)/%.c=$(BUILD)/%.o)

all: $(BUILD)/vis

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/vis: $(OBJECTS) | $(BUILD)
	gcc $(CFLAGS) $(OBJECTS) -o $(BUILD)/vis -lm `sdl2-config --cflags --libs`
	chmod +x $(BUILD)/vis

# 	$< -> input file name
#   $@ -> target file name
$(BUILD)/%.o: $(SRC)/%.c | $(BUILD)
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)/*
