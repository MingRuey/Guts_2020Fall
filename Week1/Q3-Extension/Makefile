test: test-build
	./test_node

valgrind: test-build
	valgrind ./test_node

test-build:
	cppcheck --enable=all .
	gcc -o test_node test_node.c

shuffle:shuffle-build
	./test_shuffle

valgrind-shuffle: shuffle-build
	./test_shuffle

shuffle-build:
	cppcheck --enable=all .
	gcc -o test_shuffle test_shuffle.c

main: build
	./main

build:
	cppcheck --enable=all .
	gcc -o main main.c

clean:
	rm -f main test_node test_shuffle
