#include<stdlib.h>
#ifndef binarytree_h
#define binarytree_h
class nodeforlinkedlist;
class binarytreenode
{

    int data;
    binarytreenode* left;
    binarytreenode* right;
public:
    binarytreenode(int data)
    {
        this->data=data;
        left=NULL;
        right=NULL;
    }
    friend binarytreenode* DeleteAllLeafNodes(binarytreenode*);
    friend void PrintingAllNodesThatDoNotHaveSibling(binarytreenode*);
    friend nodeforlinkedlist** CreatingLinkedListForLevels(binarytreenode*);
    friend bool IsBalanced(binarytreenode*);
    friend bool IsStructurallyIdentical(binarytreenode*,binarytreenode*);
    friend int SumOfAllNodes(binarytreenode*);
    friend int HeightOfTree(binarytreenode*);
    friend int Diameter(binarytreenode*);
    friend void MirrorTree(binarytreenode*);
    friend void InorderTraversalRecursively(binarytreenode*);
    friend void PreorderTraversalRecursively(binarytreenode*);
    friend void PostorderTraversalRecursively(binarytreenode*);
    friend binarytreenode* MakingBinaryTree();
    friend void PrintingTree(binarytreenode*);
    friend int TotalNumberOfNodes(binarytreenode*);







};
class nodeforqueue
{
public:
    binarytreenode* data;
    nodeforqueue* next;
    nodeforqueue(binarytreenode* data)
    {
        this->data=data;
        next=NULL;
    }
};
class queue
{
    nodeforqueue* front;
    nodeforqueue* end;
    public:
        queue()
        {
            front=NULL;
            end=NULL;
        }
        void enqueue(binarytreenode* data)
        {
            nodeforqueue* newnode=new nodeforqueue(data);
            if(front==NULL)
            {
                front=newnode;
                end=newnode;
            }
            else
            {
                end->next=newnode;
                end=newnode;
            }
        }
        binarytreenode* dequeue()
        {
            if(isempty())
            {
                return NULL;
            }
            nodeforqueue* temp=front;
            front=front->next;
            if(front==NULL)
                end=NULL;
            binarytreenode* tobereturned=temp->data;
            delete temp;
            return tobereturned;
        }
        bool isempty()
        {
            if(front==NULL)
                return true;
            else
                return false;
        }
};
binarytreenode* MakingBinaryTree()
{
    cout<<"data of root"<<endl;
    int data;
    cin>>data;
    binarytreenode* root=new binarytreenode(data);
    queue a;
    a.enqueue(root);
    while(!a.isempty())
    {
        binarytreenode* temp=a.dequeue();
        cout<<"Enter left child of "<<temp->data<<endl;
        cin>>data;
        if(data!=-1)
        {
        binarytreenode* leftnewnode=new binarytreenode(data);
        temp->left=leftnewnode;
        a.enqueue(temp->left);
        }
        cout<<"Enter right child of "<<temp->data<<endl;
        cin>>data;
        if(data!=-1)
        {
        binarytreenode* rightnewnode=new binarytreenode(data);
        temp->right=rightnewnode;
        a.enqueue(temp->right);
        }
    }
    return root;

}
void PrintingTree(binarytreenode* root)
{
    queue a;
    if(root!=NULL)
    {
    cout<<"root data : "<<root->data<<endl;
    a.enqueue(root);
    }
    while(!a.isempty())
    {
        binarytreenode* temp=a.dequeue();
        cout<<temp->data<<" : ";
        if(temp->left!=NULL)
        {
            cout<<temp->left->data<<" ";
            a.enqueue(temp->left);
        }
        if(temp->right!=NULL)
        {
            cout<<temp->right->data<<" ";
            a.enqueue(temp->right);
        }
        cout<<endl;
    }
}
int TotalNumberOfNodes(binarytreenode* root)
{
    if(root!=NULL)
    {
        return 1+TotalNumberOfNodes(root->left)+TotalNumberOfNodes(root->right);
    }
    else
    {
        return 0;
    }
}
int HeightOfTree(binarytreenode* root)
{
    if(root==NULL)
        return 0;
    else return 1+max(HeightOfTree(root->left),HeightOfTree(root->right));
}

