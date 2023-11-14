.PHONY: clean dirs

CFLAGS = -std=c++11 -Wfatal-errors -Wall 
LIBS = -lgtest -lpthread


UT_ALL = test/ut_all.cpp

TEST_HEADERS = test/ut_node.h \
				test/ut_file.h \
				test/ut_folder.h \
				test/ut_null_iterator.h \
				test/ut_iterator.h \
				test/ut_dfs_iterator.h \
				test/ut_bfs_iterator.h \
				test/ut_find_by_name_visitor.h \
				test/ut_stream_out_visitor.h \
				test/ut_order_by_name_iterator.h \
				test/ut_tree_visitor.h \
				test/ut_scanner.h \
				test/ut_builder.h

SRC_HEADERS = src/node.h \
				src/folder.h \
				src/null_iterator.h \
				src/iterator.h \
				src/dfs_iterator.h \
				src/find_by_name_visitor.h \
				src/stream_out_visitor.h \
				src/tree_visitor.h \
				src/file_system_scanner.h \
				src/file_system_builder.h


all: dirs bin/ut_all

bin/ut_all: $(UT_ALL) $(TEST_HEADERS) $(SRC_HEADERS) 
	g++ $(CFLAGS) -o $@ $<  $(LIBS)

clean:
	rm -rf bin obj

dirs:
	mkdir -p bin obj

valgrind: clean all
	valgrind \
	--tool=memcheck --error-exitcode=1 --track-origins=yes --leak-check=full --leak-resolution=high \
	--num-callers=50 --show-leak-kinds=definite,possible --show-error-list=yes \
	bin/ut_all 
