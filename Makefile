CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17

MSYS2_ROOT ?= C:/msys64

INCLUDES := -I$(MSYS2_PATH)/include
LDFLAGS  := -L$(MSYS2_PATH)/lib
LIBS := -lglfw3 -lglew32 -lopengl32

SRC := main.cpp
TARGET := window.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(INCLUDES) $(LDFLAGS) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
