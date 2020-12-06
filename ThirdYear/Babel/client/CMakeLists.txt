# CMakeList.txt : projet CMake pour Babel, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Source code of UI
set(GUI_CLIENT_SOURCES
    UI/MainWindow.cpp
				UI/Contact.cpp
				UI/IncomingCallWindow.cpp
				UI/NewConversionFromStdStringToQString.cpp
                UI/ClientConfig.cpp
				UI/LoginForm.cpp
				UI/TcpSocket.cpp
				UI/ProfileForm.cpp
				UI/ATcpSocket.cpp
				UI/ExternalIpGetter.cpp
)

set(GUI_CLIENT_HEADERS
				UI/QtConstants.hpp
    UI/MainWindow.hpp
				UI/Contact.hpp
				UI/IncomingCallWindow.hpp
				UI/NewConversionFromStdStringToQString.hpp
                UI/ClientConfig.hpp
				UI/LoginForm.hpp
				UI/TcpSocket.hpp
				UI/ProfileForm.hpp
				UI/ATcpSocket.hpp
				UI/ITcpSocket.hpp
				UI/ExternalIpGetter.hpp
)

set(GUI_CLIENT_UI
    UI/MainWindow.ui
				UI/Contact.ui
				UI/IncomingCallWindow.ui
				UI/LoginForm.ui
				UI/ProfileForm.ui
)

set(GUI_CLIENT_RESOURCES
				UI/Resources.qrc
)

qt5_wrap_cpp(GUI_CLIENT_SOURCES ${GUI_CLIENT_HEADERS})
qt5_wrap_ui(GUI_CLIENT_SOURCES ${GUI_CLIENT_UI})
qt5_add_resources(GUI_CLIENT_SOURCES ${GUI_CLIENT_RESOURCES})

include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_BINARY_DIR})

# Ajoutez une source à l'exécutable de ce projet.
add_executable (babel_client
				main.cpp
				Client.hpp
				VOIP.cpp
				VOIP.hpp
				Compressor.cpp
				Compressor.hpp
				AudioBuffer.cpp
				AudioBuffer.hpp
				AudioStream.hpp
				AudioStream.cpp
				${GUI_CLIENT_SOURCES}
)

target_include_directories(babel_client PUBLIC
				UI/
)

target_link_libraries(babel_client PRIVATE
				CONAN_PKG::boost
				CONAN_PKG::portaudio
				CONAN_PKG::opus
)

if (UNIX)
target_link_libraries(babel_client PRIVATE
				CONAN_PKG::libalsa
)
endif (UNIX)

target_link_libraries(babel_client PRIVATE
				Qt5::Widgets
				Qt5::Core
				Qt5::Gui
				Qt5::Network
)

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
