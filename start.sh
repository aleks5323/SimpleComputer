#!/bin/bash
function jumpto
{
    label=$1
    cmd=$(sed -n "/$label:/{:a;n;p;ba};" $0 | grep -v ':$')
    eval "$cmd"
    exit
}
make -s

clean:
echo -e "\e[31m\e[1mWould you like to clean up the mess?"
read -p "y/n: " a
echo -e "\e[0m"
case $a in
	y|Y) make -s clean ; clear ;;
	n|N) exit ;;
	*) jumpto clean ;;
esac
