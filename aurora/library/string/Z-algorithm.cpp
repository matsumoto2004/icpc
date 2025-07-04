
vector<int> Z(M);
Z[0] = M;
int a = 1;
int b = 0;
while(a < M){
  while(a+b < M && S[b] == S[a+b]) b++;
  Z[a] = b;
  if(b == 0){
    a++;
    continue;
  }
  int c = 1;
  while(c < b && c + Z[c] < b){
    Z[a+c] = Z[c];
    c++;
  }
  a += c;
  b -= c;
}
