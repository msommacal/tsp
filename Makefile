all:
	if [ ! -d bin ]; then mkdir bin; fi
	g++ src/*.cpp -o bin/tsp

win:
	if [ ! -d bin ]; then mkdir bin; fi
	x86_64-w64-mingw32-g++ -static src/*.cpp -o bin/tsp.exe

win32:
	if [ ! -d bin ]; then mkdir bin; fi
	i686-w64-mingw32-g++ -static src/*.cpp -o bin/tsp32.exe

.PHONY: doc
doc:
	doxygen doc/Doxyfile

.PHONY: clean
clean:
	rm -r bin
