.PHONY: clean stat

all: directories ut_all


TEST = test/ut_node.h \
		test/ut_file.h \
		test/ut_folder.h \
		test/ut_null_iterator.h \
		test/ut_iterator.h
		

SRC  = src/node.h \
		src/node.h \
		src/folder.h \
		src/null_iterator.h \
		src/iterator.h

ITERATOR = obj/iterator.o

ut_all: test/ut_all.cpp $(TEST) $(SRC) $(ITERATOR)
	g++ -std=c++11 test/ut_all.cpp $(ITERATOR) -o bin/ut_all -lgtest -lpthread

obj/iterator.o: src/iterator.h src/iterator.cpp
	g++ -std=c++11 -c src/iterator.cpp -o obj/iterator.o


directories:
	mkdir -p bin
	mkdir -p obj

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