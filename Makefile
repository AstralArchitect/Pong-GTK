.SILENT:
all:
	meson setup build/
	meson compile -C build/
install:
	meson setup build/
	meson install -C build/
run:
	make
	build/Pong_launcher
clean:
	rm build/ -rf
