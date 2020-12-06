cmake_minimum_required(VERSION 3.5)

project(UI LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

set(GUI_CLIENT_UI
    Contact.ui
    MainWindow.ui
    IncomingCallWindow.ui
    LoginForm.ui
)

set(GUI_CLIENT_RESOURCES
    Resources.qrc
)

set(GUI_CLIENT_FILES
    main.cpp
    ExternalIpGetter.cpp
    ExternalIpGetter.hpp
    ATcpSocket.cpp
    ATcpSocket.hpp
    ITcpSocket.hpp
    ProfileForm.cpp
    ProfileForm.hpp
    ProfileForm.ui
    LoginForm.cpp
    LoginForm.hpp
    NewConversionFromStdStringToQString.cpp
    NewConversionFromStdStringToQString.hpp
    QtConstants.hpp
    IncomingCallWindow.cpp
    IncomingCallWindow.hpp
    Contact.cpp
    Contact.hpp
    TcpSocket.cpp
    TcpSocket.hpp
    MainWindow.cpp
    MainWindow.hpp
    ${GUI_CLIENT_UI}
    ${GUI_CLIENT_RESOURCES}
)

if(ANDROID)
  add_library(UI SHARED
    ${GUI_CLIENT_FILES}
  )
else()
  add_executable(UI
    ${GUI_CLIENT_FILES}
  )
endif()

target_link_libraries(UI PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Network)

include_directories(UI PUBLIC ../../lib/ ../../lib/Babel/ ../)
