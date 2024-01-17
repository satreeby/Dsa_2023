#include <iostream>
#include <stack>
using namespace std;
struct Grid
{
    int x;
    int y;
};
struct Edge
{
    int to;
    Edge* next;
};

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
    void setEdge(Edge* e1){
        e=e1;
    }
    Edge* getEdge(){
        return e;
    }
};

class Graph
{
private:
    GraphNode* nodes;   
    int nums;           //结点数量（格子数）
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
    int getSize(){
        return nums;
    }
    bool DFSFind(int entrance, int exit){
        if (nodes[entrance].getMark()==1)
            return false;
        if (entrance==exit)
            return true;
        else{
            nodes[entrance].Marked();
            for (Edge* e = nodes[entrance].getEdge(); e!=NULL; e=e->next)
                if(DFSFind(e->to, exit))
                    return true;
            nodes[entrance].UnMarked();
            return false;
        }
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
    maze.setEdge(1, 5);
    maze.setEdge(5, 6);
    maze.setEdge(6, 10);
//    maze.setEdge(10, 11);
//    maze.setEdge(11, 15);
    maze.setEdge(8, 12);
    maze.setEdge(12, 13);

    if (maze.DFSFind(0, 15))
        cout << "Yes, there is a path from entrance to exit" << endl;
    else    
        cout << "No, there are no paths from entrance to exit" << endl;
}
