long long int modinv(long long int a,long long int m){
    long long int b = m,u = 1,v = 0;
    while(b){
      long long int t = a/b;
      a -= t*b; 
      swap(a,b);
      u -= t*v; 
      swap(u,v);
    }
    u %= m; 
    if(u<0) u += m;
    return u;
  }