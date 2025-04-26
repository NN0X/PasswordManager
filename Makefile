CXX = clang++
CFLAGS = -O3 -Wall -Wextra -Wpedantic
LDFLAGS = -lX11
SRC = src
OUT = main

all:
	rm -f -r build
	mkdir build
	$(CXX) $(CFLAGS) $(SRC)/*.cpp -o build/$(OUT) $(LDFLAGS) 2> build/make.log
	cp -r data build/data
	@echo "Build complete. Executable is located at build/$(OUT)"
