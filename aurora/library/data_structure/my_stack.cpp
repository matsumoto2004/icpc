/*
 Stack<string> s(3);
 というように型とMaxSizeを指定する
*/

template <typename T>
class Stack{
private:
    T* stack;
    int size;
    int top;

public:
    Stack(int size): size(size), top(0) { stack = new T[size]; } //コンストラクタでサイズ指定
    ~Stack() { delete[] stack; } //デストラクタでメモリ解放

    void push(T a){
        if(top < size){
            stack[top] = a;
            top++;
        }
        else{
            cout << "This stack is full." << endl;
            return;
        }
    }

    void pop(){
        if(top > 0){
            top--;
        }
        else{
            cout << "This stack is empty." << endl;
        }
    }

    T top(){
        if(top > 0){
            return stack[top-1];
        }
        else{
            cout << "This stack is empty." << endl;
        }
    }

    bool empty(){
        return top == 0;
    }

    int size(){
        return top;
    }
}