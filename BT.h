#ifndef BT_H_INCLUDED
#define BT_H_INCLUDED

using namespace std;

template < class btElementType >
class BST
{
public:
    BST();
    bool isEmpty() const;
    btElementType getData() const;
    string getTitle() const;
    void insert(const btElementType & d,const string & t,ofstream &f);
    void delet(const btElementType & d,const string & t);
    BST * retrieve(const btElementType & d);
    BST * Modify(const btElementType & d,const string & t);
    BST * left();
    BST * right();
    void makeLeft(BST * T1);
    void makeRight(BST * T1);
    void inOrderTraverse(BST *t,ofstream &f);

private:
    bool nullTree;
    btElementType treeData;
    string treeTitle;
    BST * leftTree;
    BST * rightTree;
};
#endif // BT_H_INCLUDED
