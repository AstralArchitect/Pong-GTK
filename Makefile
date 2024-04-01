all:
	windres my.rc -O coff -o my.res
	gcc `pkg-config gtk+-3.0 --cflags` main.c `pkg-config gtk+-3.0 --libs` my.res -o main.exe
run:
	./main.exe
