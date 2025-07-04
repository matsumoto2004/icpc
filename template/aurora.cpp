#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i,n) for(ll i=0;i<ll(n);i++)
#define rep2(i,m,n) for(ll i=ll(m);i<ll(n);i++)
using vl = vector<ll>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
using pl = pair<ll,ll>;
using vpl = vector<pl>;
using vvpl = vector<vpl>;
#define pb push_back

const long double EPS = 0.0000000001;
const ll INF = 1000000000000000000;
const double pi = std::acos(-1.0);

__int128 read_int128(){ //__int128を入力する
    string S;
    cin >> S;
    int N = S.size();
    int st = 0;
    bool minus = false;
    if(S[0] == '-'){
        minus = true;
        st = 1;
    }
    __int128 res = 0;
    rep2(i,st,N) res = res*10+int(S[i]-'0');
    if(minus) res *= -1;
    return res;
}

std::ostream &operator<<(std::ostream &dest, __int128_t value) { //これでcoutで__int128を出力できるように
    std::ostream::sentry s(dest);
    if (s) {
      __uint128_t tmp = value < 0 ? -value : value;
      char buffer[128];
      char *d = std::end(buffer);
      do {
          --d;
          *d = "0123456789"[tmp % 10];
          tmp /= 10;
      } while (tmp != 0);
      if (value < 0) {
          --d;
          *d = '-';
      }
      int len = std::end(buffer) - d;
      if (dest.rdbuf()->sputn(d, len) != len) {
          dest.setstate(std::ios_base::badbit);
      }
    }
    return dest;
}

void Yes(){ cout << "Yes" << endl; } //文字列"Yes"を標準出力
void No(){ cout << "No" << endl; } //文字列"No"を標準出力

template<class T> bool chmin(T& a,T b){
    if(a > b){
        a = b;
        return true;
    }
    else return false;
}

template<class T> bool chmax(T& a,T b){
    if(a < b){
        a = b;
        return true;
    }
    else return false;
}

int main(){
    
}