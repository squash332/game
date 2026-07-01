.PHONY: build run clean
build:
	cmake -S . -B build -G Ninja
	cmake --build build -j$(shell nproc)

run: build
	./build/game

clean:
	rm -rf build