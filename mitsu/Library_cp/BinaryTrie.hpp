#include<cassert>

//複数個あれば複数個格納されるので気をつける。
//だいたい O(word_size) とかで動く
//2分木。一番下の"高さ"を-1、一番上をSZ-1にする。(高さhのすぐ下の辺がh-bit目を表す。)
template<typename T,int SZ=32>
struct BinaryTrie{
    BinaryTrie():root(nullptr){}
    int size(){
        return root ? root->cnt:0;
    }
    //xを追加する。同じ値を複数個追加することも可能。
    void insert(T x){
        root=insert_inner(root,x);
    }
    //xを一つ減らす。xが存在しなければ何もしない。
    void erase(T x){
        if(!root || !count(x))return;
        root=erase_inner(root,x);
    }
    //xの個数を返す。
    int count(T x){
        if(!root)return 0;
        return count_inner(root,x);
    }
    //{x^XOR_val}の最小値
    T min_val(T XOR_val=0){
        return min_val_inner(root,XOR_val)^XOR_val;
    }
    //{x^XOR_val}の最大値
    T max_val(T XOR_val=0){
        return min_val_inner(root,~XOR_val)^XOR_val;
    }
    //XOR_valを全体にxorした集合におけるx「以下」の個数
    //第二引数を渡さない（0にする）ことで、いまの集合におけるx以下の個数も数えられる
    int lower_count(T x,T XOR_val=0){
        return lower_count_inner(root,x,XOR_val);
    }
    //x「以上」の個数、あとは同様
    int upper_count(T x,T XOR_val=0){
        return size()-lower_count(x-1,XOR_val);
    }
    //{x^XOR_val}の、小さい方からk番目
    //kは0-idx
    T kth_element(int k,T XOR_val=0){
        return kth_element_inner(root,k+1,XOR_val)^XOR_val;
    }
private:
    struct Node{
        int cnt;
        Node *child[2];
        Node():cnt(0),child{nullptr,nullptr}{}
    };
    Node *root;
    Node* insert_inner(Node *now,const T x,const int now_height=SZ-1){
        if(!now)now=new Node;
        now->cnt++;
        if(now_height==-1)return now;
        int ne=x>>now_height & 1;
        now->child[ne]=insert_inner(now->child[ne],x,now_height-1);
        return now;
    }
    Node* erase_inner(Node *now,const T x,const int now_height=SZ-1){
        assert(now);
        now->cnt--;
        if(!now->cnt){
            delete now;
            return nullptr;
        }
        if(now_height==-1)return now;
        int ne=x>>now_height & 1;
        now->child[ne]=erase_inner(now->child[ne],x,now_height-1);
        return now;
    }
    int count_inner(Node *now,const T x,const int now_height=SZ-1){
        int ne=x>>now_height & 1;
        if(now_height==-1)return now->cnt;
        if(now->child[ne])return count_inner(now->child[ne],x,now_height-1);
        return 0;
    }
    T min_val_inner(Node *now,const T XOR_val,const int now_height=SZ-1){
        //要素が存在しなければfailed
        assert(now);
        if(now_height==-1)return 0;
        int ne=XOR_val>>now_height & 1;
        //少なくとも一方には子供が存在しているはず
        if(!now->child[ne])ne=!ne;
        return min_val_inner(now->child[ne],XOR_val,now_height-1) | (T)ne<<now_height;
    }
    int lower_count_inner(Node *now,const T x,const T XOR_val,const int now_height=SZ-1){
        assert(now);
        if(now_height==-1)return now->cnt;
        //XOR_valのビットが0：(xのビットが1 ? 0の個数を足して1に潜る : 0に潜る)
        //そうでない：(xのビットが1 ? 1の個数を0に足して0に潜る : 1に潜る)
        const int XOR_bit=(XOR_val>>now_height)&1;
        const int x_bit=(x>>now_height)&1;
        //-> (x_bit==1 ? XOR_bitの個数を足して!XOR_bitに潜る:XOR_bitに潜る)
        int ans=0;
        if(x_bit){
            if(now->child[XOR_bit]){
                ans+=now->child[XOR_bit]->cnt;
            }
            if(now->child[!XOR_bit]){
                ans+=lower_count_inner(now->child[!XOR_bit],x,XOR_val,now_height-1);
            }
        }
        else{
            if(now->child[XOR_bit]){
                ans=lower_count_inner(now->child[XOR_bit],x,XOR_val,now_height-1);
            }
        }
        return ans;
    }
    T kth_element_inner(Node *now,int k,const T XOR_val,const int now_height=SZ-1){
        assert(now);
        if(now_height==-1)return 0;
        int ne=(XOR_val>>now_height)&1;
        int l_cnt=0;
        if(now->child[ne])l_cnt=now->child[ne]->cnt;
        if(l_cnt<k){
            k-=l_cnt;
            ne=!ne;
        }
        return kth_element_inner(now->child[ne],k,XOR_val,now_height-1) | ((T)ne<<now_height);
    }
};