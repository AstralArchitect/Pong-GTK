.SILENT:
all:
	meson compile -C builddir/
run:
	meson compile -C .rundata/
	.rundata/Pong_launcher
clean:
	rm builddir/ -rf
	rm .rundata/ -rf
setup:
	meson setup builddir/
	meson setup .rundata/