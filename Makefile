# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g -std=c++20 -O0 $(shell pkg-config --cflags openssl)

# Linker flags
LDFLAGS = $(shell pkg-config --libs openssl)

# Source files
SRCS = main.cpp utils.cpp phases.cpp story.cpp

# Header files
HDRS = utils.h phases.h story.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Output executable
TARGET = bomb

# Default rule
all: $(TARGET)

# Rule to compile the executable
$(TARGET): $(OBJS) Makefile
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)
	strip --strip-debug $(TARGET)  # Strip debug symbols after compilation

# Rule to compile object files
%.o: %.cpp $(HDRS) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove the compiled files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
