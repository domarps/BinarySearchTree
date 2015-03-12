# BinarySearchTree
Construct and maintain a Binary Search Tree
** Insert: Insert a given key into the BST such that the tree remains a BST. That is, the node has to be inserted at the appropriate position so that a binary search can be done during lookup of a key. If the input key is already present in the tree, it must print the postorder sequence of the existing tree.
** Remove: Remove a given key from the tree. In case of a node having both children replace it with inorder successor.
** Query: The program has to return the depth of a node, given root is at depth 0.
** Size: Given a key, your program has to return the number of nodes in the subtree rooted at the key value.  

Input:

** The first line gives the number of items in the initial tree.
** The next line of the input gives the key values for the tree. You may use the approach described in the lectures to create the tree using the values provided. The values have to be inserted in the same order as is being input.
** The third line indicates the number of operations to be performed on the tree.
** From fourth line onwards, each line will specify the operation to be performed along with key(s). The operations will use the following symbols:
------- i : insert
------- r : remove
------- q : query
------- s : size

Output:

** The lines of output has to be in the exact same order as the input.
** The first line of output should be the postorder traversal sequence of the constructed tree.
** The result for each operation has to be displayed in a new line.
** For insert and remove operations, the postorder traversal sequence of the new tree must be printed. If a duplicate key is found during insertion it must print the postorder sequence of the existing tree.
** For query, it must return the depth at which the key was found. If the key is absent, return -1.
** For size, it has to display the number of nodes in the subtree rooted at the key value including the node itself. If the input value is in a leaf node, output 1.  If the input value is in the root, return the size of the whole tree.
