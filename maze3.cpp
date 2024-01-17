#include <iostream>
#include <stack>
using namespace std;

/*格点*/
struct Grid
{
    int x;
    int y;
};
/*边*/
struct Edge
{
    int to;
    Edge* next;
};
/*记录路径*/
class Path
{
private:
    int* stack;     //使用一个栈存储路径结点序号
    int top;        //top指向栈顶（已存在）元素
    int size;       //栈的大小
    Path* next;     //指向下一条路径
    Path* sidepath;
public:
    Path(){
        stack=NULL;
        next=NULL;
        top=-1;
        sidepath=NULL;
    };
    ~Path(){
        top=-1;
        delete [] stack;
        stack=NULL;
        next=NULL;
    };
    void setSize(int n){
        size=n;
        stack=new int[size];
    }
    void push(int val){
        if (top<size-1)
            stack[++top]=val;
    }
    int pop(){
        if (top>=0)
            return stack[top--];
    }
    int gettop(){
        if (top>=0)
            return stack[top];
    }
    bool empty(){
        return (top==-1);
    }
    void setNextPath(Path* p){
        next=p;
    }
    Path* getNextPath(){
        return next;
    }
    void setSidePath(Path* p){
        sidepath=p;
    }
    Path* getSidePath(){
        return sidepath;
    }
    void printPath(){
        if (empty()==false){
            for (int i = top; i >= 0; i--)
                cout << stack[i] << " ";
            cout << endl;
        }
    }
};
/*迷宫图结点*/
class GraphNode
{
private:
    Grid value;
    Edge* e;
    int Mark;
public:
    GraphNode(){
        Mark=0;
        e=NULL;
    };
    ~GraphNode(){
        delete [] e;
        e=NULL;
    };
    void setValue(const Grid& val){
        value=val;
    }
    Grid getValue(){
        return value;
    }
    void Marked(){
        Mark=1;
    }
    void UnMarked(){
        Mark=0;
    }
    int getMark(){
        return Mark;
    }
    void setEdge(Edge* p1){
        e=p1;
    }
    Edge* getEdge(){
        return e;
    }
};
/*迷宫图*/
class Graph
{
private:
    GraphNode* nodes;
    int nums;
public:
    Graph(int size){
        nodes=new GraphNode[size];
        nums=size;
    };
    ~Graph(){
        delete [] nodes;
    };
    void setNode(int i, const Grid& val){
        if (i>=0 && i<nums)
            nodes[i].setValue(val);
    }
    void setEdge(int from, int to){
        /*无向边*/
        Edge* edge1 =new Edge[1];
        edge1->to=to;
        edge1->next=NULL;
        Edge* e=nodes[from].getEdge();
        if (e==NULL)
            nodes[from].setEdge(edge1);
        else
        {
            while (e->next!=NULL)
                e=e->next;
            e->next=edge1;            
        }
        Edge* edge2 =new Edge[1];
        edge2->to=from;
        edge2->next=NULL;
        e=nodes[to].getEdge();
        if (e==NULL)
            nodes[to].setEdge(edge2);
        else
        {
            while (e->next!=NULL)
                e=e->next;
            e->next=edge2;            
        }
    }
    void printEdge(int i){
        for (Edge* e = nodes[i].getEdge(); e!=NULL; e=e->next)
            cout << e->to << " ";
        cout << endl;
    }
    int getSize(){
        return nums;
    }
    Path* DFSFind(int entrance, int exit){
        if (nodes[entrance].getMark()==1)
            return NULL;
        if (entrance==exit){
            Path* p=new Path[1];
            p->setSize(nums);
            p->push(entrance);    
            return p;
        }
        else
        {
            Path* p_new=NULL;
            for (Edge* e = nodes[entrance].getEdge(); e!=NULL; e=e->next)
            {
                nodes[entrance].Marked();
                Path* p=DFSFind(e->to, exit);
                nodes[entrance].UnMarked();
                if (p)
                {
                    p->setSidePath(p_new);
                    p_new=p;
                    Path* p1;
                    for (p1 = p; p1; p1=p1->getNextPath())
                         p1->push(entrance);
                }
            }
            for (Path* pi = p_new; pi; pi=pi->getSidePath())
            {
                Path* pj=pi;
                for ( ; pj->getNextPath(); )
                    pj=pj->getNextPath();
                pj->setNextPath(pi->getSidePath());
            }
            return p_new;
        }
    }
    void printPaths(int entrance, int exit){
        Path* paths=DFSFind(entrance, exit);
        for (Path* p = paths; p != NULL; p=p->getNextPath())
            p->printPath();
    }
};

int main(){
    /*初始化网格*/
    Grid g[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            g[i][j].x=i;
            g[i][j].y=j;
        }
    Graph maze(16);
    for (int i = 0; i < 16; i++)
        maze.setNode(i, g[i/4][i%4]);
    maze.setEdge(0, 1);
    maze.setEdge(0, 4);
    maze.setEdge(1, 5);
    maze.setEdge(4, 5);
    maze.setEdge(4, 8);
    maze.setEdge(5, 6);
    maze.setEdge(6, 7);
    maze.setEdge(6, 10);
    maze.setEdge(10, 14);
    maze.setEdge(3, 7);
    maze.setEdge(8, 12);
    maze.setEdge(12, 13);
    maze.setEdge(13, 14);
    maze.setEdge(14, 15);

    /*打印路径*/
    maze.printPaths(0,15);

}
