mkdir build
cd build
cmake -DINNO_PLATFORM_WIN32=ON -DINNO_PLATFORM_WIN64=OFF -DINNO_PLATFORM_LINUX64=OFF -G "Visual Studio 15" ../source
cmake -DINNO_PLATFORM_WIN32=ON -DINNO_PLATFORM_WIN64=OFF -DINNO_PLATFORM_LINUX64=OFF -G "Visual Studio 15" ../source
msbuild InnocenceEngine.sln