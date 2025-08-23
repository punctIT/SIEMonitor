CXX = g++

TARGET_DIR = target
TARGET = $(TARGET_DIR)/program

SRC := $(shell find src -name "*.cpp")

# Biblioteca SQLite3
LIBS = -lsqlite3 /usr/local/lib/bcrypt.a

all: $(TARGET)

$(TARGET): $(SRC) | $(TARGET_DIR)
	$(CXX) -o $(TARGET) $(SRC) $(LIBS)

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

clean:
	rm -rf $(TARGET_DIR)
