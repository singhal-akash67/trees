#include<climits>
#ifndef tree_h
#define tree_h
class secondlargesthelper;/*just defined here, will be declared later for secondlargestvalue() function*/
                          /*so don't worry about it here */
class treenode
{
    int data;
    treenode* *children;
    int childcount;
public:
    treenode(int data,int child)
    {
        this->data=data;
        childcount=child;
        children=new treenode*[childcount];
        int i=0;
        while(i<childcount)
        {

            children[i]=NULL;
            i++;
        }
    }                /* functioning of all functions are self explanatory by their names chosen*/
    friend treenode* makingtree(int,int);/*this function does not take input level wise*/
    friend void printingtree(treenode*);/*this function does not print tree level wise*/
    friend treenode* makingtreelevelwise();/*this functions takes input for tree level wise*/
    friend void printingtreelevelwise(treenode*);/*this prints tree level wise*/
    friend void printinginidealway(treenode*);/*this is a function which prints the tree in most ideal way*/
    friend int sumofallnodes(treenode*);/*returns sum of all nodes*/
    friend bool isidentical(treenode*,treenode*);/*returns boolean value after comparing two trees*/
    friend int largestvalue(treenode*);/*returns largest value in a tree*/
    friend int secondlargestvalue(treenode*,secondlargesthelper*);/*returns second largest value in a tree*/
    friend int countleafnodes(treenode*);/*returns count of total leaf nodes in a tree*/
    friend int height(treenode*);/*returns height of tree*/
    friend void replacingeverynodebydepthvalue(treenode*,int);/*all other remaining functions are self explanatory*/
    friend void printingallnodesatdepthk(treenode*,int,int);
    friend void countallnodeshavingdatagreaterthann(treenode*,int ,int&);
    friend int valuejustgreaterthann(treenode*,int,int);

};
class node/*This class is being used by queues and queues is being used by other functions related to tree*/
{
    public:
    treenode* data;
    node* next;

