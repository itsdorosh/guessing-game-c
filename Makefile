CC = /opt/homebrew/bin/gcc-16
CFLAGS = -g -Wall
LDLIBS =
BUILD_DIR = build
TARGET = $(BUILD_DIR)/guessing-game

.PHONY: all clean run

all: $(TARGET)

$(TARGET): guessing-game.c guessing-game.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) guessing-game.c -o $(TARGET) $(LDLIBS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: all
	$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
