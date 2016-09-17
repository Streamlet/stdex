
CC = g++ -std=c++11 -Wall -Werror -Wfatal-errors -I ../../external/xlUnitTest/Include

SOURCES := $(wildcard *.cpp ../../unittest/*.cpp)
OBJECTS := $(SOURCES:%.cpp=%.o)
TARGET = unittest

$(TARGET) : $(SOURCES)
	$(CC) $(SOURCES) -o $(TARGET)

clean:
	@rm -f $(OBJECTS) $(TARGET)
distclean: clean

all: $(TARGET)


