# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

all: release-all

cmake-debug:
	mkdir -p build/debug
	cd build/debug && cmake -D CMAKE_BUILD_TYPE=Debug ../..

debug: cmake-debug
	cd build/debug && $(MAKE)

# Temporarily disable some tests:
#  * libwallet_api_tests fail (Issue #895)
debug-test:
	mkdir -p build/debug
	cd build/debug && cmake -D BUILD_TESTS=ON -D CMAKE_BUILD_TYPE=Debug ../.. &&  $(MAKE) && $(MAKE) ARGS="-E libwallet_api_tests" test

debug-all:
	mkdir -p build/debug
	cd build/debug && cmake -D BUILD_TESTS=ON -D BUILD_SHARED_LIBS=OFF -D CMAKE_BUILD_TYPE=Debug ../.. && $(MAKE)

debug-static-all:
	mkdir -p build/debug
	cd build/debug && cmake -D BUILD_TESTS=ON -D STATIC=ON -D CMAKE_BUILD_TYPE=Debug ../.. && $(MAKE)

cmake-release:
	mkdir -p build/release
	cd build/release && cmake -D CMAKE_BUILD_TYPE=Release ../..

release: cmake-release
	cd build/release && $(MAKE)

release-test:
	mkdir -p build/release
	cd build/release && cmake -D BUILD_TESTS=ON -D CMAKE_BUILD_TYPE=release ../.. && $(MAKE) && $(MAKE) test

release-all:
	mkdir -p build/release
	cd build/release && cmake -D BUILD_TESTS=ON -D CMAKE_BUILD_TYPE=release ../.. && $(MAKE)

release-static:
	mkdir -p build/release
	cd build/release && cmake -D STATIC=ON -D ARCH="x86-64" -D BUILD_64=ON -D CMAKE_BUILD_TYPE=release ../.. && $(MAKE)

coverage:
	mkdir -p build/debug
	cd build/debug && cmake -D BUILD_TESTS=ON -D CMAKE_BUILD_TYPE=Debug -D COVERAGE=ON ../.. && $(MAKE) && $(MAKE) test

# Targets for specific prebuilt builds which will be advertised for updates by their build tag

release-static-linux-armv6:
	mkdir -p build/release
	cd build/release && cmake -D BUILD_TESTS=OFF -D ARCH="armv6zk" -D STATIC=ON -D BUILD_64=OFF -D CMAKE_BUILD_TYPE=release -D BUILD_TAG="linux-armv6" ../.. && $(MAKE)

release-static-linux-armv7:
	mkdir -p build/release
	cd build/release && cmake -D BUILD_TESTS=OFF -D ARCH="armv7-a" -D STATIC=ON -D BUILD_64=OFF -D CMAKE_BUILD_TYPE=release -D BUILD_TAG="linux-armv7" ../.. && $(MAKE)

release-static-android:
	mkdir -p build/release
	cd build/release && cmake -D BUILD_TESTS=OFF -D ARCH="armv7-a" -D STATIC=ON -D BUILD_64=OFF -D CMAKE_BUILD_TYPE=release -D ANDROID=true -D INSTALL_VENDORED_LIBUNBOUND=ON -D BUILD_TAG="android" ../.. && $(MAKE)

release-static-linux-armv8:
	mkdir -p build/release
	cd build/release && cmake -D BUILD_TESTS=OFF -D ARCH="armv8-a" -D STATIC=ON -D BUILD_64=ON -D CMAKE_BUILD_TYPE=release -D BUILD_TAG="linux-armv8" ../.. && $(MAKE)

release-static-linux-x86_64:
	mkdir -p build/release
	cd build/release && cmake -D STATIC=ON -D ARCH="x86-64" -D BUILD_64=ON -D CMAKE_BUILD_TYPE=release -D BUILD_TAG="linux-x64" ../.. && $(MAKE)

release-static-freebsd-x86_64:
	mkdir -p build/release
	cd build/release && cmake -D STATIC=ON -D ARCH="x86-64" -D BUILD_64=ON -D CMAKE_BUILD_TYPE=release -D BUILD_TAG="freebsd-x64" ../.. && $(MAKE)

release-static-mac-x86_64:
	mkdir -p build/release
	cd build/release && cmake -D STATIC=ON -D ARCH="x86-64" -D BUILD_64=ON -D CMAKE_BUILD_TYPE=release -D BUILD_TAG="mac-x64" ../.. && $(MAKE)

release-static-linux-i686:
	mkdir -p build/release
	cd build/release && cmake -D STATIC=ON -D ARCH="i686" -D BUILD_64=OFF -D CMAKE_BUILD_TYPE=release -D BUILD_TAG="linux-x86" ../.. && $(MAKE)

release-static-win64:
	mkdir -p build/release
	cd build/release && cmake -G "MSYS Makefiles" -D STATIC=ON -D ARCH="x86-64" -D BUILD_64=ON -D CMAKE_BUILD_TYPE=Release -D BUILD_TAG="win-x64" -D CMAKE_TOOLCHAIN_FILE=../../cmake/64-bit-toolchain.cmake -D MSYS2_FOLDER=c:/msys64 ../.. && $(MAKE)

release-static-win32:
	mkdir -p build/release
	cd build/release && cmake -G "MSYS Makefiles" -D STATIC=ON -D ARCH="i686" -D BUILD_64=OFF -D CMAKE_BUILD_TYPE=Release -D BUILD_TAG="win-x32" -D CMAKE_TOOLCHAIN_FILE=../../cmake/32-bit-toolchain.cmake -D MSYS2_FOLDER=c:/msys32 ../.. && $(MAKE)

fuzz:
	mkdir -p build/fuzz
	cd build/fuzz && cmake -D STATIC=ON -D SANITIZE=ON -D BUILD_TESTS=ON -D USE_LTO=OFF -D CMAKE_C_COMPILER=afl-gcc -D CMAKE_CXX_COMPILER=afl-g++ -D ARCH="x86-64" -D CMAKE_BUILD_TYPE=fuzz -D BUILD_TAG="linux-x64" ../.. && $(MAKE)

clean:
	@echo "WARNING: Back-up your wallet if it exists within ./build!" ; \
        read -r -p "This will destroy the build directory, continue (y/N)?: " CONTINUE; \
	[ $$CONTINUE = "y" ] || [ $$CONTINUE = "Y" ] || (echo "Exiting."; exit 1;)
	rm -rf build

tags:
	ctags -R --sort=1 --c++-kinds=+p --fields=+iaS --extra=+q --language-force=C++ src contrib tests/gtest

.PHONY: all cmake-debug debug debug-test debug-all cmake-release release release-test release-all clean tags
