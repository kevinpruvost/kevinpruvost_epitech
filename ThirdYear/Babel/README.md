# Babel

The project consists of a client/server architecture voice over IP application, similar to Skype or TeamSpeak.

## Dependencies

### Windows

| Dependency         | Link / Command               |
| ------------------ | ---------------------------- |
| Python 3           | [Python 3]                   |
| Pip                | [pip]                        |
| Conan              | `pip3.exe install conan`     |
| CMake              | [CMake]                      |
| Qt Creator 5.14.2  | [Qt]                         |
| Doxygen (optional) | [Doxygen]                    |


[Python 3]: https://www.python.org/downloads/
[pip]: https://www.liquidweb.com/kb/install-pip-windows/
[CMake]: https://cmake.org/download/
[Qt]: https://download.qt.io/official_releases/qt/5.14/5.14.2/
[Doxygen]: https://www.doxygen.nl/download.html

:warning: **When installing Python 3, be sure to check "Add Python 3 to PATH" (to be able to launch commands).**

:warning: **After Qt is installed, be sure to add the path to the Qt's used compiler binaries to the environment variable PATH (in order to get access to windeployqt.exe).**

**Example : `C:/Qt/5.14.2/msvc2017_64/bin` ([Tutorial : Creating or Modifying environment variables])**

[Tutorial : Creating or Modifying environment variables]: https://docs.oracle.com/en/database/oracle/r-enterprise/1.5.1/oread/creating-and-modifying-environment-variables-on-windows.html#GUID-DD6F9982-60D5-48F6-8270-A27EC53807D0

### Unix

| Dependency    | Link / Command (Ubuntu)   |
| ------------- | ------------------------- |
| Python 3      | `apt install python3`     |
| Pip           | `apt install python3-pip` |
| Conan         | `pip install conan`       |
| CMake         | `apt install cmake`       |

## Setup & Build

First, we need to setup the project in order to build it,
then we simply build it (for both Windows and Unix Systems).

If you're interested for more details, Windows building process on this project
has more necessary steps, Qt on Windows manages dependencies differently and
so it needs an application that deploy applications (**windeployqt.exe**).

### Windows
```
$ ./windows_setup.bat
$ ./windows_build.bat
```

### Unix
```
$ ./unix_setup.sh
$ ./unix_build.sh
```

## Screenshots

### Login

<img src="https://github.com/kevinpruvost/kevinpruvost_epitech/blob/master/ThirdYear/Babel/screenshots/login.png"/>

### Empty Panel

<img src="https://github.com/kevinpruvost/kevinpruvost_epitech/blob/master/ThirdYear/Babel/screenshots/emptyInterface.png"/>

### Messages

<img src="https://github.com/kevinpruvost/kevinpruvost_epitech/blob/master/ThirdYear/Babel/screenshots/messaging.png"/>

### Call incoming

<img src="https://github.com/kevinpruvost/kevinpruvost_epitech/blob/master/ThirdYear/Babel/screenshots/calling.png"/>

### Calling

<img src="https://github.com/kevinpruvost/kevinpruvost_epitech/blob/master/ThirdYear/Babel/screenshots/call.png"/>
