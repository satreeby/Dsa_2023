#include <iostream>
using namespace std;
void error(){
    cout << "error!" << endl;
    exit(1);
}
class Stack
{
private:
    int size;
    int top;
    int *s;
public:
    Stack(int n){
        s=new int[n];
        top=-1;
        size=n;
    };
    ~Stack(){
        delete [] s;
        top=-1;
        size=0;
        s=NULL;
    };
    bool isempty(){
        return (top<0)? true : false;
    }
    bool isfull(){
        return (top<size-1)? false : true;
    }
    int pop(){
        if (top<0)
            error();
        return s[top--];
    }
    void push(int n){
        if (top<size-1)
        {
            s[++top]=n;
            return ;
        }
        error();
    }
};
class Queue
{
private:
    Stack s1;
    Stack s2;
public:
    Queue(int n):s1(n),s2(n){};
    ~Queue(){
        s1.~Stack();
        s2.~Stack();
    };
    bool isempty(){
        return ((s1.isempty()==true) && (s2.isempty()==true))? true : false;        
    }
    bool isfull(){
        return ((s1.isfull()==true) && (s2.isempty()==false))? true : false;
    }
    void maybepour(){
        if ((s1.isfull()==true) && (s2.isempty()==true))
        {
            int temp;
            while (s1.isempty()==false)
            {
                temp=s1.pop();
                s2.push(temp);
            }
        }
        return;
    }
    void enqueue(int n){
        if (this->isfull()==true)
            error();
        this->maybepour();
        s1.push(n);
        return;  
    }
    int dequeue(){
        if (this->isempty()==true)
           error();
        int temp;
        if (s2.isempty()==true)
        {
            while (s1.isempty()==false)
            {
                temp=s1.pop();
                s2.push(temp);
            }
        }
        temp=s2.pop();
        return temp;
    }
};
int main(){
    Queue q(10);
    for (int i = 0; i < 15; i++)
        q.enqueue(i);
    for (int i = 0; i < 10; i++)
        cout << q.dequeue() << endl;
    q.enqueue(20);
    for (int i = 0; i < 6; i++)
        cout << q.dequeue() << endl;
    return 0;
}
