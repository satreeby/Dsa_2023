#include <iostream>
#include <fstream>
#include "arrList.h"
float count=0;    //记录赋值次数
bool arrList::append(int value){
    using namespace std;
    if (curLen < maxSize)
    {
        aList[curLen]=value;
        curLen++;
        count++;
    }
    else
    {
        int* newList=new int[2*maxSize];
        int i;
        for ( i = 0; i < maxSize; i++){
            newList[i]=aList[i];
            count++;
        }
        newList[i]=value;
        count++;
        maxSize=2*maxSize;
        curLen++;
        delete [] aList;
        aList=newList; 
    }
    return true;
}
int main(){
    using namespace std;
    ofstream outfile;
	outfile.open("append1.txt");
    int n_1=50;
    float n_2;
    for ( n_2 = 1; n_2 < 50*n_1+5; n_2+=5 )
    {
        count=0;
        arrList list(n_1);
        int i;
        for ( i = 0; i < n_2; i++)
            list.append(i);
        outfile << "插入数量为：" << n_2 << "时，摊薄度为：" << count/n_2 << endl;
    }
    outfile.close();
    return 0;
}