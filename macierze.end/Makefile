#
#  To sa opcje dla kompilacji
#
CXXFLAGS= -g -lm -std=c++11 -Iinc -Wall -pedantic

__start__: uklad_rownan
	./uklad_rownan

uklad_rownan: obj/main.o obj/LZespolone.o
	g++ ${CXXFLAGS} -o uklad_rownan obj/main.o obj/LZespolone.o

obj/main.o: src/main.cpp inc/UkladRownanLiniowych.hh inc/LZespolone.hh inc/Macierz.hh inc/rozmiar.h inc/Wektor.hh
	g++ ${CXXFLAGS} -o obj/main.o -c src/main.cpp

obj/LZespolone.o: src/LZespolone.cpp inc/LZespolone.hh
	g++ ${CXXFLAGS} -o obj/LZespolone.o -c src/LZespolone.cpp

clean:
	rm -f obj/*.o uklad_rownan
