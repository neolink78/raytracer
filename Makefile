PRESET ?= unix-debug

.PHONY: build run test clean

build:
	cmake --preset $(PRESET)
	cmake --build --preset $(PRESET)

run: build
	./build/$(PRESET)/raytracer

test: build
	ctest --preset $(PRESET)

clean:
	rm -rf build/$(PRESET)
