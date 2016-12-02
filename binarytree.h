#ifndef binarytree_h
#define binarytree_h
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
    friend binarytreenode* MakingBinaryTree();
    friend void PrintingTree(binarytreenode*);
    friend int TotalNumberOfNodes(binarytreenode*);
    friend int HeightOfTree(binarytreenode*);
    friend int Diameter(binarytreenode*);
    friend void MirrorTree(binarytreenode*);
    friend void InorderTraversalRecursively(binarytreenode*);
    friend void PreorderTraversalRecursively(binarytreenode*);
    friend void PostorderTraversalRecursively(binarytreenode*);
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
    cout<<"root data : "<<root->data<<endl;
    queue a;
    a.enqueue(root);
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


#endif // binarytree_h
