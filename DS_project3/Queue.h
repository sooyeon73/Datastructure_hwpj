#ifndef QUEUE_H
#define QUEUE_H

#ifndef NULL
#define NULL    0
#endif

template<class T> class Queue
{
public:
    int front;
    int rear;
    int size; //Free to define (recommand 100 or 200)
    T *val;

    Queue(){
        size = 100; // юсюг define
        val = new T[size];
        front = 0;
        rear = 0;
    }
    ~Queue()
    {
        delete[] val;
    }

    void push(T value) {
        // input data
        if (!isFull())
        {
            val[rear] = value;
            rear = (rear + 1) % size;
        }
        else
            return;
    }

    void pop() {
        //Change Front
        if (!empty())
            front = (front + 1) % size;
        else
            return;

    }

    bool empty() {
        if (rear == front)
            return true;
        else
            return false;
        //Check its empty or not
    }

    bool isFull() {
        //Check queue is full or not
        if ((rear + 1) % size == front)
            return true;
        else
            return false;
    }
};


#endif
