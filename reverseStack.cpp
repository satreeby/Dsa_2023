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
        if (isempty()==true)
            error();
        return s[top--];
    }
    void push(int n){
        if (isfull()==true)
            error();
        s[++top]=n;
        return ;
    }
    void insert(int value){
        if (isfull()==true)
            error();
        if (isempty()==true)
            push(value);
        else{
            int temp=pop();
            insert(value);
            push(temp);
        }
    }
    void reverse(){
        if (isempty()==true)
            return;
        if (top==0)
            return;
        else
        {
            int temp=pop();
            reverse();
            insert(temp);
            return;
        }       
    }
};
int main(){
    Stack s(20);
    for (int i = 0; i < 10; i++)
        s.push(i);
    s.reverse();
    for (int i = 0; i < 10; i++)
        cout << s.pop() << endl;
    return 0;
}