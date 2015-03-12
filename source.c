#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
int lastLabel = 0;
int lDepth = 0;
int rDepth = 0;
typedef int boolean; 
struct node
{
    int data;
    int label;
    struct node* parent;
    struct node* rightChild;
    struct node* leftChild;
};

struct node* createNode(int d)
{
   struct node* newN = (struct node*)malloc(sizeof(struct node));
   newN->data = d;
   newN->leftChild  = '\0';
   newN->rightChild = '\0';
   newN->parent     = '\0';
   lastLabel++;
   newN->label      = lastLabel;
   return newN;
}
struct Queue
{
   int front,rear;
   int size;
   struct node** array;
};

typedef struct tree
{
   struct node* root;
   int size;
}BinaryTree;

////////Binary Tree Helper Functions//////////////////////
BinaryTree* createTree()
{
     BinaryTree* t = (BinaryTree*)malloc(sizeof(BinaryTree));
     t->root       = '\0';
     t->size       = 0;
     return t;
}

int size(BinaryTree *t)
{
   return t->size;
}

struct node* root(BinaryTree *t)
{
    return t->root;
}

struct node* parent(struct node* n)
{
   return n->parent;
}

int isInternal(struct node *n)
{
   return n->leftChild != '\0' || n->rightChild != '\0';
}

int isExternal(struct node *n)
{
        return !isInternal(n);
}

int isRoot(struct node* n)
{
   return n->parent == '\0';
}

int hasBothChild(struct node* temp)        
{
      if((temp!= '\0') && (temp->leftChild != '\0') && (temp->rightChild != '\0')) return 1;
}
////////Binary Tree Helper Functions//////////////////////
boolean isPresent(struct node* root,int key)
{
  while(root != '\0')
  {
    if(root->data == key) return TRUE;
    else if(key < root->data && root->leftChild != '\0') 
    {
       root = root->leftChild;
    }
    else if(key > root->data && root->rightChild != '\0')
    {
      root = root->rightChild;
    }
    else return FALSE;
  }
}

//Helper function to find the number of nodes of a particular subTree
int maxDepth(struct node* stree)
{
  if(stree == '\0') return 0;
  else              
  {
     lDepth = maxDepth(stree->leftChild);
     rDepth = maxDepth(stree->rightChild);
     if(lDepth > rDepth) return (lDepth + 1);
     else                return (rDepth + 1);
  }
} 
int depthQuery(struct node* root,int key)
{
   struct node  *temp_node   = root;   
   while(temp_node != '\0')
   {
      if(temp_node->data == key)
      {
            return maxDepth(temp_node);
      }
      else if(key < temp_node->data && temp_node->leftChild != '\0')
      {
            temp_node = temp_node->leftChild;
      }
      else if(key > temp_node->data && temp_node->rightChild != '\0')
      {
            temp_node = temp_node->rightChild;
      }
      else
      {
            return -1;        
      }
   }  
 }


//sizeFind Helper to return the subtree. Cannot Live without sizeQuery
int sizeFind(struct node* stree)
{
  if(stree == '\0') return 0;
  else              return(sizeFind(stree->leftChild) + 1 + sizeFind(stree->rightChild));
} 
//Helper function to find the  particular nodes given the node's key
int sizeQuery(struct node* root,int key)
{
   struct node  *temp_node   = root;   
   while(temp_node != '\0')
   {
      if(temp_node->data == key)
      {
            return sizeFind(temp_node);
      }
      else if(key  < temp_node->data && temp_node->leftChild != '\0')
      {
            temp_node = temp_node->leftChild;
      }
      else if(key > temp_node->data && temp_node->rightChild != '\0')
      {
            temp_node = temp_node->rightChild;
      }
      else
      {
            return -1;        
      }
   }
}

    
//insert data in the pre-existing Complete Binary Tree
struct node* insert(struct node* root,int data)
{
  if(root == '\0')
  {
   struct node* temp = createNode(data);
   root = temp;
  }
  else if(data <= root->data)
  {
       if(root->leftChild != '\0')
       {
               insert(root->leftChild,data);
       }
       else
       {
           struct node* temp = createNode(data);
           temp->parent      = root;
           root->leftChild   = temp;
       }
  }
  else
  {
       if(root->rightChild != '\0')        insert(root->rightChild,data);
       else
       {
           struct node* temp = createNode(data);
           temp->parent      = root;
           root->rightChild  = temp;
       }
  }
  return root;
}
//perform InOrder Traversal                              
void postOrder(struct node* root)
{
   if(root == '\0') return;
   if(isInternal(root)) postOrder(root->leftChild);
   if(isInternal(root)) postOrder(root->rightChild);
   printf("%d ", root->data);
}
struct node* minValue(struct node* node)
{
  struct node* currentNode = node;
  while(currentNode->leftChild != '\0' )
  {
    currentNode = currentNode->leftChild;
  }
  return (currentNode);
}


