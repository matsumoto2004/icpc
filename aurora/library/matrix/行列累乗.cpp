const long long int MOD = 998244353;
 
vector<vector<long long int>> mul(vector<vector<long long int>> &A,vector<vector<long long int>> &B){
  vector<vector<long long int>> C(A.size(),vector<long long int>(B[0].size()));
  for(int i=0;i<(int)A.size();i++) for(int k=0;k<(int)B.size();k++) for(int j=0;j<(int)B[0].size();j++) C[i][j] = (C[i][j]+A[i][k]*B[k][j])%MOD;
  return C;
}
 
vector<vector<long long int>> pow(vector<vector<long long int>> &A,long long int n){
  vector<vector<long long int>> B(A.size(),vector<long long int>(A.size()));
  for(int i=0;i<(int)A.size();i++) B[i][i] = 1;
  while(n > 0){
    if(n & 1) B = mul(B,A);
    A = mul(A,A);
    n >>= 1;
  }
  return B;
}