.PHONY: clean stat

all: directories ut_all


TEST = test/ut_node.h
		

SRC  = src/node.h

ut_all: test/ut_all.cpp $(TEST) $(SRC)
	g++ -std=c++11 test/ut_all.cpp -o bin/ut_all -lgtest -lpthread

directories:
	mkdir -p bin

clean:
	rm -f bin/*

stat:
	wc src/* test/*

test: all
	bin/ut_all


# valgrind: CXXFLAGS += -O0 -g
valgrind: clean all
	valgrind \
	--tool=memcheck --error-exitcode=1 --track-origins=yes --leak-check=full --leak-resolution=high \
	--num-callers=50 --show-leak-kinds=definite,possible --show-error-list=yes \
	bin/ut_all 