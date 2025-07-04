const int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
const int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

bool isok(ll i,ll j,ll h,ll w){
    if(i<0||j<0||i>=h||j>=w) return false;
    else return true;
}