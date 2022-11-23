#include <iostream>
#include <bits/stdc++.h>
#include <mysql/mysql.h>
using namespace std;










string Dateoftoday;

char Database[]="test";

string itos(int num){
	ostringstream str1;

	str1 << num;

	string istring = str1.str();

	if(num<10){
        istring="0"+istring;
	}

	return istring;
}

int stoii(string s){

    stringstream str(s);
    
    int x = 0;
    str >> x;
 
    return x;
}

string idgenerator(){

    time_t now = time(0);

    tm *ltm = localtime(&now);

    string b_id=
    itos(1900 + ltm->tm_year) + itos( 1+ ltm->tm_mon)
    + itos(ltm->tm_mday) + itos(ltm->tm_hour)
    + itos(ltm->tm_min) + itos(ltm->tm_sec);

    // cout<<"bill no"<<b_id;

    Dateoftoday=itos(1900 + ltm->tm_year)+"-"+itos( 1+ ltm->tm_mon)+"-"+itos(ltm->tm_mday);
    return b_id;

}

int max(int a, int b)
{
	return (a > b)? a : b;
}






class mysql{

    public:
    int row_c,fields_c;
    int count=0;
    string **results;

    MYSQL *connect(){

    MYSQL * conn;
    MYSQL * conn1;
    conn=mysql_init(NULL);
    conn1=mysql_real_connect(conn,"localhost","root","aaaa",Database,3306,NULL,0);
    if (conn1){
        // cout<<"Connected\n";
    }
    

    else{
        cout<<"[Not Connected]\n";
        cout<<mysql_error(conn)<<endl<<mysql_errno(conn)<<endl;

    }
    return conn;
}

void insert(string command){
    MYSQL *conn=connect();
    int status;
    status=mysql_query(conn,command.c_str());

    if(status==0){
        // cout<<"Inserted!\n";
    }

    else{
        cout<<"[Not Exceuted!]\n";
        cout<<mysql_error(conn)<<endl<<mysql_errno(conn)<<endl;
    }
    status=mysql_query(conn,"exit;");
}


string** fetch_data(string command1,string command){
    MYSQL *conn=connect();
    MYSQL *conn1=connect();

    int status,status1;
    status1=mysql_query(conn1,command1.c_str());

    MYSQL_ROW row1;
    MYSQL_RES *res1;

    res1=mysql_store_result(conn1);
    row1=mysql_fetch_row(res1);
    status=mysql_query(conn,command.c_str());

    MYSQL_ROW row;
    MYSQL_RES* res;

    row_c=atoi(row1[0]);
    res=mysql_store_result(conn);
    row=mysql_fetch_row(res);
    fields_c=mysql_field_count(conn);

    results=new string*[row_c+1];

    for(int i=0;i<row_c;i++){
        results[i]=new string[fields_c+1];
    }

    
    while(row!=0){
        for(int i=0;i<fields_c+1;i++){
            results[count][i]=row[i];
        }
        row=mysql_fetch_row(res);
        count++;
        
    }
    results[count]=NULL;

    return results;
    }

    // ~mysql(){
    //     delete results;
    // }
};


class issuer{
    public:
    issuer *next;
    string issuer_id;//SELF
    string issuer_name;//SELF
    string issue_date;//DD-MM-YYYY 
};



class issuerList{
    public:
    issuer *head;
    issuer *tail;
    int N;//TOTAL issuerS

    issuerList(){
        head=NULL;
        tail=NULL;
        N=0;
    }

    issuer* input1(){

        issuer *t=new issuer;
        cout<<"Enter issuer Details>>>>\n";
        cout<<"Enter issuer ID:";
        cin>>t->issuer_id;
        cout<<"Enter issuer name:";
        cin>>t->issuer_name;
        cout<<"Enter issuing date in format DD-MM-YYYY:";
        cin>>t->issue_date;

        t->next=NULL;
        return t;

    }

    void issuer_details(){// fthis function inserts the books into the system.
        N++;
        if(head==NULL){
            head=input1();
            tail=head;
        }
        else{
            issuer *t=input1();
            tail->next=t;
            tail=t;
        }
    }

    void book_return(string s)
    {

        issuer *p=head;
        if(s==head->issuer_id)
        {
            head=head->next;
        }
        else
        {
            while(p)
            {
                if(s==p->next->issuer_id)
                {
                    p->next=p->next->next;
                    break;
                }
                p=p->next;
            }
        }
        N--;
    }
};



class book{
    public:
    int book_id;//SELF
    string author;//AUTHOR_NAME
    issuerList issuer;//ISSUER DETAILS
    string title;//BOOK TITLE
    string publisher;//Publisher
    int no_pages;//Pages
    string genere;//Genere
    int quantity;//quantity
    book *next;//connection pointer

