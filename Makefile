.PHONY: all test clean

all: code

# This problem submits a header, which the judge includes in its test harness.
code: str.hpp
	cp str.hpp code

test:
	$(CXX) -std=c++11 -Wall -Wextra -Werror -pedantic -g -fsanitize=address,undefined -I. tests/str_test.cpp -o str_test
	./str_test

clean:
	rm -f code str_test
