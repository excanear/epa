.PHONY: setup build run test clean

setup:
	scripts/setup.sh

build:
	scripts/build.sh

run:
	scripts/run-qemu.sh

test:
	tests/smoke/boot_smoke.sh

clean:
	rm -rf build
