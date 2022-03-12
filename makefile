all: memorized.exe dynamic.exe

memorized.exe: memorized.o
	g++ -o memorized.exe memorized.o
	rm memorized.o
memorized.o: memorized.cpp
	g++ -std=c++11 -Wall -Wextra -c memorized.cpp

dynamic.exe: dynamic.o
	g++ -o dynamic.exe dynamic.o
	rm dynamic.o
dynamic.o: dynamic.cpp
	g++ -std=c++11 -Wall -Wextra -c dynamic.cpp
