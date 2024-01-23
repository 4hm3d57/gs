CXX = g++

CXX_FLAGS = -Wall -Wextra -Wswitch-enum -std=c++11 -pedantic -fno-exceptions -fexceptions -ggdb -Wno-unused-parameter

INCLUDE_FILES = -I./include
LIB_FILES = -L./lib

SOURCE_FILES = src/glad.c src/main.cpp

TARGET = window.exe

.PHONY: all clean run

all:$(TARGET)

$(TARGET): $(SOURCE_FILES);
	$(CXX) $(CXX_FLAGS) -o $(TARGET) $(INCLUDE_FILES) $(LIB_FILES) $(SOURCE_FILES) -lglfw3

run: $(TARGET)
	./$(TARGET)

clean:
	rm -r $(TARGET)
