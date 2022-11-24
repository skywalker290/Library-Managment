#include <bits/stdc++.h>
#include <mysql/mysql.h>
#include "connection.h"
using namespace std;

login skywalker("Askywalker290","letshackitof");
loginData admin;
loginData user;
booklist LRC;

// login skywalker("A","B");    


void Insert_Data_user(string **data);
void Insert_Data_Admin(string **data);
void Insert_Data_LRC(string **data);
void Insert_Data_Issuer(string **data);


void fetchdata(){
    mysql m1,m2,m3,m4;
    string ** usertab;
    string ** admintab;
    string ** booktab;
    string ** issuer;

    usertab=m1.fetch_data("select count(*) from login where type='user';","select username,passwd from login where type='user'");
    Insert_Data_user(usertab);

    admintab=m2.fetch_data("select count(*) from login where type='admin';","select username,passwd from login where type='admin'");
    Insert_Data_Admin(admintab);

    booktab=m3.fetch_data("select count(*) from book;","select * from book");
    Insert_Data_LRC(booktab);

    issuer=m4.fetch_data("select count(*) from issued_book ib,issuer i where i.issuer_id=ib.issuer_id"
    ,"select ib.book_id,i.issuer_id,i.name,i.date from issued_book ib,issuer i where i.issuer_id=ib.issuer_id");
    Insert_Data_Issuer(issuer);
    
}



void Insert_Data_user(string **data){
    for(int i=0;data[i];i++){
        user.insert(data[i][0],data[i][1]);
    }
}



void Insert_Data_Admin(string **data){
   for(int i=0;data[i];i++){
        admin.insert(data[i][0],data[i][1]);
    } 
}


void Insert_Data_LRC(string **data){

    for(int i=0;data[i];i++){
        LRC.book_insert(data[i][0],stoi(data[i][1]),data[i][2],data[i][3],data[i][4],stoi(data[i][5]),data[i][6]);
    }

}

void Insert_Data_Issuer(string **data){
    for(int i=0;data[i];i++){
        LRC.book_insert(data[i][0],stoi(data[i][1]),data[i][2],data[i][3],data[i][4],stoi(data[i][5]),data[i][6]);
    }
}

void adminlogin(){

    int choice=0;
    system("clear");
    cout<<"<<<Hello Admin>>>\n";
    cout<<"1->Add New Book\n";
    cout<<"2->Search Book\n";
    cout<<"3->LIKE Search Book\n";
    cout<<"4->Update Book Details\n";
    cout<<"5->Sort Books\n";
    cout<<"6->Issue Book\n";
    cout<<"7->Return Book\n";
    cout<<"8->Display\n";
    cout<<"9->Issuer of a Book\n";
    cout<<"Enter Your Choice:";
    cin>>choice;

    if(choice==1){
        LRC.insert();
    }
    
    else if (choice==2){
        string id;
        cout<<"Enter Book ID:";
        LRC.search(id);
    }
    else if(choice==3){
        string titlee;
        cout<<"Enter Title To be searched of using '%' and '_':";
        LRC.like_search(titlee);
    }
    else if(choice==4){
        string titlee;
        cout<<"Enter Title To be searched of using '%' and '_':";
        LRC.like_search(titlee);
    }
    else if(choice==5){
        cout<<"\n=========================\n";
        LRC.sort_books();
    }
    else if(choice==6){
        LRC.Book_Issue();
    }
    else if(choice==7){
        LRC.Book_Return();
    }
    else if(choice==8){
        LRC.display_current();
    }
    else if(choice==9){
        LRC.issuer_display();
    }

}


void userlogin(){

    int choice=0;
    system("clear");
    cout<<"<<<Hello User>>>\n";
    cout<<"1->Search Book\n";
    cout<<"2->LIKE Search Book\n";
    cout<<"3->Sort Books\n";
    cout<<"4->Display\n:";
    cout<<"Enter Your Choice:";
    cin>>choice;

    if (choice==2){
        string id;
        cout<<"Enter Book ID:";
        LRC.search(id);
    }
    else if(choice==2){
        string titlee;
        cout<<"Enter Title To be searched of using '%' and '_':";
        LRC.like_search(titlee);
    }
    else if(choice==3){
        cout<<"\n=========================\n";
        LRC.sort_books();
        cout<<endl;
    }

    else if(choice==4){
        LRC.display_current();
    }
}




int main(){
    fetchdata();
    cout<<"\n================================\n";
    
    skywalker.Authentication(admin,user);
    cout<<skywalker.type;
    user.preorder();

    cout<<endl;

    admin.preorder();

    cout<<"\n================================\n";
    return 0;
}

