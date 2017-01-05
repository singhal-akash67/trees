#include<stdlib.h>
#include<climits>
#ifndef binarytree_h
#define binarytree_h
class MaxBst;/*This is class used by MaxBstInBinaryTreeEfficient(binarytreenode*)*/
class nodeforlinkedlist;
class binarytreenode{
    int data;
    binarytreenode* left;
    binarytreenode* right;
public:
    binarytreenode(int data){
        this->data=data;
        left=NULL;
        right=NULL;
    };
    friend MaxBst MaxBstInBinaryTreeEfficient(binarytreenode*);
    friend binarytreenode* MaxBstInBinaryTree(binarytreenode*);
    friend int IsBst(binarytreenode*);/*This is used by above function*/
    friend void PrintRootToLeafPathsWhereSumOfAllNodesinPathIsEqualToGivenNumber(binarytreenode*,int,int,int*);
    friend void PrintingLevelsInZigZagManner(binarytreenode* );
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
    friend void InorderTraversalIteratively(binarytreenode*);
    friend void PreorderTraversalRecursively(binarytreenode*);
    friend void PreorderTraversalIteratively(binarytreenode*);
    friend void PostorderTraversalRecursively(binarytreenode*);
    friend void PostorderTraversalIteratively(binarytreenode*);
    friend binarytreenode* MakingBinaryTree();
    friend void PrintingTree(binarytreenode*);
    friend int TotalNumberOfNodes(binarytreenode*);
};
class nodeforqueue{
public:
    binarytreenode* data;
    nodeforqueue* next;
    nodeforqueue(binarytreenode* data){
        this->data=data;
        next=NULL;
    }
};
class queue{
    nodeforqueue* front;
    nodeforqueue* end;
    public:
        queue(){
            front=NULL;
            end=NULL;
        }
        void enqueue(binarytreenode* data){
            nodeforqueue* newnode=new nodeforqueue(data);
            if(front==NULL){
                front=newnode;
                end=newnode;
            }
            else{
                end->next=newnode;
                end=newnode;
            }
        }
        binarytreenode* dequeue(){
            if(isempty())
                return NULL;
            nodeforqueue* temp=front;
            front=front->next;
            if(front==NULL)
                end=NULL;
            binarytreenode* tobereturned=temp->data;
            delete temp;
            return tobereturned;
        }
        bool isempty(){
            if(front==NULL)
                return true;
            else
                return false;
        }
};
class nodeforstack{
public:
    binarytreenode* data;
    nodeforstack* next;
    nodeforstack(binarytreenode* data){
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
  void push(binarytreenode* data){
      nodeforstack* newnode=new nodeforstack(data);
      if(top==NULL){
          top=newnode;
      }
      else{
          newnode->next=top;
          top=newnode;
      }
  }
  binarytreenode* pop(){
      if(top==NULL)
        return NULL;
      binarytreenode* tobereturned=top->data;
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
binarytreenode* MakingBinaryTree(){
    cout<<"data of root"<<endl;
    int data;
    cin>>data;
    binarytreenode* root=new binarytreenode(data);
    queue a;
    a.enqueue(root);
    while(!a.isempty()){
        binarytreenode* temp=a.dequeue();
        cout<<"Enter left child of "<<temp->data<<endl;
        cin>>data;
        if(data!=-1){
        binarytreenode* leftnewnode=new binarytreenode(data);
        temp->left=leftnewnode;
        a.enqueue(temp->left);
        }
        cout<<"Enter right child of "<<temp->data<<endl;
        cin>>data;
        if(data!=-1){
        binarytreenode* rightnewnode=new binarytreenode(data);
        temp->right=rightnewnode;
        a.enqueue(temp->right);
        }
    }
    return root;
}
void PrintingTree(binarytreenode* root){
    queue a;
    if(root!=NULL){
    cout<<"root data : "<<root->data<<endl;
    a.enqueue(root);
    }
    while(!a.isempty()){
        binarytreenode* temp=a.dequeue();
        cout<<temp->data<<" : ";
        if(temp->left!=NULL){
            cout<<temp->left->data<<" ";
            a.enqueue(temp->left);
        }
        if(temp->right!=NULL){
            cout<<temp->right->data<<" ";
            a.enqueue(temp->right);
        }
        cout<<endl;
    }
}
int TotalNumberOfNodes(binarytreenode* root){
    if(root!=NULL){
        return 1+TotalNumberOfNodes(root->left)+TotalNumberOfNodes(root->right);
    }
    else{
        return 0;
    }
}
int HeightOfTree(binarytreenode* root){
    if(root==NULL)
        return 0;
    else return 1+max(HeightOfTree(root->left),HeightOfTree(root->right));
}

int Diameter(binarytreenode* root){
    if(root==NULL)
        return 0;
    return max(HeightOfTree(root->left)+HeightOfTree(root->right)+1,max(Diameter(root->left),Diameter(root->right)));
}
void MirrorTree(binarytreenode* root){
    if(root==NULL)
       return;
    swap(root->left,root->right);
    MirrorTree(root->left);
    MirrorTree(root->right);
}
void InorderTraversalRecursively(binarytreenode* root){
    if(root==NULL)
        return;
    InorderTraversalRecursively(root->left);
    cout<<root->data<<endl;
    InorderTraversalRecursively(root->right);
}
void InorderTraversalIteratively(binarytreenode* root){
    stack s;
binarytreenode* temp=root;

    while(!s.isempty()||temp!=NULL){
        while(temp!=NULL){
                s.push(temp);
                temp=temp->left;

        }
        binarytreenode* k=s.pop();
        cout<<k->data<<" ";
        if(k->right!=NULL)
            temp=k->right;
    }
    cout<<endl;
    return;
}
void PreorderTraversalRecursively(binarytreenode* root){
    if(root==NULL)
        return;
        cout<<root->data<<endl;
    PreorderTraversalRecursively(root->left);
    PreorderTraversalRecursively(root->right);
}
void PreorderTraversalIteratively(binarytreenode* root){
    stack s;
    s.push(root);
    while(!s.isempty()){
        binarytreenode* temp=s.pop();
        cout<<temp->data<<" ";
        if(temp->right!=NULL){
            s.push(temp->right);
        }
        if(temp->left!=NULL){
            s.push(temp->left);
        }
    }
    cout<<endl;
    return;
}
void PostorderTraversalRecursively(binarytreenode* root){
    if(root==NULL)
        return;
    PostorderTraversalRecursively(root->left);
    PostorderTraversalRecursively(root->right);
    cout<<root->data<<endl;
}
void PostorderTraversalIteratively(binarytreenode* root){
    stack main,aux;
    main.push(root);
    while(!main.isempty()){
        binarytreenode* temp=main.pop();
        aux.push(temp);
        if(temp->left!=NULL)
            main.push(temp->left);
        if(temp->right!=NULL)
            main.push(temp->right);
    }
    while(!aux.isempty()){
        cout<<aux.pop()->data<<" ";
    }
    cout<<endl;
}
int SumOfAllNodes(binarytreenode* root){
    if(root==NULL)
        return 0;
    else
        return root->data+SumOfAllNodes(root->left)+SumOfAllNodes(root->right);
}
bool IsStructurallyIdentical(binarytreenode* root1,binarytreenode* root2){
    if(root1==NULL&&root2==NULL)
        return true;
    else if(root1!=NULL&&root2!=NULL&&root1->data==root2->data)
        return true*IsStructurallyIdentical(root1->left,root2->left)*IsStructurallyIdentical(root1->right,root2->right);
    else
        return false;
}
bool IsBalanced(binarytreenode* root){
    if(root==NULL)
        return true;
    else if(abs(HeightOfTree(root->left)-HeightOfTree(root->right))<=1)
        return true*IsBalanced(root->left)*IsBalanced(root->right);
    else
        return false;
}
class nodeforlinkedlist{
    public:
    binarytreenode* value;
    nodeforlinkedlist* next;
    nodeforlinkedlist(){
    }
    nodeforlinkedlist(binarytreenode* value){
        this->value=value;
        next=NULL;
    }
};
nodeforlinkedlist** CreatingLinkedListForLevels(binarytreenode* root){
    nodeforlinkedlist** array=new nodeforlinkedlist*[HeightOfTree(root)];
    queue a;
    a.enqueue(root);
    int previous=1;
    int levels=0;
    while(!a.isempty()){
        int currentvalue=0;
        nodeforlinkedlist* head=NULL;
        nodeforlinkedlist* prev=NULL;
        while(previous>0){
            binarytreenode* temp=a.dequeue();
            nodeforlinkedlist* newnode=new nodeforlinkedlist(temp);
            if(head==NULL){
                head=newnode;
                prev=newnode;
            }
            else{
                prev->next=newnode;
                prev=newnode;
            }
            if(temp->left!=NULL){
                a.enqueue(temp->left);
                currentvalue++;
            }
            if(temp->right!=NULL){
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
void PrintingAllNodesThatDoNotHaveSibling(binarytreenode* root){
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
        else{
            PrintingAllNodesThatDoNotHaveSibling(root->left);
            PrintingAllNodesThatDoNotHaveSibling(root->right);
        }
}
binarytreenode* DeleteAllLeafNodes(binarytreenode* root){
    if(root==NULL)
        return NULL;
    if(root->left==NULL&&root->right==NULL){
        delete root;
        return NULL;
    }
    else{
        root->left=DeleteAllLeafNodes(root->left);
        root->right=DeleteAllLeafNodes(root->right);
    }
    return root;
}
void PrintingLevelsInZigZagManner(binarytreenode* root){
    queue a;
    a.enqueue(root);
    int level=0;
    while(!a.isempty()){
        stack b;
        while(!a.isempty()){
            binarytreenode* temp=a.dequeue();
            cout<<temp->data<<" ->";
            if(level%2==1){
                if(temp->left!=NULL){
                    b.push(temp->left);
                }
                if(temp->right!=NULL){
                    b.push(temp->right);
                }
            }
            else{
                if(temp->right!=NULL){
                    b.push(temp->right);
                }
                if(temp->left!=NULL){
                    b.push(temp->left);
                }

            }
        }
        level++;
        cout<<endl;
        while(!b.isempty()){
            binarytreenode* r=b.pop();
            a.enqueue(r);
        }
    }
}
void  PrintRootToLeafPathsWhereSumOfAllNodesinPathIsEqualToGivenNumber(binarytreenode* root,int number,int index=0,int *array=NULL)
{
    if(root==NULL)
        return;

    if(root->left==NULL&&root->right==NULL)
    {
        if(number-root->data==0)
        {
            array[index]=root->data;
            for(int i=0;i<=index;i++)
            {
                cout<<array[i]<<" ";
            }
            cout<<endl;
        }
        return;
    }
    if(array==NULL)
        array=new int[HeightOfTree(root)];
        array[index]=root->data;
    PrintRootToLeafPathsWhereSumOfAllNodesinPathIsEqualToGivenNumber(root->left,number-root->data,index+1,array);
    PrintRootToLeafPathsWhereSumOfAllNodesinPathIsEqualToGivenNumber(root->right,number-root->data,index+1,array);

}
int IsBst(binarytreenode* root)
{
    if(root==NULL)
        return 0;
    else if((root->left==NULL||(root->left!=NULL&&root->data>root->left->data))&&(root->right==NULL||(root->right!=NULL&&root->data<=root->right->data)))
        return 1+IsBst(root->left)+IsBst(root->right);
    else
        return INT_MIN;
}
binarytreenode* MaxBstInBinaryTree(binarytreenode* root)
{
    if(root==NULL)
        return NULL;
    int a=IsBst(root);
    if(a>0)
        return root;
    else
            return TotalNumberOfNodes(MaxBstInBinaryTree(root->left))>TotalNumberOfNodes(MaxBstInBinaryTree(root->right))? MaxBstInBinaryTree(root->left): MaxBstInBinaryTree(root->right);



}
class MaxBst
{
public:
    int size;
    binarytreenode* temp;
    MaxBst()
    {
        size=-1;
        temp=NULL;
    }
};
MaxBst MaxBstInBinaryTreeEfficient(binarytreenode* root)
{
    if(root==NULL)
    {
        MaxBst xyz;
        return xyz;
    }
    MaxBst left=MaxBstInBinaryTreeEfficient(root->left);
    MaxBst right=MaxBstInBinaryTreeEfficient(root->right);
    if(left.temp==NULL&&right.temp==NULL)
    {
        left.temp=root;
        left.size=left.size+2;
        return left;
    }
    if(root->left!=left.temp||root->right!=right.temp)
    {
        return left.size>right.size ? left:right;
    }
    else
    {
        if((root->left==NULL||(root->left!=NULL&&root->data>root->left->data))&&(root->right==NULL||(root->right!=NULL&&root->data<=root->right->data)))
            {
                MaxBst xyz;
                if(left.size!=-1)
                    xyz.size=left.size;
                if(right.size!=-1)
                xyz.size=xyz.size+right.size;
                xyz.size++;
                xyz.temp=root;
                return xyz;
            }
            else{
                return left.size>right.size ? left:right;
            }
    }

}
#endif // binarytree_h
