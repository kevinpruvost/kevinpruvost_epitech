conan remote add conan-center https://api.bintray.com/conan/conan/conan-center
conan remote add epitech-center https://api.bintray.com/conan/epitech/public-conan
conan remote add bincrafters-center https://api.bintray.com/conan/bincrafters/public-conan

mkdir -p build && cd build && conan install ../conanfileLinux.txt --build=missing && cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release