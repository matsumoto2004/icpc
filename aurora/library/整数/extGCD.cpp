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