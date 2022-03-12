all: memoized.exe dynamic.exe

memoized.exe: memoized.o
	g++ -o memoized.exe memoized.o
	rm memoized.o
memorized.o: memoized.cpp
	g++ -std=c++11 -Wall -Wextra -c memoized.cpp

dynamic.exe: dynamic.o
	g++ -o dynamic.exe dynamic.o
	rm dynamic.o
dynamic.o: dynamic.cpp
	g++ -std=c++11 -Wall -Wextra -c dynamic.cpp
