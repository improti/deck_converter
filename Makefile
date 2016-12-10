all:
	g++  -c  "Card.cpp" -g -O0 -Wall -std=c++11  -o Card.cpp.o -I.
	g++  -c  "DeckUtils.cpp" -g -O0 -Wall -std=c++11  -o DeckUtils.cpp.o -I.
	g++  -c  "Deck.cpp" -g -O0 -Wall -std=c++11  -o Deck.cpp.o -I.
	g++  -c  "Mdb.cpp" -g -O0 -Wall -std=c++11  -o Mdb.cpp.o -I.
	g++  -c  "main.cpp" -g -O0 -Wall -std=c++11  -o main.cpp.o -I.
	g++ -pthread -std=c++11 main.cpp.o Deck.cpp.o Card.cpp.o DeckUtils.cpp.o Mdb.cpp.o -lsqlite3 -ldl -o deck_converter
  
clean:
	rm *.o
	rm deck_converter
