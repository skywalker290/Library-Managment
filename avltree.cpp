#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class Node
{
	public:
	int key;
	Node *left;
	Node *right;
	int height;
};

int max(int a, int b)
{
	return (a > b)? a : b;
}

class Queue{
    public:
    Node **data;
    int front;
    int rear;
    int size;

    Queue(){
        data=NULL;
        front=rear=0;
    }

    Queue(int x){
        data=new Node*[x];
        front=rear=0;
        size=x;
    }

    void enqueue(Node* x){
        if(rear!=size-1){
            data[rear++]=x;
        }
    }

    Node* dequeue(){
        if(rear!=front){
            return data[front++];
        }
    }

    bool isempty(){
        return rear==front;
    }
};

class Stack{
    public:
    int size;
    int top;
    Node **st;

    Stack(int siz){
        st=new Node*[siz];
        top=-1;
        size=siz; 
    }
    
    void push(Node *t){
        if(top!=size-1){
            top++;
            st[top]=t;
        }
    }
    Node* pop(){
        if(top!=-1){
            return st[top--];
        }
        return NULL;
    }
    bool isfull(){
        if(top==size-1){
            return true;
        }
        else{
            return false;
        }
    }

    bool isempty(){
        if(top==-1){
            return true;
        }
        else{
            return false;
        }
    }
};


class AVL{
    public:
    Node *root;

    AVL(){
        root=NULL;
    }

    Node* newNode(int key)
    {
        Node* node = new Node();
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        node->height = 1; // new node is initially
                        // added at leaf
        return(node);
    }

    void insert(int key){
        root=push(root,key);
    }

    void Delete(int key){
        root=deleteNode(root,key);
    }

    int height(Node *N)
    {
        if (N == NULL)
            return 0;
        return N->height;
    }

    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(height(y->left),
                        height(y->right)) + 1;
        x->height = max(height(x->left),
                        height(x->right)) + 1;

        // Return new root
        return x;
    }

    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(height(x->left),
                        height(x->right)) + 1;
        y->height = max(height(y->left),
                        height(y->right)) + 1;

        // Return new root
        return y;
    }

    int getBalance(Node *N)
    {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }

    Node* push(Node* node, int key)
    {
        /* 1. Perform the normal BST rotation */
        if (node == NULL && root==NULL){
            root=newNode(key);
            return root;
        }
        
        if (node == NULL ){
            return(newNode(key));
        }
            
        if (key < node->key)
            node->left = push(node->left, key);
        else if (key > node->key)
            node->right = push(node->right, key);
        else
            return node;

        /* 2. Update height of this ancestor node */
        node->height = 1 + max(height(node->left),
                            height(node->right));

        /* 3. Get the balance factor of this ancestor
            node to check whether this node became
            unbalanced */
        int balance = getBalance(node);

        // If this node becomes unbalanced, then
        // there are 4 cases

        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }

    Node * minValueNode(Node* node)
    {
        Node* current = node;

        /* loop down to find the leftmost leaf */
        while (current->left != NULL)
            current = current->left;

        return current;
    }

    Node* deleteNode(Node* root, int key)
    {
        
        // STEP 1: PERFORM STANDARD BST DELETE
        if (root == NULL)
            return root;

        // If the key to be deleted is smaller
        // than the root's key, then it lies
        // in left subtree
        if ( key < root->key )
            root->left = deleteNode(root->left, key);

        // If the key to be deleted is greater
        // than the root's key, then it lies
        // in right subtree
        else if( key > root->key )
            root->right = deleteNode(root->right, key);

        // if key is same as root's key, then
        // This is the node to be deleted
        else
        {
            // node with only one child or no child
            if( (root->left == NULL) ||
                (root->right == NULL) )
            {
                Node *temp = root->left ?
                            root->left :
                            root->right;

                // No child case
                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else // One child case
                *root = *temp; // Copy the contents of
                            // the non-empty child
                free(temp);
            }
            else
            {
                // node with two children: Get the inorder
                // successor (smallest in the right subtree)
                Node* temp = minValueNode(root->right);

                // Copy the inorder successor's
                // data to this node
                root->key = temp->key;

                // Delete the inorder successor
                root->right = deleteNode(root->right,
                                        temp->key);
            }
        }

        // If the tree had only one node
        // then return
        if (root == NULL)
        return root;

        // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
        root->height = 1 + max(height(root->left),
                            height(root->right));

        // STEP 3: GET THE BALANCE FACTOR OF
        // THIS NODE (to check whether this
        // node became unbalanced)
        int balance = getBalance(root);

        // If this node becomes unbalanced,
        // then there are 4 cases

        // Left Left Case
        if (balance > 1 &&
            getBalance(root->left) >= 0)
            return rightRotate(root);

        // Left Right Case
        if (balance > 1 &&
            getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 &&
            getBalance(root->right) <= 0)
            return leftRotate(root);

        // Right Left Case
        if (balance < -1 &&
            getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
}

    void preorder(){
        Node *t=root;
        Stack st(110);

        while(t!=NULL || !st.isempty()){
            
            if(t!=NULL){
                cout<<t->key<<" ";
                st.push(t);
                t=t->left;
            }

            else{
                t=st.pop();
                t=t->right;
            }
        }

    }
        
    void inorder(){
        Node *t=root;
        Stack st(100);

        while(t!=NULL || !st.isempty()){
            
            if(t!=NULL){
                st.push(t);
                t=t->left;
            }

            else{
                t=st.pop();
                cout<<t->key<<" ";
                t=t->right;
            }
        }

    }
    
    void levelorder(){
        Node *t=root;   
        Queue q(100);
        q.enqueue(t);
        while(!q.isempty()){
            t=q.dequeue();
            if(t!=NULL){
                cout<<t->key<<" ";

                if(t->left!=NULL){
                    q.enqueue(t->left);
                }
                
                if(t->right!=NULL){
                    q.enqueue(t->right);
                }
            }
        }
    }


};


int main()
{
    AVL t1;
    
	t1.insert(10);
	t1.insert(20);
	t1.insert(30);
	t1.insert(40);
	t1.insert(50);
	t1.insert(25);
    t1.Delete(10);
	
	cout << "Preorder traversal of the "
			"constructed AVL tree is \n";
	t1.preorder();
	
	return 0;
}



