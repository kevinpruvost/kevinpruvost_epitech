greaterThan(QT_MAJOR_VERSION, 4):

QT       += core gui widgets

TARGET = MyGKrellm

CONFIG += c++17

SOURCES += MainWindow.cpp \
    main.cpp \
    Htop.cpp \
    Try.cpp \
    display/NCurses.cpp \
    modules/CPUModule.cpp \
    modules/KernelModule.cpp \
    modules/NetworkModule.cpp \
    modules/ProcessModule.cpp \
    modules/RamModule.cpp \
    modules/SwapModule.cpp \
    modules/TimeModule.cpp \
    modules/UserModule.cpp \
    qtmodules/QtCPUModule.cpp \
    qtmodules/QtKernelModule.cpp \
    qtmodules/QtNetworkModule.cpp \
    qtmodules/QtProcessModule.cpp \
    qtmodules/QtRamModule.cpp \
    qtmodules/QtSwapModule.cpp \
    qtmodules/QtTimeModule.cpp \
    qtmodules/QtUserModule.cpp \

HEADERS += \
    Htop.hpp \
    MainWindow.hpp \
    display/NCurses.hpp \
    display/IMonitorDisplay.hpp \
    modules/CPUModule.hpp \
    modules/IMonitorModule.hpp \
    modules/KernelModule.hpp \
    modules/NetworkModule.hpp \
    modules/ProcessModule.hpp \
    modules/RamModule.hpp \
    modules/SwapModule.hpp \
    modules/TimeModule.hpp \
    modules/UserModule.hpp \ \
    qtmodules/QtCPUModule.hpp \
    qtmodules/QtKernelModule.hpp \
    qtmodules/QtNetworkModule.hpp \
    qtmodules/QtProcessModule.hpp \
    qtmodules/QtRamModule.hpp \
    qtmodules/QtSwapModule.hpp \
    qtmodules/QtTimeModule.hpp \
    qtmodules/QtUserModule.hpp \

FORMS += \
    MainWindow.ui \
    qtmodules/QtCPUModule.ui \
    qtmodules/QtKernelModule.ui \
    qtmodules/QtNetworkModule.ui \
    qtmodules/QtProcessModule.ui \
    qtmodules/QtRamModule.ui \
    qtmodules/QtSwapModule.ui \
    qtmodules/QtTimeModule.ui \
    qtmodules/QtUserModule.ui \

LIBS += -L/usr/local/lib -lncurses
