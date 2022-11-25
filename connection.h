#include <bits/stdc++.h>
#include <mysql/mysql.h>
using namespace std;


void adminlogin();
void userlogin();



string Dateoftoday;

char Database[]="LMS";//Database that we are using to fetch data into our Program

string itos(int num){//integer to string typecasting
	ostringstream str1;

	str1 << num;

	string istring = str1.str();

	if(num<10){
        istring="0"+istring;
	}

	return istring;
}

int stoii(string s){//string to integer typecasting 

    stringstream str(s);
    
    int x = 0;
    str >> x;
 
    return x;
}



int max(int a, int b)
{
	return (a > b)? a : b;
}





//Mysql Class used to connect the program with mysql server root@localhost;
class mysql{

    public:
    int row_c,fields_c;
    int count=0;
    string **results;

    MYSQL *connect(){//Function to make connection varibale with the server and returns the varible to run querry

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


    //Function to execute insert querry;
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
    mysql_close(conn);
    // conn->close();
    }



    //Function to fetch data from database it uses two querryies one 
    //count the number of rows and the other one 
    //fetch the data into the string array
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
            for(int i=0;i<fields_c;i++){
                results[count][i]=row[i];
            }
            row=mysql_fetch_row(res);
            count++;
            
        }
        results[count]=NULL;

        mysql_close(conn);
        // conn->close();

        return results;
        }

    // ~mysql(){
    //     delete results;
    // }
};



//Issuer Class node for storing data of the person issuing the book connected with likedllist of issuers.
class issuer{
    public:
    issuer *next;
    string issuer_id;//SELF
    string issuer_name;//SELF
    string issue_date;//DD-MM-YYYY 
};




//Issuer List is lliked list of Issuers.
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

    //Function for taking input and creating new issuer
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


    // this function inserts the books into the system.
    void issuer_details(){
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
    
    // fthis function inserts the books into the system.
    void issuer_details_insert(string id,string name,string date){
        N++;

        issuer *t=new issuer;
        t->issuer_name=name;
        t->issuer_id=id;
        t->issue_date=date;
        t->next=NULL;

        if(head==NULL){
            head=t;
            tail=head;
        }
        else{
            // issuer *t=Iss;
            tail->next=t;
            tail=t;
        }
    }
    
    //This function is ussed to return book which was issued.
    void book_return(string s)
    {//s=id;

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

    //Displays the issuers of a particular book record
    void issuer_display(){
        issuer *t=head;

        while(t){
            cout<<t->issuer_id<<",\t"<<t->issuer_name<<",\t"<<t->issue_date<<endl;
            t=t->next;
        }
    }
};




//Book Node for storing data of the book
class book{
    public:
    string book_id;//SELF
    string author;//AUTHOR_NAME
    issuerList issuer;//ISSUER DETAILS
    string title;//BOOK TITLE
    string publisher;//Publisher
    int no_pages;//Pages
    string genere;//Genere
    int quantity;//quantity
    book *next;//connection pointer

    void book_issuer(){//this is a connectig function used while issueing book
        issuer.issuer_details();
    }
    void book_return(string s){//this is a connection fucntion used while returning a book
        issuer.book_return(s);
    }
    void display(){//for displaying all the data of a book
        cout<<endl<<book_id<<",\t"<<author<<",\t"<<title<<",\t"
        <<publisher<<",\t"<<no_pages<<",\t"<<genere<<",\t"<<quantity
        <<endl;
    }
};





//linked list of Book nodes
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

    // for inserting the data into the list directly
    void book_insert(string id,string auth,string titl,string pub,int pgno, string Gen){
    
        book *t=new book;
        t->book_id=id;
        t->quantity=100;
        t->author=auth;
        t->title=titl;
        t->publisher=pub;
        t->no_pages=pgno;
        t->genere=Gen;
        t->next=NULL;

        insert_force(t);
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

    //this is used when we get values from our database and put it into the list directly
    void insert_force(book *tt){// fthis function inserts the books into the system.
        if(head==NULL){
            head=tt;
            tail=head;
        }
        else{
            tail->next=tt;
            tail=tt;
        }
    }


    //display all the books into the list
    void display_current(){
        book *t=head;
        while(t){
            // cout<<">>"<<t->book_id<<","<<t->title<<"\n";
            t->display();
            t=t->next;
        }
        cout<<endl;

    }

    //For merging two linked list for merge sort
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
    

    //For finding Middle element of a linked list
    book* middle(book* head){

        book* slow = head;
        book* fast = head->next;

        while (!slow->next && (!fast && !fast->next)) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;

    }


    //Main calling function for merge sort
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


    //Caller function for sorting 
    void sort_books(){
        cout<<"0->Along Book_Id\n";
        cout<<"1->Along Title\n";
        cout<<"2->Along Genere\n";
        cout<<"Enter Sorting Along:";
        int choice;
        cin>>choice;

        head=sort(head,choice);
        display_current();
    }


    //like search function to search titles with % and _ just like in mysql 
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

        for(i;(text[i]!='_' || text[i]!='%' )&&  text[i];i++){
                key=key+text[i];
        }
        cout<<key;


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
                        cout<<t->book_id<<"\t"<<t->title<<endl;
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

            t=t->next;
        }
    }



    //Searching titiles with just a substring
    void like_search_2(string key){
        book *t=head;

        while(t){
            int len=t->title.length();
            int temp=t->title.find(key);

            if(temp>=0 && temp<len ){
                t->display();
            }
            t=t->next;
        }
    }


    //For inserting a issuer while fetching data from database
    void Book_Issue_insert(string id,string I_id,string name,string date){//This function is to issue a book


        book *b1=head;
        while(b1){
            if(b1->book_id==id){
                break;
            }
            b1=b1->next;
        }

        if(b1->quantity>0 && b1){
            b1->issuer.issuer_details_insert(I_id,name,date);
            b1->quantity--;
        }
        else{
            cout<<">>Book is not available<<\n";
        }        
    }



    //for displaying issuers of a particular book by its ID
    void issuer_display(){
        string id;
        cout<<"Enter Book ID:";
        cin>>id;

        book *t=head;

        while(t){
            if(t->book_id==id){
                t->issuer.issuer_display();
                break;
            }
            t=t->next;
        }
    }



    
    void Book_Issue(){//This function is to issue a book

        string id;
        cout<<"Enter Book_ID:";
        cin>>id;

        book *b1=head;
        while(b1){
            if(b1->book_id==id){
                break;
            }
            b1=b1->next;
        }

        if(b1->quantity>0 && b1){
            b1->book_issuer();
            b1->quantity--;
        }
        else{
            cout<<">>Book is not available<<\n";
        }        
    }

    void Book_Return(){//This function is to issue a book

        string bid;
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

        if(b1){
            b1->book_return(Iid);
            b1->quantity++;   
            cout<<"\nBook Returned!\n";
        }
        else{
            cout<<"book ID not found;";
        }

    }

    void update(){//This function is to update book details stored in book node;

        string b1;
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


    //For directly searching a book by its ID;
    void search(string id){
        book *t=head;

        while(t){
            if(t->book_id==id){
                t->display();
                break;
            }
            t=t->next;
        }
    }

};




