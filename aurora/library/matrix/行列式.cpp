long double determinant(vector<vector<long double>> A){
    int n = A.size();
    int ok = 0;
    long double D = 1;
    for(int i=0;i<n;i++){
      if(A[i][i] != 0) ok++;
      if(A[i][i] == 0){
        for(int j=i+1;j<n;j++){
          if(A[j][i] != 0){
            D *= -1;
            ok++;
            swap(A[i],A[j]);
            break;
          }
        }
      }
      long double b = A[i][i];
      D *= b;
      for(int j=0;j<n;j++) A[i][j] /= b;
      for(int j=0;j<n;j++){
        if(j != i){
          long double c = -A[j][i];
          for(int k=0;k<n;k++) A[j][k] += A[i][k]*c;
        }
      }
    }
    if(ok == n) return D;
    else return 0;
  }