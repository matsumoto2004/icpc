
inline long long int mod(long long int a,long long int m){
    return (a%m+m)%m;
  }
  
  //ap+bq=gcd(a,b)のgcd(a,b)を返している
  long long int extGcd(long long int a,long long int b,long long int &p,long long int &q){  
    if(b == 0){ 
      p = 1; 
      q = 0; 
      return a; 
    }  
    long long int d = extGcd(b,a%b,q,p);  
    q -= a/b*p;  
    return d;  
  }
  
  //x%m1=b1,x%m2=b2
  //tとmodを返す、存在しないなら(0,-1)
  pair<long long int,long long int> ChineseRem(long long int b1,long long int m1,long long int b2,long long int m2){
    long long int p,q;
    long long int d = extGcd(m1,m2,p,q);
    if((b2-b1)%d != 0) return make_pair(0,-1);
    long long int m = m1*(m2/d);
    long long int tmp = (b2-b1)/d*p%(m2/d);
    long long int r = mod(b1+m1*tmp,m);
    return make_pair(r, m);
  }
  