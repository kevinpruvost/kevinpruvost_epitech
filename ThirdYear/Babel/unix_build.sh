# /!\ Be sure to launch conan_configure.sh
# Creating build folder, installing conan dependencies & building with cmake
#
# If you struggle the process, check your packages, your python dependencies

cd build && cmake --build . --target all && cd - && cp build/bin/babel_client ./ && cp build/bin/babel_server ./