CXX = g++

TARGET_DIR = target
TARGET = $(TARGET_DIR)/program

SRC := $(shell find src -name "*.cpp")

# Include path pentru Qt6 pe WSL
CXXFLAGS = -I/usr/include/x86_64-linux-gnu/qt6 -I/usr/include/x86_64-linux-gnu/qt6/QtWidgets -I/usr/include/x86_64-linux-gnu/qt6/QtCore -std=c++20

# Librării
LIBS = -lsqlite3 -lQt6Widgets -lQt6Core -lQt6Gui

all: $(TARGET)

$(TARGET): $(SRC) | $(TARGET_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LIBS)

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

clean:
	rm -rf $(TARGET_DIR)
