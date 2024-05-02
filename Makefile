.SILENT:
all:
	meson setup builddir/
	meson compile -C builddir/
install:
	meson setup builddir/
	meson install -C builddir/
run: all
	builddir/Pong_launcher
clean:
	rm builddir/ -rf
