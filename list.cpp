#include <iostream>
#include "arrList.h"
using namespace std;
void arrList::clear(){
    delete [] aList;
    maxSize = curLen = position = 0;
}
int arrList::length(){
    return curLen;
}
bool arrList::append(const int value){
    if (curLen < maxSize)
    {
        aList[curLen++]=value;
        return true;
    }
    return false;
}
bool arrList::insert(const int p, int value){
    if (curLen<maxSize)
    {
        for ( position = curLen; position > p; position--)
            aList[position]=aList[position-1];
        aList[position]=value;
        curLen++;
        return true;
    }
    return false;
}
bool arrList::deletep(const int p){
    if (p<curLen)
    {
        for ( position = p; position < curLen-1; position++)
            aList[position]=aList[position+1];
        curLen--;
        return true;
    }
    return false;
}
bool arrList::setValue(const int p, int value){
    if (p<curLen)
    {
        aList[p]=value;
        return true;
    }
    return false;
}
 bool arrList::getValue(const int p, int& value){
    if (p<curLen)
    {
        value=aList[p];
        return true;
    }
    return false;
 }
 bool arrList::getPos(int & p, const int value){
    for ( position = 0; position < curLen; position++)
        if (aList[position]==value)
        {
            p=position;
            return true;
        }
    return false;
 }

 int main(){
    arrList list(10);
    int i;
    // 
    for ( i = 0; i < 8; i++)
        list.append(i);
    int value;

    list.getValue(2, value);    //测试append和getValue函数
    cout << value << endl;
    
    list.insert(2,3);           //测试insert函数            
    list.getValue(2, value);
    cout << value << endl;
    
    list.deletep(2);            //测试deletep函数
    list.getValue(2, value);
    cout << value << endl;
    
    list.setValue(2, 8);        //测试setvalue函数
    list.getValue(2, value);
    cout << value << endl;
    
    int p;
    list.getPos(p, 8);          //测试getPos函数
    cout << p << endl;

    //测试length函数
    cout << list.length() << endl;

    //测试clear函数
    list.clear();
    cout << list.length() << endl;

    return 0;
 }