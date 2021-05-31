zwirgio_lang.exe: zwm.o
	gcc zwm.o -o zwirgio_lang.exe

zwm.o: zwm.c
	gcc -c zwm.c -o zwm.o

clean:
	del *.o *.exe

run:
	./zwirgio_lang.exe
