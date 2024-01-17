#include <iostream>
using namespace std;
void error(){
    cout << "error!" << endl;
    exit(1);
}
class Circlequeue
{
private:
    int size;
    int *q;
    int front;
    int rear;
public:
    Circlequeue(int n){
        size=n+1;
        q=new int[size];
        front=rear=0;
    };
    ~Circlequeue(){
        delete [] q;
        q=NULL;
        size=0;
        front=rear=0;
    };
    bool isempty(){
        return (front==rear)? true : false;
    }
    bool isfull(){
        return ((rear+1)%size==front)? true : false;
    }
    void enqueue(int value){
        if (isfull()==true)
            error();
        q[rear]=value;
        rear=(rear+1)%size;
    }
    int dequeue(){
        if (isempty()==true)
            error();
        int temp=q[front];
        front=(front+1)%size;
        return temp;
    }
};
void date(int num_boy, int num_girl, int num_songs){
    Circlequeue boys(num_boy), girls(num_girl);
    for (int i = 0; i < num_boy; i++)
        boys.enqueue(i+1);
    for (int j = 0; j < num_girl; j++)
        girls.enqueue(j+1);
    for (int k = 0; k < num_songs; k++)
    {
        int boy=boys.dequeue();
        int girl=girls.dequeue();
        cout << boy << ' ' << girl << endl;
        boys.enqueue(boy);
        girls.enqueue(girl);
    }
    return;
}
int main(){
    int num_boy, num_girl, num_songs;
    cout << "please input the numbers of boys and girls: " << endl;
    cin >> num_boy;
    cin >> num_girl;
    cout << "please input the numbers of songs: " << endl;
    cin >> num_songs;
    date(num_boy, num_girl, num_songs);
    return 0;
}
