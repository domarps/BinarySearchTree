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

int depthQuery(struct node* temp_node,int key)
{
   while(temp_node != '\0')
   {
      if(temp_node->data == key)
      {
            return 0;
      }
      else if(key < temp_node->data && temp_node->leftChild != '\0')
      {
            return (1 + depthQuery(temp_node->leftChild,key));
      }
      else if(key > temp_node->data && temp_node->rightChild != '\0')
      {
            return(1 + depthQuery(temp_node->rightChild,key));
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


struct node* inOrderSuccessor(struct node *n)
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
struct node* Delete(struct node* temp_node,int key,int size)
{
     if(temp_node == '\0') return temp_node;
  
      if(temp_node->data == key)
      {	      
       if(!(temp_node->leftChild != '\0' && temp_node->rightChild != '\0'))  //Node does not have two children,no inorder successor replacement required
       {
	      if(temp_node->leftChild == '\0' && temp_node->rightChild == '\0')   //Node has zero children
	      {      	 
           if(temp_node->parent->leftChild == temp_node)             temp_node->parent->leftChild = '\0'; //if Node is the leftChild  of parent   
           else                                                      temp_node->parent->rightChild = '\0'; //if Node is the rightChild of parent
	        free(temp_node);
           return '\0';
         }
	      else if(temp_node->rightChild == '\0' && temp_node->leftChild != '\0') //Node has a leftChild
	      {
           struct node *sub = temp_node->leftChild;
		     temp_node->leftChild->parent = temp_node->parent;
		     temp_node->parent            = temp_node->leftChild->parent;
		     free(temp_node);
           return sub;
         }
	      else                                                                   //Node has a rightChild
         {
           struct node *sub = temp_node->rightChild;
		     temp_node->rightChild->parent = temp_node->parent;
		     temp_node->parent             = temp_node->rightChild->parent;
		     free(temp_node);
           return sub;
	      }
       }	 
       else //Node has two children
       {
         //Find its inorder successor which is succ
         struct node* succ = inOrderSuccessor(temp_node);
         if(succ == '\0') //What if there is no inorder successor
         {
          //No inorder successor, but technically it should have
          if(temp_node->parent->leftChild == temp_node) temp_node->parent->leftChild = '\0';
          else                                          temp_node->parent->rightChild = '\0';
          free(temp_node);
          temp_node = '\0';
         }
        else
        {
          temp_node->data = succ->data;   //replace the node's data with the inorder successor's data
          //Let the successor be removed from the BST, it can fall in one of the four categories
          //But first find if succ is the left or Right Child of its parent
          //*****************************************************************//
          temp_node->rightChild = Delete(temp_node->rightChild,succ->data,size);
        } 
       } 
      } 
      else if(key < temp_node->data)    temp_node->leftChild  = Delete(temp_node->leftChild,key,size);
      else                              temp_node->rightChild = Delete(temp_node->rightChild,key,size);
      return temp_node;
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