    node(treenode* data)
    {
        this->data=data;
        next=NULL;
    }

};
class queue{/*This is being used by functions of trees*/
    public:
node* front;
node* end;
queue()
{
    front=NULL;
    end=NULL;
}
void enqueue(treenode* data)
{
    node* newnode=new node(data);
    if(front==NULL)
    {
        front=newnode;
        end=newnode;
    }
    else
    {
        end->next=newnode;
        end=end->next;
    }
}
treenode* dequeue()
{
    if(isempty()==true)
    {
        return NULL;
    }
    node* k=front;
    treenode* temp=k->data;
    front=front->next;
    if(front==NULL)
    {
        end=NULL;
    }
    delete k;
    return temp;

}
bool isempty()
{
    if(front==NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

};
treenode* makingtree(int temp=INT_MAX,int p=-1)/*This does not take input level wise*/
{
    if(temp==INT_MAX)
    {
    cout<<"enter data and no. of children of root"<<endl;
    }
    else
    {
        cout<<"enter data of "<<p+1<<" child of "<<temp<<" and its no. of children "<<endl;
    }
    int data,children;
    cin>>data>>children;
    treenode* root=new treenode(data,children);
    int i=0;
    while(i<root->childcount)
    {
        root->children[i]=makingtree(root->data,i);
        i++;
    }
    return root;
}
void printingtree(treenode* root)/*This does not print tree level wise*/
{
    cout<<root->data<<endl;
    int i=0;
    while(i<root->childcount)
    {
        printingtree(root->children[i]);
        i++;
    }
}
treenode* makingtreelevelwise()
{
    cout<<"enter the data and no. of children of root"<<endl;
    int data,child;
    cin>>data>>child;
    treenode* root=new treenode(data,child);
    queue a;
    a.enqueue(root);
    while(!a.isempty())
    {
        treenode* temp=a.dequeue();
        int i=0;
        while(i<temp->childcount)
        {
            cout<<"enter data of "<<i+1<<" child of "<<temp->data<<" and its no. of children"<<endl;
            cin>>data>>child;
            treenode* newtreenode=new treenode(data,child);
            temp->children[i]=newtreenode;
            a.enqueue(newtreenode);
            i++;
        }
    }
    return root;
}
void printingtreelevelwise(treenode* root)
{
    cout<<"root:data "<<root->data<<endl;
    queue a;
    a.enqueue(root);
    while(!a.isempty())
    {
        treenode* temp=a.dequeue();
        int i=0;
        while(i<temp->childcount)
        {
            cout<<temp->children[i]->data<<" ";
            a.enqueue(temp->children[i]);
            i++;
        }

    }
    cout<<endl;
    return;
}
void printinginidealway(treenode* root)
{
    if(root==NULL)
    {
        return;
    }
    queue a;
    a.enqueue(root);
    while(!a.isempty())
    {
        treenode* temp=a.dequeue();
        cout<<temp->data<<" : ";
        int i=0;
        while(i<temp->childcount)
        {
            cout<<temp->children[i]->data<<" ";
            a.enqueue(temp->children[i]);
            i++;
        }
        cout<<endl;
    }
    return;
}
int sumofallnodes(treenode* root)
{
    if(root==NULL)
    {
        return 0;
    }
    else
    {
        int value=root->data;
        for(int i=0;i<root->childcount;i++)
        {
            value=value+sumofallnodes(root->children[i]);
        }
        return value;
    }
}
bool isidentical(treenode* root1,treenode* root2)
{
    if(root1==NULL&&root2==NULL)
    {
        return true;
    }
    else if(root1==NULL||root2==NULL)
    {
        return false;
    }
    else
    {
        if(root1->data==root2->data&&(root1->childcount==root2->childcount))
        {
            bool y=true;
            for(int i=0;i<root1->childcount;i++)
            {
                y=y*isidentical(root1->children[i],root2->children[i]);
            }
            return y;
        }
        else
        {
            return false;
        }
    }
}
int largestvalue(treenode *root)
{
    if(root==NULL)
    {
        return INT_MAX;
    }
    int largest=root->data;
    for(int i=0;i<root->childcount;i++)
    {
        int temp=largestvalue(root->children[i]);
        if(temp>largest)
        {
            largest=temp;
        }
    }
    return largest;
}
class secondlargesthelper/*this class is used by secondlargestvalue() function*/
{
public:
    int largest;
    int secondlargest;
    secondlargesthelper()
    {
        largest=INT_MIN;
        secondlargest=INT_MIN;
    }

};
int secondlargestvalue(treenode* root,secondlargesthelper *temp=new secondlargesthelper())
{
    if(root==NULL)
    {
        return INT_MIN;
    }
    if(root->data>=temp->largest)
    {
        temp->secondlargest=temp->largest;
        temp->largest=root->data;
    }
    else if(root->data>temp->secondlargest)
    {
        temp->secondlargest=root->data;
    }
    for(int i=0;i<root->childcount;i++)
    {
        secondlargestvalue(root->children[i],temp);
    }
    return temp->secondlargest;
}
int countleafnodes(treenode* root)
{
    if(root==NULL)
    {
        return 0;
    }
    int count=0;
    if(root->childcount==0)
        return 1;
    else
    {
        for(int i=0;i<root->childcount;i++)
        {
            count=count+countleafnodes(root->children[i]);
        }
        return count;
    }
}
int height(treenode* root)
{
    if(root==NULL||root->childcount==0)
    {
        return 0;
    }
    int max=INT_MIN;
    for(int i=0;i<root->childcount;i++)
    {
        int temp=height(root->children[i]);
        if(temp>max)
        {
            max=temp;
        }
    }
    return 1+max;
}
void replacingeverynodebydepthvalue(treenode* root,int depth=0)
{
    if(root==NULL)
    {
        return;
    }
    root->data=depth;
    for(int i=0;i<root->childcount;i++)
    {
        replacingeverynodebydepthvalue(root->children[i],depth+1);
    }
    return;
}
void printingallnodesatdepthk(treenode* root,int depth,int value=0)
{
    if(root==NULL)
    {
        return;
    }
    if(depth==value)
    {
        cout<<root->data<<" ";
        return;
    }
    for(int i=0;i<root->childcount;i++)
    {
        printingallnodesatdepthk(root->children[i],depth,value+1);
    }
    return;
}
void countallnodeshavingdatagreaterthann(treenode* root,int n,int &temp)
{
    if(root==NULL)
    {
        return ;
    }
    if(root->data>n)
    {
        temp=temp+1;
    }
    for(int i=0;i<root->childcount;i++)
    {
        countallnodeshavingdatagreaterthann(root->children[i],n,temp);
    }
}
int valuejustgreaterthann(treenode* root,int n,int min=INT_MAX)
{
    if(root==NULL)
    {
        return INT_MIN;
    }
    if(root->data>n&&root->data<min)
    {
        min=root->data;
    }
    for(int i=0;i<root->childcount;i++)
    {
        int temp=valuejustgreaterthann(root->children[i],n,min);
        if(temp>n&&temp<min)
        {
           min=temp;
        }
    }
    return min;

}






#endif // tree_h
