#!/bin/bash

# 编译脚本

flag=""

help() {
    echo "./compile [argv]
        argv可取:
            verbose:打印详细信息"
}

for arg in $*;
do
    if [[ ${arg} =~ "help" ]]
    then
        help
        exit
    elif [[ ${arg} =~ "verbose" ]]
    then
        flag+=" VERBOSE=1"
    fi
done

[ -d "build" ] || mkdir build

# 编译命令
cd build && cmake .. && make -j4 ${flag}

if [[ ${flag} == "" ]]
then
    help
fi


