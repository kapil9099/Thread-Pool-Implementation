CXX = g++
CXXFLAGS = -std=c++11 -pthread -Wall -I./src

TARGET = threadpool
SRCS = src/main.cpp
HDRS = src/ThreadPool.h src/ThreadPool.tpp

$(TARGET): $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

