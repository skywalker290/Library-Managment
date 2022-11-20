#include <iostream>
#include <mysql/mysql.h>
#include <string>
#include <sstream>
#include <vector>

using namespace  std;

string Dateoftoday;



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




string billnogenerator(){

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
    conn1=mysql_real_connect(conn,"localhost","root","aaaa","PMS",0,NULL,0);
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

    for(int i=0;i<row_c+1;i++){
        results[i]=new string[fields_c+1];
    }

    
    while(row!=0){
        for(int i=0;i<fields_c+1;i++){
            results[count][i]=row[i];
        }
        row=mysql_fetch_row(res);
        count++;
        
    }
  
    
    if(status==0){
        // cout<<"Inserted!\n";
        }

    else{
        cout<<"[Not Exceuted!]\n";
        cout<<mysql_error(conn)<<endl<<mysql_errno(conn)<<endl;
        }

    status=mysql_query(conn,"exit;");

    return results;
    }

    // ~mysql(){
    //     delete results;
    // }
};






class PMS{
    public:
    mysql a;

    PMS(){

    }

    void newuser(){
        string username,password;

        cout<<"Enter Username:";
        cin>>username;
        cout<<"Enter Password:";
        cin>>password;
        string command="insert into login values('"+username+"','"+password+"');";
        a.insert(command);
    }

    bool verify(string user,string pass){
        string command="select * from login where username='"+user+
        "'and passwd='"+pass+"';";
        string command1="select count(*) from login where username='"+user+
        "'and passwd='"+pass+"';";
        mysql b;
        // cout<<command1<<endl;
        // cout<<command<<endl;
        b.fetch_data(command1,command);

        if(a.row_c==1){
            return true;
        }
        else{
            return false;
		
        }
    }
};





class Stocks{
    public:
    
    Stocks(){}

    void addstock(){
        mysql a;
        string ID,name,company,quantity,rate,exp_date;

        cout<<"Enter Product_ID:";
        cin.ignore(1,'\n');
        getline(cin,ID);

        cout<<"Enter Name:";
        getline(cin,name);

        cout<<"Enter Company_Name:";
        getline(cin,company);

        cout<<"Enter Quantity:";
        getline(cin,quantity);

        cout<<"Enter Rate:";
        getline(cin,rate);

        cout<<"Enter Expiry_Date(YYYY-MM-DD):";
        getline(cin,exp_date);

        string command;
        command="insert into stock values('"
        +ID+"','"
        +name+"','"
        +company+"',"
        +quantity+","
        +rate+",'"
        +exp_date+"');";
        system("clear");

    
        a.insert(command);

        
    }

    void editstock(){
        cout<<"Press 1->Quantity&Rate\n";
        cout<<"Press 2->Rate\n";
        int input;
        cout<<"Input>";
        cin>>input;

        if(input==1){
            cout<<"Press 1->IF RATE\n";
            int r;
            cout<<"Input>";
            cin>>r;
            if(r==1){
                string rate_change;
                cout<<"Enter change in Rate:";
                cin>>rate_change;
                Qedit(rate_change);
            }
            else{
                Qedit("0");
            }
        }
        else{
            Redit();
        }
    }

    void Qedit(string r_change){
        string change;
        string ID;
        cout<<"Enter Change ID:";
        cin>>ID;
        cout<<"Change in Quantity:";
        cin>>change;
        
        mysql a;
        string command;
        command="update stock set quantity=quantity+"
        +change+",rate=rate+"
        +r_change+" where ID='"
        +ID+"';";

        // cout<<command<<endl;
        system("clear");
        a.insert(command);
    }

    void Redit(){
        string ID;
        string rchange;
        cout<<"Enter Change ID:";
        cin>>ID;
        cout<<"Change in Rate:";
        cin>>rchange;
        
        mysql a;
        string command;
        command="update stock set rate=rate+"
        +rchange+"where ID='"
        +ID+"';";
        cout<<command<<endl;
        a.insert(command);
    }
};





class customer{
    public:

    customer(){}

