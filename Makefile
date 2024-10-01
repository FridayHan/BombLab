# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g -std=c++20 -O0

# Source files
SRCS = main.cpp utils.cpp phases.cpp story.cpp

# Header files
HDRS = utils.h phases.h story.h

# Output executable
TARGET = bomb

# Default rule
all: $(TARGET)

# Rule to compile the executable
$(TARGET): $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Clean rule to remove the compiled files
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean
