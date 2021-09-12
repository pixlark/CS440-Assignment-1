CXX=clang++
CXXFLAGS=-std=c++11 -g -O0 -ldl -Wall -Wextra -Wpedantic -Werror -Wno-unused-variable

SRC=
HDR=Deque.hpp

my_tests: my_tests.cpp $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) $(SRC) my_tests.cpp -o $@

tests: test.cpp $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) $(SRC) test.cpp -o $@
