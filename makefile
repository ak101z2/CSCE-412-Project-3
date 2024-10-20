CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
SRCS = main.cpp request.cpp webserver.cpp loadbalancer.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = main

all: clean_log $(EXEC)

clean_log:
	rm -f log.txt

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean clean_log