# DESCRIPTION
The Gomoku project is an AI meant to beat every players on the 'Gomoku' game, a sort of a 'Connect 4' but it's a 'Connect 5' and there's no 'gravity' rules so you can place a coin wherever you want.<br/>
We used the Min-Max algorithm mixed with some n-ary trees algorithms and other things to optimize it.

# INSTALL
Python 3: https://www.python.org/downloads/  
piskvork: https://sourceforge.net/projects/piskvork/  

# COMPILE
    make
    make clean
    make fclean
    make re
On windows the makefile create an executable(.exe) using pyinstaller.  
On linux it simply copy&rename "./main.py" to "./pbrain-gomoku-ai"

# EXECUTE
    ./piskvork -p pbrain-program1.exe pbrain-program2.exe
    
Ou directement depuis le logiciel piskvork

# SCREENSHOTS IN ACTION

<img src="https://github.com/kevinpruvost/kevinpruvost_epitech/blob/master/ThirdYear/Gomoku/screenshots/capture1.PNG"/>
<img src="https://github.com/kevinpruvost/kevinpruvost_epitech/blob/master/ThirdYear/Gomoku/screenshots/capture2.PNG"/>

# DOCUMENTATION
piskvork: https://svn.code.sf.net/p/piskvork/code/trunk/source/doc/protocl2en.htm  
ou alors ici pour vous peter les yeux: http://petr.lastovicka.sweb.cz/protocl2en.htm

# OTHERS
Un repo contenant des IAs ayants participées au dernières competitions de Gomoku:  
https://github.com/Gomocup/GomocupDownload  

AI evaluation function is based on this report:  
https://linyanghe.github.io/projects/resources/Gomuku.pdf

Papers:  
https://lib.dr.iastate.edu/cgi/viewcontent.cgi?article=1491&context=creativecomponents  
https://www.diva-portal.org/smash/get/diva2:823737/FULLTEXT01.pdf  
https://stanford-cs221.github.io/autumn2019-extra/posters/14.pdf  
