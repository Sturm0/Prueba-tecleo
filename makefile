.PHONY: clean
Main: Main.cpp clean
	g++ -o ./Compilado/$@  $< $(shell pkg-config --libs --cflags ncursesw) -DTEST --debug -g
clean:
	rm -f Main