int Diameter(binarytreenode* root)
{
    if(root==NULL)
        return 0;
    return max(HeightOfTree(root->left)+HeightOfTree(root->right)+1,max(Diameter(root->left),Diameter(root->right)));

}
void MirrorTree(binarytreenode* root)
{
    if(root==NULL)
       return;
    swap(root->left,root->right);
    MirrorTree(root->left);
    MirrorTree(root->right);
}
void InorderTraversalRecursively(binarytreenode* root)
{
    if(root==NULL)
        return;
    InorderTraversalRecursively(root->left);
    cout<<root->data<<endl;
    InorderTraversalRecursively(root->right);
}
void PreorderTraversalRecursively(binarytreenode* root)
{
    if(root==NULL)
        return;
        cout<<root->data<<endl;
    PreorderTraversalRecursively(root->left);
    PreorderTraversalRecursively(root->right);
}
void PostorderTraversalRecursively(binarytreenode* root)
{
    if(root==NULL)
        return;
    PostorderTraversalRecursively(root->left);
    PostorderTraversalRecursively(root->right);
    cout<<root->data<<endl;
}
int SumOfAllNodes(binarytreenode* root)
{
    if(root==NULL)
        return 0;
    else
        return root->data+SumOfAllNodes(root->left)+SumOfAllNodes(root->right);
}
bool IsStructurallyIdentical(binarytreenode* root1,binarytreenode* root2)
{
    if(root1==NULL&&root2==NULL)
        return true;
    else if(root1!=NULL&&root2!=NULL&&root1->data==root2->data)
        return true*IsStructurallyIdentical(root1->left,root2->left)*IsStructurallyIdentical(root1->right,root2->right);
    else
        return false;
}
bool IsBalanced(binarytreenode* root)
{
    if(root==NULL)
        return true;
    else if(abs(HeightOfTree(root->left)-HeightOfTree(root->right))<=1)
        return true*IsBalanced(root->left)*IsBalanced(root->right);
    else
        return false;
}
class nodeforlinkedlist
{
    public:
    binarytreenode* value;
    nodeforlinkedlist* next;
    nodeforlinkedlist()
    {

    }
    nodeforlinkedlist(binarytreenode* value)
    {
        this->value=value;
        next=NULL;
    }

};
nodeforlinkedlist** CreatingLinkedListForLevels(binarytreenode* root)
{
    nodeforlinkedlist** array=new nodeforlinkedlist*[HeightOfTree(root)];
    queue a;
    a.enqueue(root);
    int previous=1;
    int levels=0;
    while(!a.isempty())
    {
        int currentvalue=0;
        nodeforlinkedlist* head=NULL;
        nodeforlinkedlist* prev=NULL;
        while(previous>0)
        {
            binarytreenode* temp=a.dequeue();


            nodeforlinkedlist* newnode=new nodeforlinkedlist(temp);
            if(head==NULL)
            {
                head=newnode;
                prev=newnode;
            }
            else
            {
                prev->next=newnode;
                prev=newnode;
            }
            if(temp->left!=NULL)
            {
                a.enqueue(temp->left);
                currentvalue++;
            }
            if(temp->right!=NULL)
            {
                a.enqueue(temp->right);
                currentvalue++;
            }
            previous--;
        }

        array[levels]=head;
        levels++;
        previous=currentvalue;
    }
    return array;

}
void PrintingAllNodesThatDoNotHaveSibling(binarytreenode* root)
{
    if(root==NULL)
        return;
    else if(root->left==NULL&&root->right!=NULL){
        cout<<root->right->data<<endl;
        PrintingAllNodesThatDoNotHaveSibling(root->right);
        }
    else if(root->left!=NULL&&root->right==NULL){
        cout<<root->left->data<<endl;
        PrintingAllNodesThatDoNotHaveSibling(root->left);
        }
        else
        {
            PrintingAllNodesThatDoNotHaveSibling(root->left);
            PrintingAllNodesThatDoNotHaveSibling(root->right);

        }
}
binarytreenode* DeleteAllLeafNodes(binarytreenode* root)
{
    if(root==NULL)
        return NULL;
    if(root->left==NULL&&root->right==NULL)
    {
        delete root;
        return NULL;
    }
    else
    {
        root->left=DeleteAllLeafNodes(root->left);
        root->right=DeleteAllLeafNodes(root->right);
    }
    return root;
}

#endif // binarytree_h
