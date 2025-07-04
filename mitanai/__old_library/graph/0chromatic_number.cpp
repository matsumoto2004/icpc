int ChromaticNumber(vector<vector<int>> D){
  int n = D.size();
  int nn = 1 << n;
  vector<unsigned int> E(n,nn-1);
  for(int i=0; i<n; i++) for(int j=0; j<n; j++) if(i!=j) if(D[i][j] == 1) E[i] -= (1<<j);
  vector<unsigned int> A(nn>>1,0); A[0] = 1;
  for(int d=0; d<n-1; d++) for(int i=0; i<(1<<d); i++) A[i|(1<<d)] = A[i] + A[i&E[d]];
  vector<unsigned int> table(nn>>1,0); table[0] = 1;
  for(int d=0; d<n-1; d++) for(int i=0; i<(1<<d); i++) if(0 == ((i|(nn>>1)) & ~E[d])) table[i|(1<<d)] = table[i];
  if(table.back() != 0) return 1;
  for(int iD = 1; iD < n; iD++){
    int biD = 1<<(n-iD);
    int biDh = biD>>1;
    for(int d=0; d<n-iD; d++) for(int i=0; i<biD; ++i, i+=i&(1<<d)) table[i|(1<<d)] += table[i];
    for(int i=0; i<biD; i++) table[i] *= A[i];
    for(int i=0; i<biDh; ++i) table[i|biDh] -= table[i];
    for(int d=0; d<n-iD-1; d++) for(int i=biDh; i<biD; ++i, i+=i&(1<<d)) table[i|(1<<d)] -= table[i];
    if(table[biD-1] != 0) return iD+1;
    for(int i=0; i<biDh; i++) table[i] = table[biDh|i] ? 1 : 0;
  }
  return -1;
}
