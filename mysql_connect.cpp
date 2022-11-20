#include <iostream>
#include <mysql/mysql.h>
using namespace std;

// static char *host ="localhost";
// static char *user ="root";
// static char *passwd ="aaaa";
// static char *database ="test";

char host[]="localhost";
char user[]="root";
char passwd[]="aaaa";
char database[]="";

unsigned int port=3306;
static char* unix_socket=NULL;
unsigned int flag=0;

int *check;


int main(){
    cout <<"\n=========================================\n\n";

    MYSQL * conn;

    conn=mysql_init(NULL);
    if(!(mysql_real_connect(conn, host, user, passwd, database, port, unix_socket,flag))){
        cout<<mysql_error(conn)<<endl<<mysql_errno(conn)<<endl;
        // exit(1);
    }  

    else{
        cout<<"Mithai batvado";
        
    }


    





    cout <<"\n=========================================\n\n";
    return 0;
}
