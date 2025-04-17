all: resources coinflip

resources: resources.geresource.xml
	glib-compile-resources --generate-source resources.geresource.xml

coinflip: main.c
	gcc `pkg-config --cflags gtk4` main.c resources.geresource.c -o bin/coinflip `pkg-config --libs gtk4`

test:
	valgrind ./bin/coinflip

run:
	./bin/coinflip

clean:
	rm resources.geresource.c
	rm -v bin/*

install:
	mkdir /opt/coinflipper
	cp -r bin /opt/coinflipper
	cp coinflipper.desktop /usr/share/applications/coinflipper.desktop