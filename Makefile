.SILENT:
all:
	meson setup build/
	meson compile -C build/
install:
	meson setup build/
	meson install -C build/
run:
	meson setup run/
	meson compile -C run/
	run/Pong_launcher
	rm -r run/
clean:
	rm build/ -rf
