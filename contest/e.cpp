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

typedef string::const_iterator State;



const ll MOD = 998244353;
map<string, int> var_to_ind;
vector<int> value; // TF は 01, 未定は -1
ll det_cnt = 0; // 「現時点で既定」の個数
ll var_cnt = 0; // 変数全体の個数、定数
ll ans = 0;

vector<ll> pow2;

string var(State &begin){
    string res = "";
    assert(islower(*begin));
    while(islower(*begin)){
        res += *begin;
        begin++;
    }
    return res;
}

// 一桁までしかない
int number(State &begin){
    return *(begin++) - '0';
}


void expression(State &begin, bool gomi = false){
    if(isdigit(*begin)){
        // そこに到達する方法 * number
        if(!gomi)(ans += pow2[var_cnt - det_cnt] * number(begin) % MOD) %= MOD;
        else{
            begin++;
        }
    }
    else{
        // "if_"
        rep(i,3)begin++;
        // var
        int var_idx = var_to_ind[var(begin)];
        bool not_det = value[var_idx] == -1;
        if(not_det)det_cnt += 1;

        // "_then_"
        rep(i,6)begin++;
        if(not_det){
            value[var_idx] = 1;
            
        }
        expression(begin, gomi | !value[var_idx]);
        
        // "_else_"
        rep(i,6)begin++;
        if(not_det){
            value[var_idx] = 0;
        }
        expression(begin, gomi | value[var_idx]);

        if(not_det){
            value[var_idx] = -1;
            det_cnt -= 1;
        }
    }
}

// 変数の個数を数えるだけ
void expression_for_count(State &begin){
    if(isdigit(*begin)){
        begin++;
        return;
    }
    else{
        // "if_"
        rep(i,3)begin++;
        // 変数名
        string varname = var(begin);
        if(!var_to_ind.count(varname)){
            var_to_ind[varname] = var_to_ind.size();
        }

        // "_then_"
        rep(i,6)begin++;
        expression_for_count(begin);
        // "_else_"
        rep(i,6)begin++;
        expression_for_count(begin);

        return;
    }
}

int main(){
    string e;
    cin >> e;

    // 変数数える
    State begin = e.begin();
    expression_for_count(begin);

    var_cnt = var_to_ind.size();
    value.resize(var_cnt, -1);
    pow2.resize(var_cnt + 1, 1);
    rep(i,var_cnt)pow2[i+1] = pow2[i] * 2 % MOD;

    begin = e.begin();
    expression(begin, false);

    cout << ans << endl;
}

// if_xxxxxduayfudisahfgaushgja_then_if_y_then_2_else_7_else_if_y_then_1_else_8