struct node* inOrderSuccessor(struct node* root,struct node *n)
{
  if(n->rightChild != '\0') 
  {
     return minValue(n->rightChild);
  }
  struct node* succ = n->parent;
  //printf("A %d %d \n",succ->data,n->data);
  if(succ != '\0' && succ->rightChild == '\0')  
  {
    //printf("B %d %d \n",succ->data,n->data);
    return succ;
  }
  //printf(" C %d %d \n",succ->data,n->data);
  while(succ != '\0' && n  == succ->rightChild)
  {
    
      n = succ;
      succ = succ->parent;
      
  }
  return succ;
}

//The helper function will remove the node containing the Key(multiple instances possible), then it would replace that node with the Last Node
struct node* Delete(struct node* root,int key,int size)
{
    struct node  *temp_node   = root;

    while(temp_node != '\0')
    {
      if(temp_node->data == key)
      {
        
        //Find its inorder successor which is succ
        struct node* succ = inOrderSuccessor(root,temp_node);
        //printf(" C %d %d \n",succ->data,temp_node->data);
       
        if(succ == '\0') //What if there is no inorder successor
        {
          //No inorder successor
          if(temp_node->parent->leftChild == temp_node) temp_node->parent->leftChild = '\0';
          else                                          temp_node->parent->rightChild = '\0';
          free(temp_node);
          temp_node = '\0';
          return root;
        }
        else
        {
          temp_node->data = succ->data;
          //Let the successor be removed from the BST, four ways
          //But first find if succ is the left or Right Child of its parent
          //*****************************************************************//
          int flagLR;
          if(succ->parent->leftChild == succ) flagLR = 0; //0 for LEFT CHILD
          else                                flagLR = 1; //1 for RIGHT CHILD
          //*****************************************************************//
          
          //Case 1 : succ is an External Node
          if(isExternal(succ) && succ->parent != '\0') 
          {
                       if(succ->parent->leftChild == succ) succ->parent->leftChild = '\0';
                       else                                succ->parent->rightChild = '\0';
                       free(succ);
          }  
          //Case 2 : succ is an Internal Node with two children
          else if((hasBothChild(succ) == 1))
          {
              succ->parent->leftChild  = succ->leftChild;
              succ->parent->rightChild = succ->rightChild;  
              succ->leftChild->parent  = succ->parent;
              succ->rightChild->parent = succ->parent;
          } 
          //Case 3 : succ is the leftChild of the parent
          else if(succ->leftChild != '\0' )
          {
            succ->leftChild->parent  = succ->parent;
            if(flagLR == 0)
            {
                    succ->parent->leftChild  = succ->leftChild;
            }
            else
            {
                    succ->parent->rightChild = succ->leftChild;
            }
          }
         //Case 4 : succ is the rightChild of the parent
          else
          {
           succ->rightChild->parent  = succ->parent;
           if(flagLR == 0)
            {
                    succ->parent->rightChild  = succ->rightChild;
            }
            else
            {
                         succ->parent->rightChild = succ->rightChild;
            }
          }
        } 
        return root;       
      } 
      else if(key < temp_node->data && temp_node->leftChild != '\0')
      {
       //     printf("Fuck Up \n"); 
            temp_node = temp_node->leftChild;
      }
      else if(key > temp_node->data && temp_node->rightChild != '\0')
      {
            temp_node = temp_node->rightChild;
      }
      else
      {
            return '\0';  
      }      
   }
}    
   
int main()
{
   int num_items;
   int key;
   int num_Ops;
   char op;
   int op_key;
   int ctr;
   int qcount;
   int i;
   int stree_ctr;
   scanf("%d",&num_items); 
   boolean  res;
   struct node*  root = '\0';
   for(ctr = 0; ctr < num_items; ctr++)
   {
      scanf("%d",&key);
      root =  insert(root,key);
   }
   postOrder(root);
   printf("\n");
   scanf("%d",&num_Ops);
   for(i = 0; i < num_Ops ; i++)
   {     
     while((op = getchar())== '\n');
     scanf("%d",&op_key);
     if(op ==  'i') 
      {
                       res = isPresent(root,op_key);
                       if(res == TRUE)
                       {

                       }
                       else
                       {
                          root = insert(root,op_key);
                       }
                          postOrder(root);
                          printf("\n");
                       
      }
      else if(op == 'q')
      {  
                       lDepth = 0;
                       rDepth = 0;
                       if(isPresent(root,op_key)==FALSE) 
                       {
                         printf("-1\n");
                       }
                       else
                       {  
                         qcount = depthQuery(root,op_key);
                         printf("%d\n",qcount);
                       }  
      }               
      else if(op == 's')
      {
                       stree_ctr = sizeQuery(root,op_key);
                       printf("%d\n",stree_ctr);
      }
      else if(op == 'r')
      {
                    root = Delete(root,op_key,lastLabel);
                    postOrder(root);
                    printf("\n");
      }
   }
   return 0;
}

