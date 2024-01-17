#include <iostream>
using namespace std;
#define M 10240
#define N 10
int w[N];
void error()
{
    cout << "error!" << endl;
    exit(1);
}
struct Frame
{
    bool result;
    int returnadd;
    int n;
    int s;
};
class Stack
{
public:
    struct Frame* frame;
    int top;
    int maxSize;
    Stack(int n){
        frame=new Frame[n];
        top=-1;
        maxSize=n;
    };
    ~Stack(){
        top=-1;
        maxSize=0;
        delete [] frame;
        frame=NULL;
    };
    void push(Frame f){
        if (top<maxSize)
        {
            frame[++top].returnadd=f.returnadd;
            frame[top].result=f.result;
            frame[top].s=f.s;
            frame[top].n=f.n;
            return;
        }
        else
            error();
    }
    Frame pop(){
        if (top>=0)
        {
            struct Frame f;
            f.returnadd=frame[top].returnadd;
            f.result=frame[top].result;
            f.s=frame[top].s;
            f.n=frame[top--].n;
            return f;
        }
        else
            error();
    }
};


bool knap(int s, int n){
    if (s == 0) return true;
    if ((s < 0) || (s>0 && n <1)) return false;
    if (knap (s-w[n-1], n-1)){
        cout << w[n-1] << endl;
        return true;
    }
    else 
        return knap(s, n-1);
}


bool knap_i(int s, int n){
    Stack stack(M);
    struct Frame f;
    f.n=n;
    f.s=s;
    f.returnadd=3;
    stack.push(f);

L0:
    if (stack.frame[stack.top].s==0){
        stack.frame[stack.top].result=true;
        f=stack.pop();
        switch (f.returnadd)
        {
        case 3: goto L3; break;
        case 2: goto L2; break;
        case 1: goto L1; break;
        case 0: goto L0; break;
        default: break;
        }
    }
    if ((stack.frame[stack.top].s < 0) || (stack.frame[stack.top].s>0 && stack.frame[stack.top].n <1)){
        stack.frame[stack.top].result=false;
        f=stack.pop();
        switch (f.returnadd)
        {
        case 3: goto L3; break;
        case 2: goto L2; break;
        case 1: goto L1; break;
        case 0: goto L0; break;
        default: break;
        }
    }

    f.n=stack.frame[stack.top].n-1;
    f.s=stack.frame[stack.top].s-w[stack.frame[stack.top].n-1];
    f.returnadd=1;
    stack.push(f);
    goto L0;

L1: 
    if(f.result==true){
        cout << w[f.n] << endl;
        f=stack.pop();
        f.result=true;
        switch (f.returnadd)
        {
        case 3: goto L3; break;
        case 2: goto L2; break;
        case 1: goto L1; break;
        case 0: goto L0; break;
        default: break;
        }
    }

    f.n=stack.frame[stack.top].n-1;
    f.s=stack.frame[stack.top].s;
    f.returnadd=2;
    stack.push(f);
    goto L0;  

L2:
    switch (f.result)
    {
    case true:
        f=stack.pop();
        f.result=true;
        break;
    default:
        f=stack.pop();
        f.result=false;
        break;
    }
    switch (f.returnadd)
    {
    case 3: goto L3; break;
    case 2: goto L2; break;
    case 1: goto L1; break;
    case 0: goto L0; break;
    default: break;
    }

L3:
    stack.~Stack();
    return f.result; 
}

int main(){
    int i;
    for ( i = 0; i < 4; i++)
        w[i]=i+1;
    w[i]=11;
    if (knap(5,5)==true)
        cout << "knap: yes" << endl;
    else
        cout << "knap: no" << endl; 
    if (knap_i(5,5)==true)
        cout << "knap_i: yes" << endl;
    else
        cout << "knap_i: no" << endl; 
}