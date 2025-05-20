CC = g++
CFLAGS = -Wall -Wextra -Werror -I include
SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/main
all: $(TARGET)

$(TARGET): $(SRC_DIR)/main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC_DIR)/main.cpp

clean:
	rm -rf $(BUILD_DIR)
	mkdir $(BUILD_DIR)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
