
CC = g++ -std=c++11
INCLUDE_DIR = ../../../external/xlUnitTest/Include
CFLAGS = -I $(INCLUDE_DIR) -Wall -Werror -Wfatal-errors
LFLAGS = 

SOURCES := $(wildcard *.cpp ../../../unittest/*.cpp)
OBJECTS := $(SOURCES:%.cpp=%.o)
TARGET = unittest

$(TARGET) : $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LFLAGS)

clean:
	@rm -f $(OBJECTS) $(TARGET)
distclean: clean

all: clean $(TARGET)


