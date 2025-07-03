template<typename T,T (*op)(T,T)>
struct Disjoint_Sparse_Table{
    vector<T> a;
    vector<vector<T>> table;
    vector<int> height;
    Disjoint_Sparse_Table(const vector<T> &a_):a(a_){
        int n=a.size();
        int h=1;
        while((1<<h)<=n)h++;
        table.assign(h,vector<T>(n));
        height.assign((1<<h),0);
        for(int i=2;i<(1<<h);i++)height[i]=height[i>>1]+1;
        for(int i=0;i<n;i++)table[0][i]=a[i];
        for(int i=1;i<h;i++){
            int s=(1<<i);
            for(int j=0;j<n;j+=(s<<1)){
                int t=min(j+s,n);
                table[i][t-1]=a[t-1];
                for(int k=t-2;k>=j;k--){
                    table[i][k]=op(a[k] , table[i][k+1]);
                }
                if(n<=t)break;
                table[i][t]=a[t];
                for(int k=t+1;k<min(t+s,n);k++){
                    table[i][k]=op(table[i][k-1] , a[k]);
                }
            }
        }
    }
    T query(int l,int r){
        r--;
        if(l==r)return table[0][l];
        return op(table[height[l^r]][l] , table[height[l^r]][r]);
    }
};