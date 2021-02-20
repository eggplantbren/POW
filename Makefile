FLAGS = -I . -I /home/brewer/local/poco/Crypto/include -I /home/brewer/local/poco/Foundation/include -std=c++2a -O3 -march=native -Wall -Wextra -pedantic

LINKDIR = /home/brewer/local/poco/lib/Linux/x86_64

default:
	g++ $(FLAGS) -c *.cpp
	g++ -L $(LINKDIR) -o main main.o -lPocoFoundation -lPocoCrypto
	rm -f *.o