//Cred class is to store username and passwords for logging purposes
class Cred
{
	public:
	string username;
	string password;
	Cred *lchild;
	Cred *rchild;
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



//loginData is an AVL tree class for storing login credentials of various admins and users

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
        CCred->password = password;
        CCred->lchild = NULL;
        CCred->rchild = NULL;
        CCred->height = 1; // new Cred is initially
                        // added at leaf
        return(CCred);
    }

    void insert(string username,string password){//only administrator can insert new user either admin or normal
        root=push(root,username,password);
    }

    void manual_insert(){
        string usr,psd;
        cout<<"Enter Username:";
        cin>>usr;
        cout<<"Enter Password:";
        cin>>psd;

        root=push(root,usr,psd);
    }

    void Delete(string username){//Only Administrators can delete
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
        Cred *x = y->lchild;
        Cred *T2 = x->rchild;

        // Performing rotation
        x->rchild = y;
        y->lchild = T2;

        // Updating heights
        y->height = max(height(y->lchild),
                        height(y->rchild)) + 1;
        x->height = max(height(x->lchild),
                        height(x->rchild)) + 1;

        // Returning new root
        return x;
    }

    Cred *leftRotate(Cred *x)
    {
        Cred *y = x->rchild;
        Cred *T2 = y->lchild;

        // Performing rotation
        y->lchild = x;
        x->rchild = T2;

        // Updating heights
        x->height = max(height(x->lchild),
                        height(x->rchild)) + 1;
        y->height = max(height(y->lchild),
                        height(y->rchild)) + 1;

        // Returning new root
        return y;
    }

    int getBalance(Cred *N)
    {
        if (N == NULL)
            return 0;
        return height(N->lchild) - height(N->rchild);
    }

    Cred* push(Cred* Cred, string username,string password)
    {
        /* 1. Performing the normal BST insertion */
        if (Cred == NULL && root==NULL){
            root=newCred(username,password);
            return root;
        }
       
        if (Cred == NULL ){
            return(newCred(username,password));
        }
           
        if (username < Cred->username)
            Cred->lchild = push(Cred->lchild, username,password);
        else if (username > Cred->username)
            Cred->rchild = push(Cred->rchild, username,password);
        else
            return Cred;

        /* 2. Updating the height of Cred */
        Cred->height = 1 + max(height(Cred->lchild),height(Cred->rchild));

        /* 3. Get the balance factor of Cred in
            order to check whether this Cred became
            unbalanced or not */
        int balance = getBalance(Cred);

        // If the Cred becomes unbalanced, then
        // there are 4 cases with 4 types of rotation

        // Left Left case
        if (balance > 1 && username < Cred->lchild->username)
            return rightRotate(Cred);

        // Right Right case
        if (balance < -1 && username > Cred->rchild->username)
            return leftRotate(Cred);

        // Left Right Case
        if (balance > 1 && username > Cred->lchild->username)
        {
            Cred->lchild = leftRotate(Cred->lchild);
            return rightRotate(Cred);
        }

        // Right Left case
        if (balance < -1 && username < Cred->rchild->username)
        {
            Cred->rchild = rightRotate(Cred->rchild);
            return leftRotate(Cred);
        }

        /* If height of cred is balanced then
        return the (unchanged) Cred pointer */
        return Cred;
    }

    Cred * minValueCred(Cred* CCred)
    {
        Cred* current = CCred;

        /* loop down to find the leftmost node of the right
         subtree in order to find inorder succesor */
        while (current->lchild != NULL)
            current = current->lchild;

        return current;
    }

    Cred* deleteCred(Cred* root, string username)
    {
        // 1.Performing simple BST deletion in the tree
        if (root == NULL)
            return root;

        // If the username to be deleted is smaller
        // than the root->username, then it will be
        // in left subtree
        if ( username < root->username )
            root->lchild = deleteCred(root->lchild, username);

        // If the username to be deleted is greater
        // than the root->username, then it lies
        // in right subtree
        else if( username > root->username )
            root->rchild = deleteCred(root->rchild, username);

        // if username is same as root's username, then
        // This is the Cred to be deleted
        else
        {
            // Cred with only one child or no child
            if( (root->lchild == NULL) || (root->rchild == NULL) )
            {
                Cred *temp = root->lchild ?root->lchild :root->rchild;

                // No child case
                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else // One child case
                *root = *temp; // Copy the contents of the non-empty child
                free(temp);
            }
            else
            {
                // Cred with two children: Get the inorder
                // successor (smallest in the right subtree)
                Cred* temp = minValueCred(root->rchild);

                // Copy the inorder successor's
                // data to this Cred
                root->username = temp->username;

                // Delete the inorder successor
                root->rchild = deleteCred(root->rchild,
                                        temp->username);
            }
        }

        // If the tree had only one Cred
        // then return
        if (root == NULL)
        return root;

        // 2.UPDATE HEIGHT OF THE CURRENT Cred
        root->height = 1 + max(height(root->lchild),
                            height(root->rchild));

        // 3.Get the balance factor of Cred in
        // order to check whether this Cred became
        // unbalanced or not */
        int balance = getBalance(root);

        // If this Cred becomes unbalanced,
        // then there are 4 cases with 4 types of rotation

        // Left Left case
        if (balance > 1 &&
            getBalance(root->lchild) >= 0)
            return rightRotate(root);

        // Left Right Case
        if (balance > 1 &&
            getBalance(root->lchild) < 0)
        {
            root->lchild = leftRotate(root->lchild);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 &&
            getBalance(root->rchild) <= 0)
            return leftRotate(root);

        // Right Left Case
        if (balance < -1 &&
            getBalance(root->rchild) > 0)
        {
            root->rchild = rightRotate(root->rchild);
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
                t=t->lchild;
            }

            else{
                t=st.pop();
                t=t->rchild;
            }
        }

    }
       
    void inorder(){
        Cred *t=root;
        Stack st(100);

        while(t!=NULL || !st.isempty()){
           
            if(t!=NULL){
                st.push(t);
                t=t->lchild;
            }

            else{
                t=st.pop();
                cout<<t->username<<" ";
                t=t->rchild;
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

                if(t->lchild!=NULL){
                    q.enqueue(t->lchild);
                }
               
                if(t->rchild!=NULL){
                    q.enqueue(t->rchild);
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
                t=t->lchild;
            }
            else{
                t=t->rchild;
            }
        }
        return NULL;
    }

    Cred * insert()

};

class login{
    public:
    string username;
    string password;
    
    string type;

    login(){
        cout<<"Enter Username:";
        cin>>username;
        cout<<"Enter Password:";
        cin>>password;
        typespec();
    }

    login(string user,string pas){
        username=user;
        password=pas;

        int flag=0;

        typespec();
    }

    
    int typespec(){
        if(username[0]=='A'){
            type="Admin";
            return 11;
        }
        else if(username[0]=='U'){
            type="User";
            return 1;
        }
        else{
            type="INVALID";
            return 0;
        }
    }
    
    int Authentication(loginData &admin,loginData &user){

        int flag=0;


        if(type=="User"){
            Cred* temp=user.search(username);
            if(temp)
            if(temp->password==password ){
                flag=1;
            }
        }
        else if(type=="Admin"){
            Cred *temp=admin.search(username);
            if(temp)
            if(temp->password==password && temp){
                flag=11;
            }
        }
        else{
            cout<<"INVALID CREDENTIALS!\n";
            flag=-1;
            return -1;
        }

        if(flag==1){
            userlogin();
        }
        else if(flag==11){
            adminlogin();
        }
        else if(flag==0){
            cout<<"Wrong Credentials";
        }
    }
};





