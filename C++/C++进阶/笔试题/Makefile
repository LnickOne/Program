# Makefile for DaVinci Color Wheel Automation

# 检查操作系统
ifeq ($(OS),Windows_NT)
    CXX = g++
    CXXFLAGS = -std=c++11 -Wall -Wextra
    LIBS = -lUIAutomationCore -lole32 -loleaut32 -lcv2 -lhighgui -limgproc -lopencv_core
    EXECUTABLE = davinci_color_wheel.exe
    CLEAN_CMD = del /f $(OBJECTS) $(EXECUTABLE)
else
    all: 
	@echo "Error: This program only compiles and runs on Windows platform!"
	@echo "Please use Visual Studio or MinGW on Windows to compile this program."
	@exit 1
endif

# 源文件
SOURCES = davinci_color_wheel.cpp davinci_color_wheel_impl.cpp

# 头文件
HEADERS = davinci_color_wheel.h

# 目标文件
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean run

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(CLEAN_CMD)

# 运行程序
run: $(EXECUTABLE)
	./$(EXECUTABLE)