# Makefile

# 变量定义
CXX = g++
CXXFLAGS = -Wall 
TARGET = main
SRC = main.cpp

# 目标规则
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) $(TARGET).exe
