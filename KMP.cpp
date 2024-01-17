#include <iostream>
#include <string.h>
using namespace std;
/*  int* buildnext(const char *P)
    int size=strlen(P);
    int* next=new int[size];
    int j=0;
    int t=next[0]=-1;
    while (j<size-1)
    {
        if (t>=0 && P[t]==P[j])
            next[++j]=++t;
        else if (t>=0 && P[t]!=P[j])
            t=next[t];
        else
            next[++j]=t=0;
    }
    return next;
} */
int* buildnext(const char *P){
    int size=strlen(P);
    int* next=new int[size];
    int j=0;
    int t=next[0]=-1;
    while (j<size-1)
    {
        while (t>=0 && P[t]!=P[j])
            t=next[t];
        next[++j]=++t;
    }
    return next;
}
int match(const char* P, const char* T){
    if (strlen(P)>strlen(T))
    {   
        int i, j;
        i=j=0;
        int *n=buildnext(T);
        int sizelong=strlen(P);
        int sizeshort=strlen(T);
        while (i<sizelong && j<sizeshort)
        {
            if (j>=0 && P[i]==T[j])
            {
                i++;
                j++;
            }
            else if (j>=0 && P[i]!=T[j])
            {
                j=n[j];
            }
            else
            {
                j++;
                i++;
            }       
        }
        return i-j;
    }
    else
        return match(T, P);
}
int main(){
    char T[]="lla";
    char P[]="ininchchilla";
    int *n=buildnext(P);
    for (int i = 0; i < strlen(P); i++)
    {
        cout << n[i] << " ";
    }
    cout << endl;
    int m=match(P, T);
    cout << m << endl;
}