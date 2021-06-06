zwirgio_lang.exe: main.o  zwm.o zwassembly.o
	gcc main.o  zwm.o zwassembly.o -o zwirgio_lang.exe

main.o: main.c
	gcc -c main.c -o main.o

zwm.o: zwm.c
	gcc -c zwm.c -o zwm.o

zwassembly.o: zwassembly.c
	gcc -c zwassembly.c -o zwassembly.o

clean:
	del *.o *.exe

run:
	./zwirgio_lang.exe