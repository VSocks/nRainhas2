output: nRainhas2.o
	gcc nRainhas2.o -o nRainhas2

nRainhas.o: nRainhas2.c
	gcc -c nRainhas2.c

clean:
	rm *.o nRainhas2