    void book_issuer(){
        issuer.issuer_details();
    }
    void book_return(string s){
        issuer.book_return(s);
    }
};



class booklist{
    public:
    book *head;
    book *tail;
    int N;
    
    booklist(){
        head=NULL;
        tail=NULL;
        N=0;
    }

    book* input(){

        book *t=new book;
        cout<<"Enter Book Details>>>>\n";
        cout<<"Enter Book_Id:";
        cin>>t->book_id;
        cout<<"Enter Quantity:";
        cin>>t->quantity;
        cout<<"Enter author_name:";
        cin>>t->author;
        cout<<"Enter Title:";
        cin>>t->title;
        cout<<"Enter Publisher:";
        cin>>t->publisher;
        cout<<"Total Pages:";
        cin>>t->no_pages;
        cout<<"Enter Genere:";
        cin>>t->genere;

        t->next=NULL;

        N++;

        return t;
    }

    void insert(){// fthis function inserts the books into the system.
        if(head==NULL){
            head=input();
            tail=head;
        }
        else{
            book *t=input();
            tail->next=t;
            tail=t;
        }
    }


    void display_current(){
        book *t=head;
        while(t){
            cout<<t->title<<" "<<t->book_id<<" \n";
        }
        cout<<endl;

    }

    book* merge(book* firstNode, book* secondNode,int choice){
        book* merged = new book;
        book* temp = new book;

        merged = temp;

        // while either firstNode or secondNode becomes NULL
        if(choice==0){//book_id Sorting
            while (firstNode != NULL && secondNode != NULL) {

                if (firstNode->book_id <= secondNode->book_id) {
                    temp->next = firstNode;
                    firstNode = firstNode->next;
                }

                else {
                    temp->next = secondNode;
                    secondNode = secondNode->next;
                }
                temp = temp->next;
            }

        }

        else if(choice==1){//title Sorting
            while (firstNode != NULL && secondNode != NULL) {

                if (firstNode->title <= secondNode->title) {
                    temp->next = firstNode;
                    firstNode = firstNode->next;
                }

                else {
                    temp->next = secondNode;
                    secondNode = secondNode->next;
                }
                temp = temp->next;
            }

        }

        else if(choice==2){//author Sorting
            while (firstNode != NULL && secondNode != NULL) {

                if (firstNode->genere <= secondNode->genere) {
                    temp->next = firstNode;
                    firstNode = firstNode->next;
                }

                else {
                    temp->next = secondNode;
                    secondNode = secondNode->next;
                }
                temp = temp->next;
            }

        }
        
        
        
        
        while (firstNode != NULL) {
            temp->next = firstNode; 
            firstNode = firstNode->next;
            temp = temp->next;
        }

        while (secondNode != NULL) {
            temp->next = secondNode;
            secondNode = secondNode->next;
            temp = temp->next;
        }
        
        return merged->next;


        
    }
    
    book* middle(book* head){

        book* slow = head;
        book* fast = head->next;

        while (!slow->next && (!fast && !fast->next)) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;

    }

    book* sort(book* head,int choice)
    {
        if (head->next == NULL) {
            return head;
        }

        book* mid = new book;
        book* head2 = new book;
        mid = middle(head);
        head2 = mid->next;
        mid->next = NULL;
        book* finalhead = merge(sort(head,choice), sort(head2,choice),choice);
        return finalhead;
    }

    void sort_books(){
        cout<<"\n0->Along Book_Id\n";
        cout<<"1->Along Title\n";
        cout<<"2->Along Genere\n";
        cout<<"Enter Sorting Along:";
        int choice;
        cin>>choice;


        head=sort(head,choice);
        display_current();
    }

