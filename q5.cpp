#include <iostream>
using namespace std;
template <class T>
struct Node{
    T info;
    Node<T>* left;
    Node<T>* right;
};

template <class T>
int countleaf(Node<T>* root){
    if (root==NULL)
        return 0;
    if (root->left==NULL && root->right==NULL)
        return 1;
    return countleaf<T>(root->left)+countleaf<T>(root->right);
}

int main(){
    Node<int>* n1=new Node<int>[1];
    Node<int>* n2=new Node<int>[1];
    Node<int>* n3=new Node<int>[1];
    Node<int>* n4=new Node<int>[1];
    Node<int>* n5=new Node<int>[1];
    
    n1->left=n2;
    n1->right=n3;

    n2->left=n2->right=NULL;

    n3->left=n4;
    n3->right=n5;

    n4->left=n4->right=NULL;
    n5->left=n5->right=NULL;

    cout << countleaf<int>(n1) << endl;
}
