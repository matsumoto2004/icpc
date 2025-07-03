#! /bin/bash

set -- `getopt s:c:g: $@`
while [ $1 != -- ]; do
    case $1 in
        -s ) g++-14 -std=gnu++20 -Wall -Wextra -Wfatal-errors -O2 -I . $2 -o solver ;;
        -c ) g++-14 -std=gnu++20 -Wall -Wextra -Wfatal-errors -O2 -I . $2 -o checker ;;
        -g ) g++-14 -std=gnu++20 -Wall -Wextra -Wfatal-errors -O2 -I . $2 -o generator ;;
    esac
    shift; shift
done

echo "compiled"

while true; do
    ./generator >input.txt
    ./solver <input.txt >>input.txt
    res=$(./checker <input.txt)
    if [ "$res" != "AC" ]; then
        echo "WA"
        echo "$res"
        exit
    fi
    echo "AC"
done

#ケース：input.txt
#WA出力：input.txt
#AC出力："WA"のあと

#あなたが実装すべきもの：
#・generator.cpp　テストケースの生成、出力を行う（小さめケースを生成するのがおすすめ）
#・solver.cpp　あなたの書いた、問題を解くコード（デバッグしたいコード）
#　generatorとsolverの出力はどちらもinput.txtになされます
#・checker.cpp　テストケースとsolver.cppの出力を受け取って、ACかどうか判定するコード（簡単に判定できるものは素直に判定を書く、愚直解が作れるならそれを作る、など）
#　checkerの出力は、WAなケースが見つかった時に"WA"の出力の後にターミナルへ書き込まれます

#使い方：
#ターミナルで bash randomtest.sh -s solver.cpp -g generator.cpp -c checker.cpp と書く