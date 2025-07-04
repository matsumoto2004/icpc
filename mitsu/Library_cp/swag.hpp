template<typename S,S (*op)(S,S),S (*e)()>
struct SWAG{
    //stack二つでqueueを作る：
    // stf ===| <- |=== stb
    //演算の向きに気を付ける
    std::stack<S> stf,stb,stb_row;
    void push(S x){
        if(stb.empty())stb.push(x);
        else stb.push(op(stb.top(),x));
        stb_row.push(x);
    }
    S fold(){
        if(stf.empty()){
            if(stb.empty())return e();
            return stb.top();
        }
        if(stb.empty())return stf.top();
        return op(stf.top(), stb.top());
    }
    void pop(){
        if(stf.empty()){
            while(!stb.empty()){
                S x=stb_row.top();
                stb.pop();stb_row.pop();
                if(stf.empty())stf.push(x);
                else stf.push(op(x,stf.top()));
            }
        }
        stf.pop();
    }
};