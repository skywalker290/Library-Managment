#include <iostream>
#include <bits/stdc++.h>
#include <mysql/mysql.h>
#include "connection.h"
using namespace std;


loginData admin;
loginData user;
login skywalker;
booklist LRC;


int main(){


    // mysql conn;

    // string query1="select count(*) from test69;";
    // string query2="select * from test69;";
    // string **result=conn.fetch_data(query1,query2);

    // for(int i=0;result[i];i++){
    //     cout<<"|";
    //     for(int j=0;j<2;j++){
    //         cout<<result[i][j]<<"\t|";
    //     }
    //     cout<<"|"<<endl;
    // }


    cout<<"\n================================\n";

    loginData d1;
    d1.insert("Ayush","Gupta");
    d1.insert("A","Gpta");
    d1.insert("Ay","Gupsta");
    d1.insert("Afds","Gudfsta");
    d1.insert("Aydf","Gudta");

    d1.preorder();
    cout<<d1.search("Ayus");
    cout<<"\n";

    d1.preorder();
    system("clear");


    cout<<"\n================================\n";









    return 0;
}

