CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17

MSYS2_ROOT ?= C:/msys64

INCLUDES := -I$(MSYS2_PATH)/include -Iinclude
LDFLAGS  := -L$(MSYS2_PATH)/lib -mconsole
LIBS := -lglfw3 -lglew32 -lopengl32

SRC := $(wildcard src/*.cpp) \
       $(wildcard src/renderer/*.cpp) \
	   $(wildcard src/audio/*.cpp) \
	   $(wildcard src/input/*.cpp) \
	   $(wildcard src/time/*.cpp)
TARGET := bin/window.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(INCLUDES) $(LDFLAGS) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
