#!/bin/sh
mkdir build
cd build
cmake -DINNO_PLATFORM_WIN32=OFF -DINNO_PLATFORM_WIN64=OFF -DINNO_PLATFORM_LINUX64=OFF -DINNO_PLATFORM_MACOS=ON -G "Xcode" ../source
cmake -DINNO_PLATFORM_WIN32=OFF -DINNO_PLATFORM_WIN64=OFF -DINNO_PLATFORM_LINUX64=OFF -DINNO_PLATFORM_MACOS=ON -G "Xcode" ../source

