all:
	windres info.rc -O coff -o info.res
	gcc `pkg-config gtk+-3.0 --cflags` main.c `pkg-config gtk+-3.0 --libs` info.res -o main.exe
run:
	./main.exe
clean:
	rm info.res
remove:
	rm main.exe score.txt info.res
