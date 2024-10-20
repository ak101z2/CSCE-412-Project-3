# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Source files
SRCS = main.cpp request.cpp webserver.cpp loadbalancer.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = load_balancer

# Default target
all: $(EXEC)

# Linking the object files to create the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compiling the source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -f $(OBJS) $(EXEC)

# Phony targets
.PHONY: all clean