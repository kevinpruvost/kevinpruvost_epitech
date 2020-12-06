@echo off
echo "Adding needed conan remotes..."

conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
conan remote add epitech-center https://api.bintray.com/conan/epitech/public-conan
conan remote add conan-center https://api.bintray.com/conan/conan/conan-center

:found
echo "Setting up the project into build/ ..."
mkdir build
cd build && conan install --build=missing -s compiler="Visual Studio" -s compiler.version=16 -s "arch=x86_64" -s "arch_build=x86_64" .. && cmake .. -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Release && echo "Setup Completed !"