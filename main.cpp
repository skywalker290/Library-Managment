#include <bits/stdc++.h>
#include <mysql/mysql.h>
#include "connection.h"
using namespace std;

login skywalker("Uskywalker290","letshackitof");
//this is login token as inital is U so its a user token 
//if this would be A then it would be Admin utoken


loginData admin;
//admin is an AVL tree which stores all the data of 
//Admins usernames and passwords

loginData user;
//user is an AVL tree which stores all the data of 
//users usernames and passwords

booklist LRC;
//LRC is a linked list type whose nodes are book object storing
//all the book details of a library



void Insert_Data_user(string **data);
void Insert_Data_Admin(string **data);
void Insert_Data_LRC(string **data);
void Insert_Data_Issuer(string **data);


void fetchdata(){
    mysql m1,m2,m3,m4;//mysql class objects used for connections


    //these **string pointers store the data which is fetch from the queries
    //executed below.
    string ** usertab;
    string ** admintab;
    string ** booktab;
    string ** issuer;

    //All userdata
    usertab=m1.fetch_data("select count(*) from login where type='user';","select username,passwd from login where type='user'");
    Insert_Data_user(usertab);

    //All admindata
    admintab=m2.fetch_data("select count(*) from login where type='admin';","select username,passwd from login where type='admin'");
    Insert_Data_Admin(admintab);

    //Books to booklist
    booktab=m3.fetch_data("select count(*) from book;","select * from book");
    Insert_Data_LRC(booktab);

    //issuers according to book_id
    issuer=m4.fetch_data("select count(*) from issued_book ib,issuer i where i.issuer_id=ib.issuer_id"
    ,"select ib.book_id,i.issuer_id,i.name,i.date from issued_book ib,issuer i where i.issuer_id=ib.issuer_id");
    Insert_Data_Issuer(issuer);
    
}


//Function to transfer data to their respective objects

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
        LRC.book_insert(data[i][0],data[i][1],data[i][2],data[i][3],stoii(data[i][4]),data[i][5]);
    }

}

void Insert_Data_Issuer(string **data){
    for(int i=0;data[i];i++){
        LRC.Book_Issue_insert(data[i][0],data[i][1],data[i][2],data[i][3]);
    }
}


//Admin Login Menu all the access for Admin
//They can update,display,issue,return books;

void adminlogin(){

    int choice=0;
    while(choice<10){
        // system("clear");
        cout<<"\n===============================\n";
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

        cout<<"\n=========================\n";


        //for Adding New Book
        if(choice==1){
            LRC.insert();
            cout<<"\n=========================\n";
            LRC.display_current();
        }
        

        //For searching Book Using its Book ID
        else if (choice==2){
            string id;
            cout<<"Enter Book ID:";
            cin>>id;
            LRC.search(id);

        }

        //For searching Book title using Uncertain words
        else if(choice==3){
            string titlee;
            cout<<"Enter Approx Title To be searched of :";
            cin>>titlee;
            LRC.like_search_2(titlee);

        }


        //For updating the Book Record's Data
        else if(choice==4){
            LRC.update();

        }

        //For Sorting Books with respect to Many datavalues
        else if(choice==5){
            cout<<"\n=========================\n";
            LRC.sort_books();

        }

        //For Issuing A book
        else if(choice==6){
            LRC.Book_Issue();

        }
        
        //For returning an Issued book
        else if(choice==7){
            LRC.Book_Return();

        }

        //For Displaying Current State of Data
        else if(choice==8){
            LRC.display_current();

        }

        //For Displaying Issuer of A book
        else if(choice==9){
            LRC.issuer_display();

        }

    }

}



//User Login Menu ,From this user type can operate 
//they can only see the data cant make any changes
void userlogin(){
int choice=0;
    while(choice<5){
        
        cout<<"\n=========================\n";
        cout<<"<<<Hello User>>>\n";
        cout<<"1->Search Book\n";
        cout<<"2->LIKE Search Book\n";
        cout<<"3->Sort Books\n";
        cout<<"4->Display\n:";
        cout<<"Enter Your Choice:";
        cin>>choice;
        cout<<"\n=========================\n";

        if (choice==1){
            string id;
            cout<<"Enter Book ID:";
            cin>>id;
            LRC.search(id);
        }
        else if(choice==2){
            string titlee;
            cout<<"Enter Approx Titile :";
            cin>>titlee;
            LRC.like_search_2(titlee);
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
}




int main(){
    fetchdata();
    cout<<"\n================================\n";
    
    skywalker.Authentication(admin,user);
    // user.preorder();
    // admin.preorder();


    cout<<"\n================================\n";
    return 0;
}