    void addcustomer(string p_no){
        mysql a;
        string name,email,medicine;
        int membe=1;
        string tm;

        // cout<<"Enter phone no.";
        // getline(cin,p_no);
        getline(cin,tm);

        cout<<"Enter Name:";
        getline(cin,name);

        cout<<"Enter email:";
        getline(cin,email);
        

        cout<<"Want Membership?\n";
        cout<<"Press 1->for YES\n";
        cout<<"Press 0->for NO\n";
        cout<<"Input>";
        cin>>membe;

        string command;
        command="insert into customer values('"
        +p_no+"','"
        +name+"','"
        +email+"',"
        +itos(membe)+");";

        // cout<<command;
        a.insert(command);

        // bill b;
        // b.newbill(p_no);
        throw p_no;

    }


    void editcustomer(){
        string phone_num;
        cout<<"\nEnter phone number:";
        cin>>phone_num;
        cout<<"Press 1->Phone Number\n";
        cout<<"Press 2->Email\n";
        int input1;
        cout<<"Input>:";
        cin>>input1;

        if(input1==1){

                Qedit(phone_num);
        }
        else{
        emailedit(phone_num);

        }
    }

    void Qedit(string p_num){
        string ph_ch;
        cout<<"Enter changed phone number:";
        cin>>ph_ch;

        mysql a;
        string command;
        command="update customer set Ph_no='"
        +ph_ch+"' where Ph_no='"
        +p_num+"';";
        cout<<"\nUpdated customer";

        // cout<<command<<endl;
        a.insert(command);
    }



    void emailedit(string p_num){
        string emailchange;
        cout<<"Enter Change email:";
        cin>>emailchange;


        mysql a;
        string command;
        command="update customer set email='"
        +emailchange+"' where Ph_no='"
        +p_num+"';";
        // cout<<command<<endl;
        a.insert(command);
    }


};





class bill{
    public:

    bill(){}

    void newbill(){
        string p_no,d_name,email;
        int member;
        string tempo;

        cout<<"Enter phone no:";
        cin>>p_no;
        // getline(cin,tempo);
        mysql a=cus_check(p_no);

        string* medicine;
        string* medicine_q;

        if(a.row_c==0){
            customer b;
            b.addcustomer(p_no);
        }
        else{

            system("clear");
            cout<<"Bill no:";
            string billno=billnogenerator();
            cout<<billno<<endl;

            string **ptr=a.results;

            d_name=ptr[0][1];
            email=ptr[0][2];
            member=stoii(ptr[0][3]);

            cout<<"Name:"<<ptr[0][1]<<endl;
            cout<<"Email:"<<ptr[0][2]<<endl;
            cout<<"Membership:"<<ptr[0][3]<<endl;



            vector<string> medicine_q;
            vector<string> medicine;


            string med,quantity;
            while(med[0]!='0'){
                cout<<"============================"<<endl;
                
                cout<<"Enter Medicine ID:";
                cin>>med;

                if(med[0]=='0'){
                    break;
                }

                cout<<"Enter Quantity:";
                cin>>quantity;

                medicine.push_back(med);
                medicine_q.push_back(quantity);
            }
            


            float total_price;
            total_price=pricecalc(medicine,medicine_q);
            cout<<"Before Discount:"<<total_price<<endl;
            

            if(member==1){
                total_price=total_price-(total_price*(0.15));
            }
            cout<<"After Discount:"<<total_price<<endl;

            savebill(billno,p_no,medicine,medicine_q);
            // system("pause");
            int c=getchar();

        }


    }

    mysql cus_check(string phone){
        mysql a;
        string command="select * from customer where Ph_no="+phone+";";
        string command1="select count(*) from customer where Ph_no="+phone+";";

        string **ptr=a.fetch_data(command1,command);
        
        return a;
    }

    void newbill(string p_no){
        string d_name,email;
        int member;
        // vector<string> medicine;
        // vector<string> medicine_q;
        
        cout<<endl;
 
        mysql a=cus_check(p_no);

        if(a.row_c==0){
            customer b;
            b.addcustomer(p_no);
        }
        else{

            system("clear");
            cout<<"Bill no:";
            string billno=billnogenerator();
            cout<<billno<<endl;

            string **ptr=a.results;

            d_name=ptr[0][1];
            email=ptr[0][2];
            member=stoii(ptr[0][3]);

            cout<<"Name:"<<ptr[0][1]<<endl;
            cout<<"Email:"<<ptr[0][2]<<endl;
            cout<<"Membership:"<<ptr[0][3]<<endl;



            vector<string> medicine_q;
            vector<string> medicine;


            string med,quantity;
            while(med[0]!='0'){
                cout<<"============================"<<endl;
                
                cout<<"Enter Medicine ID:";
                cin>>med;

                if(med[0]=='0'){
                    break;
                }

                cout<<"Enter Quantity:";
                cin>>quantity;
                medicine.push_back(med);
                medicine_q.push_back(quantity);
            }
            
            cout<<"============================"<<endl;
            // cout<<medicine[0];

            float total_price;
            total_price=pricecalc(medicine,medicine_q);
            cout<<"Before Discount:"<<total_price<<endl;

            if(member==1){
                total_price=total_price-(total_price*0.15);
            }

            cout<<"After Discount:"<<total_price<<endl;

            savebill(billno,p_no,medicine,medicine_q);
            // system("pause");
            int c=getchar();

        }
    }

