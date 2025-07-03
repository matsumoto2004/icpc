#ifndef LOGX
#include<bits/stdc++.h>
#endif
//check関数でのオーバーフローに気をつける.
template<class T,class func>
T b_search(T ok,T ng,func check,int cnt=300){
    assert(check(ok) && !check(ng));
    if(typeid(T)==typeid(int) || typeid(T)==typeid(long long)){//整数値二分探索
        while(ok-ng>1 || ng-ok>1){
            T mid=(ok+ng)/2;
            if(check(mid))ok=mid;
            else ng=mid;
        }
        return ok;
    }
    else{
        while(cnt--){
            T mid=(ok+ng)/2;
            if(check(mid))ok=mid;
            else ng=mid;
        }
        return ok;
    }
}