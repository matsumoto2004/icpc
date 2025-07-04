vs rotate(vs v,ll h,ll w){
    vs ret(w,string(h,' '));
    rep(i,h)rep(j,w){
        ret[w-1-j][i]=v[i][j];
    }
    return ret;
}