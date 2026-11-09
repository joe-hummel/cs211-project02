SHELL := /bin/bash

build:
	rm -f ./a.out
	g++ -std=c++20 -g -Wall -pedantic -Werror main.cpp pgutil.cpp nupython.o -lm -Wno-psabi -Wno-unused-variable -Wno-unused-function -Wno-write-strings

test: gtest.o
	rm -f ./a.out
	g++ -std=c++20 -g -Wall -DUNIT_TEST -pedantic -Werror testsmain.cpp pgutil.cpp nupython.o gtest.o -I. -lm -lpthread -Wno-psabi -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable -Wno-write-strings

gtest.o:
	@echo "**Building googletest, just need to do this once**"
	pushd ./googletest/src && \
	g++ -std=c++20 -g -c gtest-all.cc -I. && \
	ld -relocatable gtest-all.o -o gtest.o && \
	cp gtest.o ../.. && \
	popd

run:
	./a.out

valgrind:
	rm -f ./a.out
	g++ -std=c++20 -g -Wall -pedantic -Werror main.cpp pgutil.cpp nupython.o -lm -Wno-psabi -Wno-unused-variable -Wno-unused-function -Wno-write-strings
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./a.out "$(file)"

testvalgrind: gtest.o
	rm -f ./a.out
	g++ -std=c++20 -g -Wall -DUNIT_TEST -pedantic -Werror testsmain.cpp pgutil.cpp nupython.o gtest.o -I. -lm -lpthread -Wno-psabi -Wno-unused-variable -Wno-unused-function -Wno-write-strings
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./a.out "$(file)"

clean:
	rm -f ./a.out
  
submit:
	/gradescope/gs submit 1396807 9025911 main.cpp pgutil.*

commit:
	git add .
	git commit -m "$(msg)"

push:
	git push origin main

nupython:
	rm -f execute.o parser.o programgraph.o ram.o scanner.o tokenqueue.o nupython.o
	gcc -std=c11 -c -w -Wall execute.c
	gcc -std=c11 -c -w -Wall parser.c
	gcc -std=c11 -c -w -Wall programgraph.c
	gcc -std=c11 -c -w -Wall ram.c
	gcc -std=c11 -c -w -Wall scanner.c
	gcc -std=c11 -c -w -Wall tokenqueue.c
	ld -relocatable execute.o parser.o programgraph.o ram.o scanner.o tokenqueue.o -o nupython.o
	rm -f execute.o parser.o programgraph.o ram.o scanner.o tokenqueue.o