    void like_search(string text){
        int len=text.length();
        int Lscore=0;
        int Rscore=0;
        int leftp=0;
        int rightp=0;
        string key="";
        int i=0;

        if(text[0]=='%'){
            leftp=1;
        }
        else if(text[0]=='_'){
            
            for(i=0;text[i]=='_';i++){
                Lscore++;
            }    
        }

        for(i;text[i]!='_' || text[i]!='%' || text[i];i++){
                key=key+text[i];
        }


        if(text[len]=='%'){
            rightp=1;
        }
        else if(text[len]=='_'){
            for(i;text[i];i++){
                Lscore++;
            }
        }

        book* t=head;
        while(t){
            string check=t->title;
            int clen=check.length();

            if(check.length()>=key.length() && leftp==1 && rightp==1){
                for(int i=0;i<clen-key.length();i++){
                    int test=0;
                    for(int j=i;j<key.length();j++){
                        if(key[j]==text[j]){
                            test=1;
                        }
                        else{
                            test=0;
                            break;
                        }
                    }
                    if(test==1){
                        cout<<t->book_id<<" "<<t->title<<endl;
                    }
                }
            }

            else if(clen>Lscore+key.length()+Rscore && leftp==1 && rightp==0){
                for(int i=0;i<clen-key.length()-Rscore;i++){
                    int test=0;
                    for(int j=i;j<key.length();j++){
                        if(key[j]==text[j]){
                            test=1;
                        }
                        else{
                            test=0;
                            break;
                        }
                    }
                    if(test==1){
                        cout<<t->book_id<<" "<<t->title<<endl;
                    }
                }
                
            }

            else if(clen>Lscore+key.length()+Rscore && leftp==0 && rightp==1){
                for(int i=Lscore;i<clen-key.length()-Rscore;i++){
                    int test=0;
                    for(int j=i;j<key.length();j++){
                        if(key[j]==text[j]){
                            test=1;
                        }
                        else{
                            test=0;
                            break;
                        }
                    }
                    if(test==1){
                        cout<<t->book_id<<" "<<t->title<<endl;
                    }
                }
                
            }
        }
    }
    
    void Book_Issue(){//This function is to issue a book

        int id;
        cout<<"Enter Book_ID:";
        cin>>id;

        book *b1=head;
        while(b1){
            if(b1->book_id==id){
                break;
            }
            b1=b1->next;
        }

        if(b1->quantity>0){
            b1->book_issuer();
            b1->quantity--;
        }
        else{
            cout<<">>Book is not available<<\n";
        }        
    }

    void Book_Return(){//This function is to issue a book

        int bid;
        string Iid;
        cout<<"Enter Book_ID:";
        cin>>bid;
        cout<<"Enter Issuer_ID:";
        cin>>Iid;

        book *b1=head;
        while(b1){
            if(b1->book_id==bid){
                break;
            }
            b1=b1->next;
        }

    
        b1->book_return(Iid);
        b1->quantity++;   
    }

    void update(){//This function is to update book details stored in book node;

        int b1;
        int y;
        book * p=head;
        while (true)
        {
            cout<<"Choose which column you want to update: "<<endl;
            cout<<"1-Title"<<endl;
            cout<<"2-Publisher"<<endl;
            cout<<"3-Author"<<endl;
            cout<<"4-Genere"<<endl;
            cout<<"5-Quantity"<<endl;
            cout<<"0-Exit"<<endl;
            cout<<"Input>>>";
            cin>>y;
            cout<<"Enter book ID whose detail you want to update"<<endl;
            cout<<"Input>>>";
            cin>>b1;
            while(p){

                if(p->book_id==b1)
                {
                    break;
                }
                p=p->next;
            }

            if(y==1){

                string b2;
                cout<<"Enter new Title:"<<endl;
                cin>>b2;
                p->title=b2;
            }
            else if(y==2){
                
                string b2;
                cout<<"Enter new Author:"<<endl;
                cin>>b2;
                p->author=b2;
            }
            else if(y==3){

                string b2;
                cout<<"Enter new Publisher:"<<endl;
                cin>>b2;
                p->publisher=b2;
            }
            else if(y==4){

                string b2;
                cout<<"Enter new Genere:"<<endl;
                cin>>b2;
                p->genere=b2;
            }
            else if(y==5){

                int b2;
                cout<<"Enter new Quantity:"<<endl;
                cin>>b2;
                p->quantity=b2;
            }
            else
            {
                break;
            }

        }

    }

};


class Cred
{
	public:
	string username;
	string password;
	Cred *left;
	Cred *right;
	int height;
};


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

    void insert(string username,string password){//only admin users can insert new user either admin or normald
        root=push(root,username,password);
    }

    void Delete(string username){//Only Admin users can delete
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


    Cred* search(string key){//searching for the login cred node using username
        Cred *t=root;
        while(t!=NULL){
            if(key==t->username){
                return t;
            }
            else if(key<(t->username)){
                t=t->left;
            }
            else{
                t=t->right;
            }
        }
        return NULL;
    }

    void chooseuser(){

    }


};

class login{
    public:
    string username;
    string password;
    

    string typespec(string username){
        if(username[0]=='A'){
            adminlogin();
        }
        else if(username[0]=='U'){
            userlogin();
        }
        else{
            return "Invalid Username";
        }
    }

    void adminlogin(){
        int choice=0;
        system("clear");
        // cout<<"Hello"<<
        cout<<"Enter Your Choice:";
    }
    void userlogin(){

    }

};

void Authentication(){




    string userN;
    string passwD;
    login skywalker;

    cout<<"Enter Username:";
    cin>>userN;
    cout<<"Enter Password:";
    cin>>passwD;

    skywalker.username=userN;
    skywalker.password=passwD;

}



