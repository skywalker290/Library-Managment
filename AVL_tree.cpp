#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class Cred
{
	public:
	string username;
	string password;
	Cred *left;
	Cred *right;
	int height;
};

int max(int a, int b)
{
	return (a > b)? a : b;
}

class Queue{
    public:
    Cred **data;
    int front;
    int rear;
    int size;

    Queue(){
        data=NULL;
        front=rear=0;
    }

    Queue(int x){
        data=new Cred*[x];
        front=rear=0;
        size=x;
    }

    void enqueue(Cred* x){
        if(rear!=size-1){
            data[rear++]=x;
        }
    }

    Cred* dequeue(){
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
    Cred **st;

    Stack(int siz){
        st=new Cred*[siz];
        top=-1;
        size=siz; 
    }
    
    void push(Cred *t){
        if(top!=size-1){
            top++;
            st[top]=t;
        }
    }
    Cred* pop(){
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


class loginData{
    public:
    Cred *root;

    loginData(){
        root=NULL;
    }

    Cred* newCred(string username,string password)
    {
        Cred* CCred = new Cred();
        CCred->username = username;
        CCred->password = username;
        CCred->left = NULL;
        CCred->right = NULL;
        CCred->height = 1; // new Cred is initially
                        // added at leaf
        return(CCred);
    }

    void insert(string username,string password){
        root=push(root,username,password);
    }

    void Delete(string username){
        root=deleteCred(root,username);
    }

    int height(Cred *N)
    {
        if (N == NULL)
            return 0;
        return N->height;
    }

    Cred *rightRotate(Cred *y)
    {
        Cred *x = y->left;
        Cred *T2 = x->right;

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

    Cred *leftRotate(Cred *x)
    {
        Cred *y = x->right;
        Cred *T2 = y->left;

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

    int getBalance(Cred *N)
    {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }

    Cred* push(Cred* Cred, string username,string password)
    {
        /* 1. Perform the normal BST rotation */
        if (Cred == NULL && root==NULL){
            root=newCred(username,password);
            return root;
        }
        
        if (Cred == NULL ){
            return(newCred(username,password));
        }
            
        if (username < Cred->username)
            Cred->left = push(Cred->left, username,password);
        else if (username > Cred->username)
            Cred->right = push(Cred->right, username,password);
        else
            return Cred;

        /* 2. Update height of this ancestor Cred */
        Cred->height = 1 + max(height(Cred->left),
                            height(Cred->right));

        /* 3. Get the balance factor of this ancestor
            Cred to check whether this Cred became
            unbalanced */
        int balance = getBalance(Cred);

        // If this Cred becomes unbalanced, then
        // there are 4 cases

        // Left Left Case
        if (balance > 1 && username < Cred->left->username)
            return rightRotate(Cred);

        // Right Right Case
        if (balance < -1 && username > Cred->right->username)
            return leftRotate(Cred);

        // Left Right Case
        if (balance > 1 && username > Cred->left->username)
        {
            Cred->left = leftRotate(Cred->left);
            return rightRotate(Cred);
        }

        // Right Left Case
        if (balance < -1 && username < Cred->right->username)
        {
            Cred->right = rightRotate(Cred->right);
            return leftRotate(Cred);
        }

        /* return the (unchanged) Cred pointer */
        return Cred;
    }

    Cred * minValueCred(Cred* CCred)
    {
        Cred* current = CCred;

        /* loop down to find the leftmost leaf */
        while (current->left != NULL)
            current = current->left;

        return current;
    }

    Cred* deleteCred(Cred* root, string username)
    {
        
        // STEP 1: PERFORM STANDARD BST DELETE
        if (root == NULL)
            return root;

        // If the username to be deleted is smaller
        // than the root's username, then it lies
        // in left subtree
        if ( username < root->username )
            root->left = deleteCred(root->left, username);

        // If the username to be deleted is greater
        // than the root's username, then it lies
        // in right subtree
        else if( username > root->username )
            root->right = deleteCred(root->right, username);

        // if username is same as root's username, then
        // This is the Cred to be deleted
        else
        {
            // Cred with only one child or no child
            if( (root->left == NULL) ||
                (root->right == NULL) )
            {
                Cred *temp = root->left ?
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
                // Cred with two children: Get the inorder
                // successor (smallest in the right subtree)
                Cred* temp = minValueCred(root->right);

                // Copy the inorder successor's
                // data to this Cred
                root->username = temp->username;

                // Delete the inorder successor
                root->right = deleteCred(root->right,
                                        temp->username);
            }
        }

        // If the tree had only one Cred
        // then return
        if (root == NULL)
        return root;

        // STEP 2: UPDATE HEIGHT OF THE CURRENT Cred
        root->height = 1 + max(height(root->left),
                            height(root->right));

        // STEP 3: GET THE BALANCE FACTOR OF
        // THIS Cred (to check whether this
        // Cred became unbalanced)
        int balance = getBalance(root);

        // If this Cred becomes unbalanced,
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
        Cred *t=root;
        Stack st(110);

        while(t!=NULL || !st.isempty()){
            
            if(t!=NULL){
                cout<<t->username<<" ";
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
        Cred *t=root;
        Stack st(100);

        while(t!=NULL || !st.isempty()){
            
            if(t!=NULL){
                st.push(t);
                t=t->left;
            }

            else{
                t=st.pop();
                cout<<t->username<<" ";
                t=t->right;
            }
        }

    }
    
    void levelorder(){
        Cred *t=root;   
        Queue q(100);
        q.enqueue(t);
        while(!q.isempty()){
            t=q.dequeue();
            if(t!=NULL){
                cout<<t->username<<" ";

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
    loginData t1;
    
	t1.insert("ayush","pass1");
	t1.insert("shivang","pass2");
	t1.insert("akshit","pass3");
    
    t1.Delete("shivang");
	
	cout << "Preorder traversal of the "
			"constructed AVL tree is \n";
	t1.preorder();
	
	return 0;
}