    float pricecalc(vector<string> &med ,vector<string> &quan){

        float total=0;
        for(int i=0;i<med.size();i++){
            total=total+medprice(med[i],quan[i]);
            // cout<<total<<endl;
        }
        return total;
    }

    float medprice(string ID,string quantity){
        mysql a,b;
        float price;
        string command="select quantity,rate from stock where ID='"+ID+"';";
        string command1="select count(*) from stock where ID='"+ID+"';";
        string **ptr=a.fetch_data(command1,command);

        // cout<<command<<endl;

        price=stof(ptr[0][1])*stoii(quantity);

        string command2="update stock set quantity=quantity-"+quantity+" where ID='"+ID+"';";
        // cout<<command2<<endl;
        b.insert(command2);



        return price;

    }

    void savebill(string B_ID,string Phone,vector<string> &meds,vector<string> &quan){
        string medic="";
        string quantity="";
        for(int i=0;i<meds.size();i++){
            medic=medic+meds[i]+",";
            quantity=quantity+quan[i]+",";
        }
        medic.pop_back();
        quantity.pop_back();

        mysql a;
        string command1="insert into invoices values('"+B_ID+"','"+Phone+"','"
        +medic+"','"+quantity+"','"+Dateoftoday+"');";
        // cout<<command1<<endl;
        a.insert(command1);
    }

};


void displaytab(){
    mysql a;
    string command1="select * from stocks;";
    string command="select count(*) from stocks;";
    string **s=a.fetch_data(command,command1);
    // int temp=sizeof(s)/sizeof(s[0]);
    // for(int i=0;i<temp;i++){
    //     cout<<s[i][0]<<"\t"<<s[i][1]<<"\t"<<s[i][2]<<endl;
    // }
}

// int main(){
//     cout <<"\n=========================================\n\n";


//     displaytab();
//     return 0;
//     // int input=1;

//     // string username,passwd;
//     // cout<<"Enter Username:";
//     // cin>>username;
//     // cout<<"Enter Password:";
//     // cin>>passwd;
//     // PMS p;
//     // int n;

//     // if(p.verify(username,passwd)){
//     //     n=1;
//     // }
//     // else{
//     //     n=-1;
//     // }




//     // while(n>0){

//     //     try{
//     //     cout<<"============================"<<endl;
//     //     int c=getchar();
//     //     system("clear");
//     //     cout<<"============================"<<endl;
//     //     cout<<"For Stocks->       Press 1\n";
//     //     cout<<"For New Bill->     Press 2\n";
//     //     cout<<"For Edit Customer->Press 3\n";
//     //     cout<<"Input>";
//     //     cin>>input;
//     //     system("clear");
//     //     cout<<"============================"<<endl;

//     //     if(input==1){

//     //         cout<<"For New Stock->Press 1:\n";
//     //         cout<<"For Edit Stock->Press 2:\n";
//     //         cout<<"Input>";
//     //         cin>>input;
//     //         system("clear");

//     //         Stocks s;

//     //         if(input==1){
//     //             s.addstock();
//     //         }

//     //         else if(input==2){
                
//     //             s.editstock();
//     //         }
            
//     //     }

//     //     else if(input==2){
//     //         try{
//     //         bill b;
//     //         b.newbill();
//     //         }
//     //         catch(string phone){
//     //             bill b;
//     //             b.newbill(phone);
//     //         }
//     //     }

//     //     else if(input==3){
//     //         customer c;
//     //         c.editcustomer();
//     //         int c2=getchar();
//     //     }

//     //     }

//     //     catch(...){
//     //         cout<<"[Try Again!...]\n";
//     //         // system("pause");
//     //         // system("clear");
//     //     }




//     // }

    





//     // cout <<"\n=========================================\n\n";
//     // return 0;
// }
