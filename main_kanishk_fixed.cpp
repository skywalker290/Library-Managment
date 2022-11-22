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
    string issuer_name;//SELF
    string issuer_id;//SELF
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
    issuerList issuer;
    string title;
    string publisher;
    int no_pages;
    string genere;
    int quantity;
    book *next;

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

    void display_modified(book *H){
        book *t=H;
        while(t){
            cout<<t->title<<" "<<t->book_id<<" \n";
        }
        cout<<endl;

    }

    book* merge(book* firstissuer, book* secondissuer,int choice){
        book* merged = new book;
        book* temp = new book;

        // merged is equal to temp so in the end we have the top
        // issuer.
        merged = temp;

        // while either firstissuer or secondissuer becomes NULL
        if(choice==0){//book_id Sorting
            while (firstissuer != NULL && secondissuer != NULL) {

                if (firstissuer->book_id <= secondissuer->book_id) {
                    temp->next = firstissuer;
                    firstissuer = firstissuer->next;
                }

                else {
                    temp->next = secondissuer;
                    secondissuer = secondissuer->next;
                }
                temp = temp->next;
            }

        }

        else if(choice==1){//title Sorting
            while (firstissuer != NULL && secondissuer != NULL) {

                if (firstissuer->title <= secondissuer->title) {
                    temp->next = firstissuer;
                    firstissuer = firstissuer->next;
                }

                else {
                    temp->next = secondissuer;
                    secondissuer = secondissuer->next;
                }
                temp = temp->next;
            }

        }

        else if(choice==2){//author Sorting
            while (firstissuer != NULL && secondissuer != NULL) {

                if (firstissuer->genere <= secondissuer->genere) {
                    temp->next = firstissuer;
                    firstissuer = firstissuer->next;
                }

                else {
                    temp->next = secondissuer;
                    secondissuer = secondissuer->next;
                }
                temp = temp->next;
            }

        }


        // any remaining issuer in firstissuer or secondissuer gets
        // inserted in the temp List

        while (firstissuer != NULL) {
            temp->next = firstissuer;
            firstissuer = firstissuer->next;
            temp = temp->next;
        }

        while (secondissuer != NULL) {
            temp->next = secondissuer;
            secondissuer = secondissuer->next;
            temp = temp->next;
        }
        // return the head of the sorted list
        return merged->next;
    }




    // function to calculate the middle Element
    book* middle(book* head){

        book* slow = head;
        book* fast = head->next;

        while (!slow->next && (!fast && !fast->next)) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;

    }




    // function to sort the given list
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
        // recursive call to sort() hence diving our problem,
        // and then merging the solution
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


int main(){
    int c;
    while(true)
    {
        cout<<"1-Add new book to database"<<endl;
        cout<<"2-Issuing a book"<<endl;
        cout<<"3-Searching record"<<endl;
        cout<<"4-Sorting data lexicographically"<<endl;
        cout<<"5-Update records"<<endl;
        cout<<"0-Exit"<<endl;
        cout<<"Enter choice: ";
        cin>>c;
        if(c==1)
        {

        }
        else if(c==2)
        {

        }
        else if(c=3)
        {

        }
        else if(c=4)
        {

        }
        else if(c=5)
        {

        }
        else
        {
            break;
        }
    }
    return 0;
}

 