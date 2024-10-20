CXX = g++
CXXFLAGS = -std=c++20 -O2
TARGET = List
SOURCES = List.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean report run

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

report: report.tex
	xelatex report.tex

clean:
	rm -f $(TARGET) $(OBJECTS) *.aux *.log *.pdf *.fls *.fdb_latexmk *.synctex.gz

run: $(TARGET)
	./$(TARGET)

