.PHONY: clean
Main: Main.cpp clean
	g++ -o ./Compilado/$@  $< -lncursesw -DTEST --debug -g
clean:
	rm -f Main
