alias g='g++ -std=gnu++20 -Wfatal-errors -O2 -I /System/Volumes/Data/home/6448374050/Documents/icpc'
alias dbg='g -DLOGX'

function uz(){
    command unzip input/samples-$1.zip -d input/$1
}
function a() {
    command ./a.out < input/$1/$2.in
}
