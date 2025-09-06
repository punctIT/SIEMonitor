CXX = g++ -std=c++20 

TARGET_DIR = target
TARGET = $(TARGET_DIR)/program

SRC := $(shell find src -name "*.cpp")
MOC_HEADERS := src/backend/ServerConection.h\
			   src/backend/UpdateWorker.h\
			   src/frontend/gui.h\
               src/frontend/window/SIEM/siem.h\
			   src/frontend/window/SIEM/UpdateSiemData.h

MOCS := $(MOC_HEADERS:src/%.h=$(TARGET_DIR)/moc_%.cpp)

# moc pentru Qt6
MOC = /usr/lib/qt6/libexec/moc

# Include path pentru Qt6 pe WSL
CXXFLAGS = -I/usr/include/x86_64-linux-gnu/qt6 \
           -I/usr/include/x86_64-linux-gnu/qt6/QtWidgets \
           -I/usr/include/x86_64-linux-gnu/qt6/QtCore \
		   -I/usr/include/x86_64-linux-gnu/qt6/QtCharts \
           -std=c++20

# Librării
LIBS = -lsqlite3 -lQt6Widgets -lQt6Core -lQt6Gui -lQt6Charts 

all: $(TARGET)

$(TARGET): $(SRC) $(MOCS) | $(TARGET_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(MOCS) $(LIBS)

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

# regulă pentru generat fișiere moc
$(TARGET_DIR)/moc_%.cpp: src/%.h | $(TARGET_DIR)
	mkdir -p $(dir $@)
	$(MOC) $< -o $@

clean:
	rm -rf $(TARGET_DIR)
