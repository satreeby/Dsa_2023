#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/*定义点坐标和矩形导体*/
struct Point
{
    int x;
    int y;
};
struct Rectangle
{
    int height;
    int width;
    Point p;
};

/*判断矩形导体是否交叠*/
bool overlap(Rectangle a, Rectangle b){
    if ( (a.p.y > b.p.y+b.height) || (a.p.y+a.height < b.p.y) || (a.p.x > b.p.x+b.width) || (a.p.x+a.width < b.p.x) )
        return false;
    else
        return true;
}

/*并查集矩形导体结点*/
template <class T>
class PartreeNode
{
private:
    T value;                //值为矩形导体
    PartreeNode<T>* parent; //矩形导体结点的父节点
    int ncount;             //矩形导体结点重量
    int num;                //矩形导体结点编号
public:
    PartreeNode(){
        ncount=1;
        parent=NULL;
    };
    virtual ~PartreeNode(){};
    T getValue(){
        return value;
    }
    void setValue(const T& val){
        value=val;
    }
    PartreeNode<T>* getParent(){
        return parent;
    }
    void setParent(PartreeNode<T>* par){
        parent=par;
    }
    int getCount(){
        return ncount;
    }
    void setCount(int n){
        ncount=n;
    }
    int getNum(){
        return num;
    }
    void setNum(int n){
        num=n;
    }
};

/*并查集矩形导体树*/
template <class T>
class Partree
{
private:
    PartreeNode<T>* array;
    int Size;
public:
    Partree(int size){
        Size=size;
        array=new PartreeNode<T>[size];
    };
    virtual ~Partree(){
        delete [] array;
    };
    int getSize(){
        return Size;
    }
    PartreeNode<T>* getNodei(int i){
        if (i<Size && i>=0)
            return &array[i];
    }//获取array第i个结点的值
    void setNodeiValue(int i, const T& val){
        if (i<Size && i>=0){
            array[i].setValue(val);
            array[i].setNum(i);
        }
    }//给array第i个结点赋值，包括编号
    PartreeNode<T>* Find(PartreeNode<T>* node){
        if (node->getParent()==NULL)
            return node;
        else
            return Find(node->getParent());        
    }
    bool Different(int i, int j){
        PartreeNode<T>* pi=Find(&array[i]);
        PartreeNode<T>* pj=Find(&array[j]);
        return pi!=pj;
    }
    void Union(int i, int j){
        PartreeNode<T>* pi=Find(&array[i]);
        PartreeNode<T>* pj=Find(&array[j]);
        if ( pi!=pj )
        {
            if ( pi->getCount() >= pj->getCount() )
            {
                pj->setParent(pi);
                pi->setCount(pi->getCount()+pj->getCount());
            }
            else
            {
                pi->setParent(pj);
                pj->setCount(pi->getCount()+pj->getCount());
            }
        }
    }
};

/*生成由若干个矩形导体组成的线网*/
struct Netnode
    {
        int* num;
        int tagnum;
        int q;
    };
struct Net
{
    Netnode* nets;
    int netnumbers;
};
Net getNet(Rectangle* array, int size){
    Partree<Rectangle> t(size);
    for (int i = 0; i < size; i++)
        t.setNodeiValue(i, array[i]);
    for (int i = 0; i < size-1; i++)
        for (int j = i+1; j < size; j++)
            if (overlap(array[i], array[j])==true)
                t.Union(i, j); 
    Netnode* nets=new Netnode[size];
    int netnumbers=0;
    for (int i = 0; i < size; i++)
    {
        PartreeNode<Rectangle>* p= t.Find(t.getNodei(i));
        int j = 0;
        for (; j < netnumbers; j++)
            if (nets[j].tagnum==p->getNum())
                break;
        if (j==netnumbers)
        {
            nets[j].tagnum=p->getNum();
            nets[j].num=new int[p->getCount()];
            nets[j].q=0;
            netnumbers++;
        }
        nets[j].num[nets[j].q++]=i;
    }
    Net n;
    n.nets=nets;
    n.netnumbers=netnumbers;
    return n; 
}
void printNet(Net n){
    for (int i = 0; i < n.netnumbers; i++)
    {
        cout << "Net" << i << ":";
        for (int j = 0; j < n.nets[i].q; j++)
            cout << n.nets[i].num[j] << ' ';
        cout << endl;
    }
}

Rectangle* initiate(int size){
    Rectangle* array=new Rectangle[size];
    unsigned seed;
    seed = time(0);
    srand(seed);
    for (int i = 0; i < size; i++)
    {
        array[i].p.x=rand()%10000;
        array[i].p.y=rand()%10000;
        if (array[i].p.x==10000 || array[i].p.y==10000)
        {
            array[i].width=array[i].height=0;
        }
        else
        {
            array[i].width=rand()%(10000-array[i].p.x);
            array[i].height=rand()%(10000-array[i].p.y);
        }
        /*cout << "Rectangle" << i << ": (" << array[i].p.x << "," << array[i].p.y << "), " << "width=" << array[i].width << ", height=" << array[i].height << endl;*/
    }
    return array;
}
int main(){
    printNet(getNet(initiate(50), 50));
}