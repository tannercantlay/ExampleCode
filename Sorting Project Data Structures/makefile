main: main.o Sorting.o Sorting.h
        g++ -o main main.o Sorting.o
main.o: main.cpp Sorting.h
        g++ -c main.cpp
Sorting.o: Sorting.cpp Sorting.h
        g++ -c Sorting.cpp
clean:
        rm ./*.o
