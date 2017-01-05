//MANY MORE FUNCTIONS TO COME
#ifndef binarysearchtree_h
#define binarysearchtree_h
class treenode
{
    int data;
    treenode* left;
    treenode* right;
public:
    treenode(int data)
    {
        this->data=data;
        left=NULL;
        right=NULL;
    }
    friend int LCA(treenode* root,int data1,int data2);
    friend treenode* Insertion(treenode*,int);
    friend treenode* Deletion(treenode*,int);
    friend treenode* DeletingWithOneorZeroChild(treenode*,treenode*,int);/*This is the function used by Deletion function*/
    friend void DeletingWithTwoChild(treenode*,int);/*This is the function used by Deletion function*/
    friend int Height(treenode*);
    friend void PrintRootToLeafPathsWhereSumOfAllNodesinPathIsEqualToGivenNumber(treenode*,int,int,int*);
    friend void ReplacingEachNodeDataWithSumOfGreaterNodesInTree(treenode*,int);
    friend int SumofAllNodes(treenode* root);
    friend void TwoNumbersWhichSumToX(treenode* root,int X);
    friend int* CreatingSortedArray(treenode*);
    friend treenode* FindMin(treenode*);/*This is the function used by DeletingWithTwoChild function*/
    friend treenode* MakingTree();
    friend void PrintingTree(treenode*);
    friend int SizeOfTree(treenode*);
    friend bool Search(treenode*,int);
    friend void CreatingDuplicateNodesOnLeft(treenode*);
};
class nodeforqueue
{
    public:
    treenode* data;
    nodeforqueue* next;
    nodeforqueue(treenode* data)
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
    void enqueue(treenode *data)
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
    treenode* dequeue()
    {
        if(front==NULL)
            return NULL;
        treenode* tobereturned=front->data;
        nodeforqueue* temp=front;
        front=front->next;
        delete temp;
        if(front==NULL)
            end=NULL;
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
treenode* MakingTree()
{
    int data;
    cout<<"enter root data"<<endl;
    cin>>data;
    treenode* root=new treenode(data);
    queue a;
    a.enqueue(root);
    while(!a.isempty())
    {
        treenode* temp=a.dequeue();
        cout<<"enter data of left child of "<<temp->data<<endl;
        cin>>data;
        if(data!=-1)
        {
        while(data>=temp->data)
        {
            cout<<"data of left child should be small from its parent"<<endl;
            cin>>data;
        }

        treenode* leftnewnode=new treenode(data);
        temp->left=leftnewnode;
        a.enqueue(leftnewnode);
        }
        cout<<"enter data of right child of "<<temp->data<<endl;
        cin>>data;
        if(data!=-1)
        {
        while(data<temp->data)
        {
            cout<<"data of right child should be greater from its parent"<<endl;
            cin>>data;
        }
        treenode* rightnewnode=new treenode(data);
        temp->right=rightnewnode;
        a.enqueue(rightnewnode);
        }

    }
    return root;
}
void PrintingTree(treenode* root)
{
    queue a;
    a.enqueue(root);
    while(!a.isempty())
    {
        treenode* temp=a.dequeue();
        cout<<temp->data<<" : ";
        if(temp->left!=NULL)
        {
            cout<<temp->left->data<<" ";
            a.enqueue(temp->left);
        }
        else
        {
            cout<<"  ";
        }
        if(temp->right!=NULL)
        {
            cout<<temp->right->data<<" ";
            a.enqueue(temp->right);
        }
        cout<<endl;
    }

}
treenode* Insertion(treenode* root,int data)
{
    if(root==NULL)
    {
        treenode* newnode=new treenode(data);
        return newnode;
    }
    else if(data<=root->data)
    {
        root->left=Insertion(root->left,data);
    }
    else
    {
        root->right=Insertion(root->right,data);
    }
}
treenode* DeletingWithOneorZeroChild(treenode* root,treenode* temp,int data)/*This is a function which is used by Deletion(treenode*,int)  function*/
{
    if(root==temp)
    {
        if(root->left!=NULL)
            root=root->left;
        else
        root=root->right;
        delete temp;
        return root;
    }
    else
    {
        treenode* p=root;
        while(p->left!=temp&&p->right!=temp)
        {
            if(data<=p->data)
                p=p->left;
            else
                p=p->right;
        }
        if(p->right==temp)
        {
            if(temp->left!=NULL)
                p->right=temp->left;
            else
                p->right=temp->right;
        }
        else
        {
            if(temp->left!=NULL)
                p->left=temp->left;
            else
                p->left=temp->right;
        }

        return root;
    }
}
treenode* FindMin(treenode* root)/*This is a function which is used by DeletingWithTwoChild(treenode*,int)  function*/
{
    while(root!=NULL&&root->left!=NULL)
    {
        root=root->left;
    }
    return root;
}

void DeletingWithTwoChild(treenode *temp,int data)/*This is a function which is used by Deletion(treenode*,int)  function*/
{
    treenode* mininrightsubtree=FindMin(temp->right);
    temp->data=mininrightsubtree->data;
    temp->right=Deletion(temp->right,mininrightsubtree->data);
}

treenode* Deletion(treenode* root,int data)
{
    treenode* temp=root;
    while(temp!=NULL&&temp->data!=data)
    {
        if(data>temp->data)
        {
            temp=temp->right;
        }
        else
        {
            temp=temp->left;
        }
    }
    if(temp!=NULL&&temp->left!=NULL&&temp->right!=NULL)
    {
        DeletingWithTwoChild(temp,data);
    }
    else
    {
        root=DeletingWithOneorZeroChild(root,temp,data);
    }
    return root;

}
int SizeOfTree(treenode *root)
{
    if(root!=NULL)
        return 1+SizeOfTree(root->left)+SizeOfTree(root->right);
    else
        return 0;
}
bool Search(treenode* root,int data)
{
    if(root==NULL)
        return false;
    else if(root->data==data)
        return true;
    else
    {
        if(data>root->data)
            return Search(root->right,data);
        else
            return Search(root->left,data);
    }
}
void CreatingDuplicateNodesOnLeft(treenode* root)
{
    if(root==NULL)
        return;
    else
    {
        treenode* newnode=new treenode(root->data);
        if(root->left==NULL)
            root->left=newnode;
        else
        {
            newnode->left=root->left;
            root->left=newnode;
        }
        CreatingDuplicateNodesOnLeft(newnode->left);
        CreatingDuplicateNodesOnLeft(root->right);
        return;

    }
}
class nodeforstack{
public:
    treenode* data;
    nodeforstack* next;
    nodeforstack(treenode* data){
        this->data=data;
        next=NULL;
    }
};
class stack{
    public:
  nodeforstack *top;
  stack(){
      top=NULL;
  }
  void push(treenode* data){
      nodeforstack* newnode=new nodeforstack(data);
      if(top==NULL){
          top=newnode;
      }
      else{
          newnode->next=top;
          top=newnode;
      }
  }
  treenode* pop(){
      if(top==NULL)
        return NULL;
      treenode* tobereturned=top->data;
      nodeforstack* temp=top;
      top=top->next;
      delete temp;
      return tobereturned;
  }
  bool isempty(){
      if(top==NULL)
        return true;
      else
        return false;
  }
};
int* CreatingSortedArray(treenode* root){
    int* array=new int[SizeOfTree(root)];
 stack s;
treenode* temp=root;
int index=0;
    while(!s.isempty()||temp!=NULL){
        while(temp!=NULL){
                s.push(temp);
                temp=temp->left;

        }
    treenode* k=s.pop();
        array[index]=k->data;
        index++;
        if(k->right!=NULL)
            temp=k->right;
    }
    cout<<endl;
    return array;
}
void TwoNumbersWhichSumToX(treenode* root,int X){
    int* array=CreatingSortedArray(root);
    for(int i=0,j=SizeOfTree(root)-1;i<j;){
        if(array[i]+array[j]==X){
            cout<<array[i]<<" "<<array[j]<<endl;
            return;
        }
        else if(array[i]+array[j]<X){
            i++;
        }
        else{
            j--;
        }
    }
    cout<<"sorry no solution"<<endl;
    return;
}
int LCA(treenode* root,int data1,int data2){
    if(root==NULL)
        return -1;
    else if(data1==root->data||data2==root->data)
        return root->data;
    else if((data1>root->data&&data2<root->data)||(data1<root->data&&data2>root->data))
        return root->data;
    else if(data1>root->data&&data2>root->data)
        return LCA(root->right,data1,data2);
    else
        return LCA(root->left,data1,data2);
}
int SumofAllNodes(treenode* root){
    if(root==NULL)
        return 0;
    else
        return root->data+SumofAllNodes(root->left)+SumofAllNodes(root->right);
}
void ReplacingEachNodeDataWithSumOfGreaterNodesInTree(treenode* root,int rightsubtreedata=0){
    if(root==NULL)
        return;
        int a=root->data;
        root->data=SumofAllNodes(root->right)+rightsubtreedata;
    ReplacingEachNodeDataWithSumOfGreaterNodesInTree(root->left,a+root->data);
    ReplacingEachNodeDataWithSumOfGreaterNodesInTree(root->right,rightsubtreedata);
    return;
}
int Height(treenode *root)
{
    if(root==NULL)
        return 0;
    else
        return 1+max(Height(root->left),Height(root->right));
}
void  PrintRootToLeafPathsWhereSumOfAllNodesinPathIsEqualToGivenNumber(treenode* root,int number,int index=0,int *array=NULL)
{
    if(root==NULL)
    {
        if(number==0)
        {
            for(int i=0;i<=index;i++)
            {
                cout<<array[i]<<" ";
            }
            cout<<endl;
        }
        return;
    }
    if(array==NULL)
        array=new int[Height(root)];
        array[index]=root->data;
    PrintRootToLeafPathsWhereSumOfAllNodesinPathIsEqualToGivenNumber(root->left,number-root->data,index+1,array);
    PrintRootToLeafPathsWhereSumOfAllNodesinPathIsEqualToGivenNumber(root->right,number-root->data,index+1,array);

}
#endif // binarysearchtree_h
