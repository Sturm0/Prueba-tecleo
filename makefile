.PHONY: clean

VERSION = 1.0
NAME = Prueba-tecleo
DISTDIR = $(NAME)-$(VERSION)

Main: Main.cpp clean
	g++ -o $@  $< $(shell pkg-config --libs --cflags ncursesw) -DTEST --debug -g
clean:
	rm -f Main

dist:
	mkdir -p $(DISTDIR)
	cp Main.cpp makefile README.md LICENSE $(DISTDIR)
	tar -czvf $(DISTDIR).tar.gz $(DISTDIR)
	rm -r $(DISTDIR)
