#include <iostream>
#include <string.h>
using namespace std;
void error(){
    cout << "error!" << endl;
    exit(1);
}
template <class T>
struct Node{
    T info;
    Node<T>* left;
    Node<T>* right;
};
Node<char>* creatbtree(char* str_f, char* str_m){
    int len_f=strlen(str_f);
    int len_m=strlen(str_m);

    /*字符串长度不等出错*/
    if (len_f!=len_m)
        error();

    /*空字符串返回空指针*/
    if (len_m==0)
        return NULL;
    
    /*非空字符串*/
    int i;
    for (i = 0; i < len_m; i++)
        if (str_m[i]==str_f[0])
            break;
    if (i==len_m)
        error();

    /*构建根节点*/
    Node<char>* root=new Node<char>[1];
    root->info=str_m[i];
    root->left=root->right=NULL;
    
    /*构建左子树*/
    char left_f[i+1];
    char left_m[i+1];
    for (int j = 0; j < i; j++)
        left_f[j]=str_f[j+1];
    left_f[i]='\0';
    for (int j = 0; j < i; j++)
        left_m[j]=str_m[j];
    left_m[i]='\0';
    Node<char>* left=creatbtree(left_f, left_m);
    
    /*构建右子树*/
    char right_f[len_f-i];
    char right_m[len_f-i];
    for (int j = 0; j < len_f-i-1; j++)
        right_f[j]=str_f[j+i+1];
    right_f[len_f-i-1]='\0';
    for (int j = 0; j < len_f-i-1; j++)
        right_m[j]=str_m[j+i+1];
    right_m[len_f-i-1]='\0';
    Node<char>* right=creatbtree(right_f, right_m);

    /*连接成树*/
    root->left=left;
    root->right=right;

    return root;
}
void preorder(Node<char>* root){
    if (root==NULL)
        return;
    cout << root->info;
    preorder(root->left);
    preorder(root->right);   
    return; 
}
void midorder(Node<char>* root){
    if (root==NULL)
        return;
    midorder(root->left);
    cout << root->info;
    midorder(root->right);   
    return; 
}
void postorder(Node<char>* root){
    if (root==NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->info;
    return; 
}
int main(){
    char* str1="ABDCEGFHI";
    char* str2="DBAEGCHFI";

    Node<char>* root=creatbtree(str1, str2);
    preorder(root);
    cout << endl;
    midorder(root);
    cout << endl;
    postorder(root);
}
