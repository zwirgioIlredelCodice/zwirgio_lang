zwirgio_lang.exe: main.o  zwm.o 
	gcc main.o  zwm.o  -o zwirgio_lang.exe

main.o: main.c
	gcc -c main.c -o main.o

zwm.o: zwm.c
	gcc -c zwm.c -o zwm.o

clean:
	del *.o *.exe

run:
	./zwirgio_lang.exe