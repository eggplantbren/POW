default:
	g++ -I . -std=c++2a -O3 -march=native -Wall -Wextra -pedantic -c *.cpp
	g++ -o main main.o
	rm -f *.o
