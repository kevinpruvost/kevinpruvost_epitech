#! /bin/bash

yellow='\e[1;33m'
default='\e[0;37m'
red='\e[1;31m'
green='\e[1;32m'

bash .././bdsh -f file.json create database
bash .././bdsh -f file.json create table user id,firstname,lastname
bash .././bdsh -f file.json create table age id,age
bash .././bdsh -f file.json insert user id=1,firstname=John,lastname=SMITH
bash .././bdsh -f file.json insert user id=4,firstname=Robert\ John,lastname=WILLIAMS
bash .././bdsh -f file.json insert user id=2,firstname=Lisa,lastname=SIMPSON
bash .././bdsh -f file.json insert user id=10,lastname=SMITH
bash .././bdsh -f file.json insert user firstname=Laura,lastname=SMITH
bash .././bdsh -f file.json insert user id=9
bash .././bdsh -f file.json insert age id=1,age=42

bash .././bdsh -f file.json describe user >result

diff result describetest1 >diff_file
value=$(cat diff_file)

if [ "${value}" != "" ]; then
    echo -e "${red}Test failed${default}"
    echo -e "${red}Test failed${default}"
    echo -e "expected file:"
    cat describetest1
    echo -e "\n\nresulting file:"
    cat result
else
    echo -e "${green}Test succes${default}"
fi

rm result
rm diff_file

bash .././bdsh -f file.json "select" user lastname,firstname order >result

diff result describetest2 >diff_file
if [ $? != 0 ]; then
    echo -e "${red}Test failed${default}"
    echo -e "expected file:"
    cat describetest2
    echo -e "\n\nresulting file:"
    cat result
else
    echo -e "${green}Test succes${default}"
fi

rm diff_file
rm result

echo -e "${yellow}Test : wrong arguments with create function${default}"
bash .././bdsh -f file.json create
if [ $? = 1 ]; then
    echo -e "${green}Test succes${default}"
else
    echo -e "${red}Test failed${default}"
fi

bash .././bdsh -f file.json create databas
if [ $? = 1 ]; then
    echo -e "${green}Test succes${default}"
else
    echo -e "${red}Test failed${default}"
fi

bash .././bdsh -f file.json create table
if [ $? = 1 ]; then
    echo -e "${green}Test succes${default}"
else
    echo -e "${red}Test failed${default}"
fi

bash .././bdsh -f file.json create tabl
if [ $? = 1 ]; then
    echo -e "${green}Test succes${default}"
else
    echo -e "${red}Test failed${default}"
fi

echo -e "${yellow}Test : wrong arguments with insert function${default}"
bash .././bdsh -f file.json insert
if [ $? = 1 ]; then
    echo -e "${green}Test succes${default}"
else
    echo -e "${red}Test failed${default}"
fi

echo -e "${yellow}Test : files json${default}"
bash .././bdsh -f files describe user
if [ $? = 1 ]; then
    echo -e "${green}Test success${default}"
else
    echo -e "${red}Test failed${default}"
fi

bash .././bdsh describe user
if [ $? = 1 ]; then
    echo -e "${green}Test succes${default}"
else
    echo -e "${red}Test failed${default}"
fi

rm file.json

bash ../bdsh -f test.json describe age > result
diff result test_bd
if [ $? != 0 ]; then
    echo -e "${red}Test failed${default}"
    echo -e "expected file:"
    cat test_bd
    echo -e "\n\nresulting file:"
    cat result
else
    echo -e "${green}Test succes${default}"
fi