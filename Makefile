all:
	g++ src/*.cpp -o bin/tsp

win:
	x86_64-w64-mingw32-g++ -static src/*.cpp -o bin/tsp.exe

win32:
	i686-w64-mingw32-g++ -static src/*.cpp -o bin/tsp32.exe

.PHONY: clean
clean:
	rm bin/*
