test: test-build
	./test

valgrind: test-build
	valgrind ./test

test-build:
	gcc -o test test.c

main: build
	./main

build:
	cppcheck --enable=all .
	gcc -o main main.c

clean:
	rm -f ./main ./test
