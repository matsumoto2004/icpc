template <typename T>
class Queue{
private:
    T* queue;
    int size;
    int head;
    int tail;

public:
    Queue(int size): size(size), head(0), tail(0) { queue = new T[size]; }
    ~Queue() { delete[] queue; }

    void enqueue(T a){
        if(tail < size){
            queue[tail] = a;
            tail++;
        }
        else{
            cout << "This queue is full." << endl;
            return;
        }
    }

    void dequeue(){
        if(head < tail){
            head++;
        }
        else{
            cout << "This queue is empty." << endl;
            return;
        }
    }

    T top(){
        if(head < tail){
            return queue[head];
        }
    }

    bool empty(){
        return tail == head;
    }

    int size(){
        return size;
    }
}