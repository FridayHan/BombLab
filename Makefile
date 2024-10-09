# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Werror -g -std=c++20 -O0 -fno-stack-protector $(shell pkg-config --cflags openssl)

# Linker flags
# LDFLAGS = -Wl,-Bstatic $(shell pkg-config --libs --static openssl) -ldl -lpthread -lrt -Wl,-Bdynamic -lc
LDFLAGS = /usr/lib/x86_64-linux-gnu/libssl.a /usr/lib/x86_64-linux-gnu/libcrypto.a -ldl -lpthread -lrt -static-libstdc++ -static-libgcc

# Source files
SRCS = main.cpp utils.cpp phases.cpp story.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Output executable
TARGET = bomb++

# Default rule: Build the target executable
all: $(TARGET)

# Rule to compile the executable
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)
	strip --strip-debug $(TARGET)  # Strip debug symbols after compilation

# Rule to compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove compiled files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets to avoid conflicts
.PHONY: all clean
