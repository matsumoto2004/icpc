#include<bits/stdc++.h>
using namespace std;
using ll=long long;
template<int mod>
using Fp=ll;/////////わあ。

//Modintに依存.
template<typename T>
struct Matrix{
    vector<vector<T>> v;
    Matrix(const int n,const int m,T x=0):v(n,vector<T>(m,x)){}
    size_t size()const{return v.size();}
    inline vector<T>& operator[](const int i){return v[i];}
};

template<int MOD>
int modp_Gauss_Jordan(Matrix<Fp<MOD>> &a,bool is_ex=false){
    int m=a.size(),n=a[0].size();
    
    int rank=0;
    for(int col=0;col<n;col++){
        //拡大係数行列を見ているなら一番右について操作しない.
        if(is_ex && col+1==n)break;
        //その列の非零元を探し,その列を上の方へ.なければ次の列へ.
        int piv=-1;
        for(int row=rank;row<m;row++){
            if(a[row][col].x!=0){
                piv=row;
                break;
            }
        }
        if(piv==-1)continue;
        swap(a[piv] , a[rank]);

        //上の方に持ってきた列のピボットが1になるように定数倍.
        Fp<MOD> now=1/a[rank][col];
        for(int col2=col;col2<n;col2++){////////
            a[rank][col2]=a[rank][col2]*now;
        }
        //その列に零でない元があると困るので,それを取り除く.
        //a[rank]の左の方は全て零なので,引き算するところはcol2>=colでよい.
        for(int row=0;row<m;row++){
            if(row!=rank && a[row][col].x!=0){
                Fp<MOD> fac=a[row][col];
                for(int col2=col;col2<n;col2++){
                    a[row][col2]-=a[rank][col2]*fac;
                }
            }
        }
        rank++;
    }
    return rank;
}

//A(res)=bを解く.
template<int MOD>
int modp_linear_equation(Matrix<Fp<MOD>>A,vector<ll> b,vector<ll> &res){
    int m=A.size(),n=A[0].size();
    Matrix<Fp<MOD>> M(m,n+1);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            M[i][j]=A[i][j];
        }
        M[i][n]=b[i];
    }
    int rank=Gauss_Jordan(M,true);
    for(int row=rank;row<m;row++)if(M[row][n].x!=0)return -1;
    res.assign(n,0);
    int j=0;
    for(int i=0;i<rank;i++){
        for(;;j++)if(M[i][j]){res[j]=M[i][n];break;}
    }
    return rank;
}


const int MAX_COL=51;//適宜.
struct bitMatrix{
    int h,w;
    vector<bitset<MAX_COL>> val;
    bitMatrix(int m=1,int n=1):h(m),w(n){
        val.resize(h);
    }
    inline bitset<MAX_COL>& operator[](const int i){return val[i];}
};
int bit_Gauss_Jordan(bitMatrix &a,bool is_ex=false){
    int rank=0;
    for(int col=0;col<a.w;col++){
        if(is_ex && col+1==a.w)break;
        //その列の非零元を探し,上へ.
        int piv=-1;
        for(int row=rank;row<a.h;row++){
            if(a[row][col]){
                piv=row;
                break;
            }
        }
        if(piv==-1)continue;
        swap(a[piv] , a[rank]);
        //F_2で非零元は1なので,ピボットは必ず1.

        //その列に零でない元があると困るので,それを取り除く.
        //xorが足し算/引き算に相当する.
        for(int row=0;row<a.h;row++){
            if(row!=rank && a[row][col])a[row]^=a[rank];
        }
        rank++;
    }
    return rank;
}
int bit_linear_equation(bitMatrix A,vector<int> b,vector<int> &res){
    int m=A.h;
    int n=A.w;
    bitMatrix M(m,n+1);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            M[i][j]=A[i][j];
        }
        M[i][n]=b[i];
    }
    int rank=bit_Gauss_Jordan(M,true);
    for(int row=rank;row<m;row++)if(M[row][n])return -1;
    res.assign(n,0);
    int j=0;
    for(int i=0;i<rank;i++){
        for(;;j++)if(M[i][j]){res[j]=M[i][n];break;}
    }
    return rank;
}