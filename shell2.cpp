#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h> 
#include <chrono>
#include <ctime>
#include <vector>
using namespace std;

void info_table(string , string );
void tweets_table(string , string );
void tweet_like_table(string , string);

void del_info();
void update_password();
void update_username();

void retweets_table(string, string ,string );
void ret_like_table(string , string );

bool correct_parantheses_and(string );
int string_to_int(string );
string removeSpaces(string );
void display();
void half_eq(string ,vector <int> &,vector <string> &,string );
void expr_handling(string ,string ,vector <vector<int> > &);                      //logical expression handling
void args_func_insert(int &, string ,vector<string> &,vector <string> &, vector <int> & , vector <string> &  , vector <int> &);
vector <int>  Union(vector <int> , vector <int> );
vector <int>  Intersection(vector <int> , vector <int> );

int main()
{
    display();
    return 0;
}

vector <int>  Union(vector <int> vec1, vector <int> vec2) { 
    set<int> s; 
    for (int i = 0; i < vec1.size(); i++) 
        s.insert(vec1[i]); 

    for (int i = 0; i < vec2.size(); i++) 
        s.insert(vec2[i]); 

    vector <int> final;
    for (auto it = s.begin(); it != s.end(); it++) 
        final.push_back(*it);
    return final;
} 

vector <int>  Intersection(vector <int> vec1, vector <int> vec2) { 
    set<int> s; 

    for (int i = 0; i < vec1.size(); i++) 
        s.insert(vec1[i]); 
    
    vector <int> final;
    for (int i = 0; i < vec2.size(); i++) {
        if (s.find(vec2[i]) != s.end()) 
            final.push_back(vec2[i]);
    }
    return final;      
} 



void half_eq(string arg_first,vector <int> &id_s,vector <string> &arg_in_schemas,string table_name){

    int equal_ind,size_eq;
    bool equality_condition=true;

    size_t f_eq=arg_first.find("==");
    size_t f_not=arg_first.find("!=");
    if(f_eq != string::npos){
        equal_ind=f_eq;
        equality_condition=true;
        size_eq=3;
    }
    else if(f_not != string::npos){
        equal_ind=f_not;
        equality_condition=false;
        size_eq=3;
    }

    string the_one_in_table=removeSpaces(arg_first.substr(0,equal_ind));
    string the_one_with_the_value=removeSpaces(arg_first.substr(equal_ind+size_eq,arg_first.size()-equal_ind-size_eq-1));
    //cout<<the_one_in_table<<"  "<<the_one_with_the_value;

    int sotoon;
    for(int i=0;i<arg_in_schemas.size();i++){
        if(arg_in_schemas[i]==the_one_in_table){
            sotoon=i;
            break;
        }    
    }   
    //cout<<sotoon;
    
    //////////////////////////////////getting id from users
    if(table_name=="users_table"){
        sotoon+=1;
        ifstream user_table("users_table.txt");
        int id;
        string username,pass;
        while(user_table>>id>>username>>pass){
            if(equality_condition){
                if(sotoon==1){
                    if(username==the_one_with_the_value){
                        id_s.push_back(id);
                    }
                }
                else if(sotoon==2){
                    if(pass==the_one_with_the_value){
                        id_s.push_back(id);
                    }
                }
            }
            else if(!(equality_condition)){
                if(sotoon==1){
                    if(username!=the_one_with_the_value){
                        id_s.push_back(id);
                    }
                }
                else if(sotoon==2){
                    if(pass!=the_one_with_the_value){
                        id_s.push_back(id);
                    }
                }
            }    
        }
    }
    //////////////////////////////////getting id from tweet
    else if(table_name=="tweets_table"){
        sotoon+=1;
        ifstream tw_table("tweets_table.txt");
        int id1,id2;
        string user,tweet;
        while(tw_table>>id1>>id2>>user){
            getline(tw_table,tweet);
            if(equality_condition){
                if(sotoon==1){
                    if(user==the_one_with_the_value){
                        id_s.push_back(id1);
                    }
                }
                else if(sotoon==2){
                    if(tweet==the_one_with_the_value){
                        id_s.push_back(id1);
                    }
                }
            }
            else if(!(equality_condition)){
                if(sotoon==1){
                    if(user!=the_one_with_the_value){
                        id_s.push_back(id1);
                    }
                }
                else if(sotoon==2){
                    if(tweet!=the_one_with_the_value){
                        id_s.push_back(id1);
                    }
                }
            }    

        }
    } 
    
    ////////////////////////////////////id from retweet table
    else if(table_name=="retweets_table"){
        sotoon+=1;
        ifstream ret("retweets_table.txt");
        int id0,id1,id2;
        string user,retweet;
        while(ret>>id0>>id1>>id2>>user){
            getline(ret,retweet);
            if(equality_condition){
                if(sotoon==1){
                    if(user==the_one_with_the_value){
                        id_s.push_back(id0);
                    }
                }
                else if(sotoon==2){
                    if( (id1== the_one_with_the_value[0]-48) &&  (id2== the_one_with_the_value[1]-48) ){
                        id_s.push_back(id0);
                    }
                }
                else if(sotoon==3){
                    if(retweet==the_one_with_the_value){
                        id_s.push_back(id0);
                    }
                }
            }
            else if(!(equality_condition)){
                if(sotoon==1){
                    if(user!=the_one_with_the_value){
                        id_s.push_back(id0);
                    }
                }
                else if(sotoon==2){
                    if( (id1!= the_one_with_the_value[0]-48) ||  (id2!= the_one_with_the_value[1]-48) ){
                        id_s.push_back(id0);
                    }
                }
                else if(sotoon==3){
                    if(retweet!=the_one_with_the_value){
                        id_s.push_back(id0);
                    }
                }
            }
        }
    }

    ////////////////////id from tweet likes
    else if(table_name=="tweet_like_table"){
        ifstream tw_like("tweet_like_table.txt");
        int id1,id2;
        string user;
        vector <string> id_user;
        while(tw_like>>id1>>id2>>user){
            if(equality_condition){
                if(sotoon==0){
                    if(user==the_one_with_the_value){
                        id_user.push_back(user);
                    }
                }
                else if(sotoon==1){
                    if( (id1==int(the_one_with_the_value[0])-48) && (id2==int(the_one_with_the_value[1])-48)){
                        id_user.push_back(user);
                    }
                }
            }
            else if(!(equality_condition)){
                if(sotoon==0){
                    if(user!=the_one_with_the_value){
                        id_user.push_back(user);
                    }
                }
                else if(sotoon==1){
                    if( (id1 != int(the_one_with_the_value[0])-48) || (id2 != int(the_one_with_the_value[1])-48)){
                        id_user.push_back(user);
                    }
                }
            }
        }
        ifstream user_table("users_table.txt");
        int id;
        string us,pass;
        while(user_table>>id>>us>>pass){
            for(int q=0;q<id_user.size();q++){
                if(us==id_user[q]){
                    id_s.push_back(id);
                }
            }
        }
    }
    /////////////////////////////id from retweet_like table
    else if(table_name=="ret_like_table"){
        ifstream ret_like("ret_like_table.txt");
        vector <string> id_user;
        int id0,id1,id2;
        string user;
        while(ret_like>>id0>>id1>>id2>>user){
            if(equality_condition){
                if(sotoon==0){
                    if(user==the_one_with_the_value){
                        id_user.push_back(user);
                    }
                }
                else if(sotoon==1){
                    if( (id0==int(the_one_with_the_value[0])-48) && (id1==int(the_one_with_the_value[1])-48) && (id2==int(the_one_with_the_value[2])-48)){
                        id_user.push_back(user);
                    }
                }
            }
            else if(!(equality_condition)){
                if(equality_condition){
                    if(sotoon==0){
                        if(user!=the_one_with_the_value){
                            id_user.push_back(user);
                        }
                    }
                    else if(sotoon==1){
                        if( (id0!=int(the_one_with_the_value[0])-48) || (id1!=int(the_one_with_the_value[1])-48) || (id2!=int(the_one_with_the_value[2])-48)){
                            id_user.push_back(user);
                        }
                    }
                }
            }
        }
        ifstream user_table("users_table.txt");
        int id;
        string us,pass;
        while(user_table>>id>>us>>pass){
            for(int q=0;q<id_user.size();q++){
                if(us==id_user[q]){
                    id_s.push_back(id);
                }
            }
        }
    }

}


//////////////////////////expr handling
void expr_handling(string s,string table_name,vector < vector<int> > & help_me_please){

    vector <string> arg_in_schema;
    string table_for_parse,s1;   //field in our table
    ifstream schemas("schemas.txt");  
    while(getline(schemas,table_for_parse)){
        if(table_for_parse=="") continue;
        if(table_for_parse==table_name){
            getline(schemas,s1);
            while(s1!=""){
                int ind=0;
                string s2;
                while(s1[ind]!=' '){
                    s2+=s1[ind];
                    ind++;
                }
                //cout<<s2<<" ";
                arg_in_schema.push_back(s2);
                s1="";
                getline(schemas,s1);
            }
        }
    }


    vector <pair <int,int> > vec;
    int n =s.size();
    bool is_Balanced = true;
    int open_Paranthese = 0;
    for (int i = 0;i < n;i++) {
        if (s[i] == ')')
            open_Paranthese--;
        else if(s[i] == '(')
            open_Paranthese++;
        else
            continue;
        if (open_Paranthese < 0) {
            is_Balanced = false;
        }
    }
    if (open_Paranthese != 0)
        is_Balanced = false;
    if (is_Balanced) {
        stack <int> myStack;
        for (int i = 0;i < n;i++) {
            if (s[i] == ')') {
                if (myStack.empty())
                    is_Balanced = false;
                else {
                    vec.push_back(make_pair(myStack.top(),i));  //coordinates of parentheses 
                    myStack.pop();
                }
            }else if(s[i]=='(')
                myStack.push(i);
        }
    } else {
        cout << "NOT BALANCED"<<endl;
        exit(1);
    }

    cout<<endl;
    vector <string> vec_for_sub_par;   //for substring in parentheses
    for(int i=0;i<vec.size();i++){
        vec_for_sub_par.push_back(s.substr(vec[i].first,vec[i].second-vec[i].first+1));
        //cout<<s.substr(vec[i].first,vec[i].second-vec[i].first+1)<<"  ";
    }


    for(int i=0;i<vec_for_sub_par.size();i++){
        //cout<<vec_for_sub_par[i]<<endl;
        
        int op;
        int size_op;
        char op_condition;

        size_t f_AND=vec_for_sub_par[i].find("AND");
        size_t f_OR=vec_for_sub_par[i].find("OR");
        if(f_AND!=string::npos){
            op=f_AND;
            size_op=3;
            op_condition='a';
        }    
        else if(f_OR!=string::npos){
            op=f_OR;
            size_op=2;
            op_condition='o';
        }
        else
            op_condition='N'; //no operator
        // cout<<endl;
        // cout<<op<<"  "<<size_op;

        if(op_condition=='N'){
            int en=vec_for_sub_par[0].find(')');
            string strr;
            for(int w=1;w<en;w++){
                strr+=vec_for_sub_par[0][w];
            }
            string st1=removeSpaces(strr);
            vector <int> id_ss;
            half_eq(st1,id_ss,arg_in_schema,table_name);
            help_me_please.push_back(id_ss);
        }
        else{
        
            vector <int> final;

            if( (vec_for_sub_par[i][op-2]!=')') && (vec_for_sub_par[i][op+2]!='(') ){
                string arg_first=removeSpaces(vec_for_sub_par[i].substr(1,op-1));       //separating
                string arg_second=removeSpaces(vec_for_sub_par[i].substr(op+size_op,vec_for_sub_par[i].size()-op-size_op-1));
                //cout<<arg_first<<"  "<<arg_second;

                vector <int> id_s_first;
                vector <int> id_s_second;
                half_eq(arg_first,id_s_first,arg_in_schema,table_name);
                half_eq(arg_second,id_s_second,arg_in_schema,table_name);

                if(op_condition=='o'){
                    final=Union(id_s_first,id_s_second);
                    help_me_please.push_back(final);
                    final.clear();
                }
                else if(op_condition=='a'){
                    final=Intersection(id_s_first,id_s_second);
                    help_me_please.push_back(final);
                    final.clear();
                }
                
            }
            else if( (vec_for_sub_par[i][op-2]!=')') && (vec_for_sub_par[i][op+2]=='(')){
                string arg_first=removeSpaces(vec_for_sub_par[i].substr(1,op-1));
                vector <int> id_s_first;
                half_eq(arg_first,id_s_first,arg_in_schema,table_name);

                if(op_condition=='o'){
                    final=Union(id_s_first,help_me_please[i-1]);
                    help_me_please.push_back(final);
                    final.clear();
                    vector <vector<int>>::iterator it;
                    it=help_me_please.begin();
                    help_me_please.erase(it+i-1);
                }
                else if(op_condition=='a'){
                    final=Intersection(id_s_first,help_me_please[i-1]);
                    help_me_please.push_back(final);
                    final.clear();
                    vector <vector<int>>::iterator it;
                    it=help_me_please.begin();
                    help_me_please.erase(it+i-1);
                }
            }
            else if( (vec_for_sub_par[i][op-2]==')') && (vec_for_sub_par[i][op+2]!='(')){
                string arg_second=removeSpaces(vec_for_sub_par[i].substr(op+size_op,vec_for_sub_par[i].size()-op-size_op-1));
                vector <int> id_s_first;
                half_eq(arg_second,id_s_first,arg_in_schema,table_name);

                if(op_condition=='o'){
                    final=Union(id_s_first,help_me_please[i-1]);
                    help_me_please.push_back(final);
                    final.clear();
                    vector <vector<int>>::iterator it;
                    it=help_me_please.begin();
                    help_me_please.erase(it+i-1);
                }
                else if(op_condition=='a'){
                    final=Intersection(id_s_first,help_me_please[i-1]);
                    help_me_please.push_back(final);
                    final.clear();
                    vector <vector<int>>::iterator it;
                    it=help_me_please.begin();
                    help_me_please.erase(it+i-1);
                }
            }
            else if( (vec_for_sub_par[i][op-2]==')') && (vec_for_sub_par[i][op+2]=='(')){
                if(op_condition=='o'){
                    final=Union(help_me_please[i-1],help_me_please[i-2]);
                    help_me_please.push_back(final);
                    final.clear();
                    vector <vector<int>>::iterator it;
                    it=help_me_please.begin();
                    help_me_please.erase(it+i-1);
                    help_me_please.erase(it+i-2);
                }
                else if(op_condition=='a'){
                    final=Intersection(help_me_please[i-1],help_me_please[i-2]);
                    help_me_please.push_back(final);
                    final.clear();
                    vector <vector<int>>::iterator it;
                    it=help_me_please.begin();
                    help_me_please.erase(it+i-1);
                    help_me_please.erase(it+i-2);
                }
            }
        }    
    }
}




///for schema fields of each table
void args_func_insert(int &mot, string table_name,vector<string> & arg_in_s,vector <string> & arg_in_schema, vector <int> & is_unique , vector <string> & type_in_schema , vector <int> &max_for_char){

    string table_for_parse,s1;   //field in our table
    ifstream schemas("schemas.txt");  
    while(getline(schemas,table_for_parse)){
        if(table_for_parse=="") continue;
        if(table_for_parse==table_name){
            getline(schemas,s1);
            while(s1!=""){
                arg_in_schema.push_back(s1);
                s1="";
                getline(schemas,s1);
            }
        }
    }

    if(arg_in_schema.size()==arg_in_s.size()){  //equality of arguments

        for(int in_vec_field=0;in_vec_field<arg_in_schema.size();in_vec_field++){
            int letter=0;
            int type=0;
            while(arg_in_schema[in_vec_field][letter]!=' '){
                type++;
                letter++;
            }
            type+=1;
            int after_u=type;

            string type_;

            if(arg_in_schema[in_vec_field][type]=='U'){   //UNIQUE
                is_unique.push_back(1);
                while(arg_in_schema[in_vec_field][type]!=' '){
                    type++;
                    after_u++;
                }
                after_u+=1;
                for(int f=after_u;f<arg_in_schema[in_vec_field].size();f++){
                    type_+=arg_in_schema[in_vec_field][f];
                }
                type_in_schema.push_back(type_);
            }

            else if(arg_in_schema[in_vec_field][type]!='U'){    //type is anything but UNIQUE
                for(int f=type;f<arg_in_schema[in_vec_field].size();f++){
                    type_+=arg_in_schema[in_vec_field][f];
                }
                type_in_schema.push_back(type_);
            } 
            //cout<<type_<<" ";
        }
        for(int q=0;q<arg_in_schema.size();q++){
            
            if((type_in_schema[q][0]=='C')){    //char
                string max_size;
                int start=type_in_schema[q].find('[');
                int end=type_in_schema[q].find(']');
                for(int a=start+1;a<end;a++){
                    max_size+=type_in_schema[q][a];
                }
                int max_int=string_to_int(max_size);
                //cout<<max_int<<" ";
                max_for_char.push_back(max_int);
                // cout<<arg_in_s[q]<<" ";
                // cout<<arg_in_s[q].size()<<" ";

                if(arg_in_s.size()<=max_int+1){
                    mot+=1;
                }

            }
            else if((type_in_schema[q][0]=='B')){  //boolean
                if((arg_in_s[q]=="True") || (arg_in_s[q]=="False")){
                    mot+=1;
                }
                else{
                    cout<<"ERROR!! BAD TYPE "<<endl;
                    exit(1);
                }
            }
            else if((type_in_schema[q][0]=='T')){   //timestmap
                mot+=1;
            }
            else if((type_in_schema[q][0]=='I')){  //int
                int qq;
                for(int ch=0;ch<arg_in_s[q].size();ch++){
                    if((int(arg_in_s[q][ch])>=48) && (int(arg_in_s[q][ch])<=57)){
                        qq+=1;
                    }
                }
                if(qq==arg_in_s[q].size()){
                    mot+=1;
                }
            }
        }
    }
    else{
        cout<<"ARGS ARE NOT THE SAME!!";
        exit(1);
    }
}


//////////////////////////////removing space
string removeSpaces(string str)  
{ 
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    return str; 
} 

////////////////////////////////convert str to int
int string_to_int(string s){
    stringstream hi(s);
    int x = 0; 
    hi >> x; 
    return x;
}

void display(){

    //users_table     for  id username  password
    //tweets_table    for user_ id  nth_id  tweet
    //tweet_like_table  for  tweet_id    username  tweet
    //ret_like_table    for  user_id  tweet_id    username  retweet
    //retweets_table   for  retweet_id    username  retweet

    vector <string> table_name_in_schema;
    ifstream schema("schemas.txt");  //schemas
    string line;
    while(getline(schema,line)){
        if(line=="") continue;
        if( line.substr(line.size()-5,5)=="table"){
            int s=line.size();
            table_name_in_schema.push_back(line.substr(0,s));
        }
    }

    string s="SELECT FROM users_table WHERE ( password=='1234' );";
    string s8="INSERT INTO ret_like_table VALUES (amir,111);";

    string table_name;
    ////////////////////////////////////////////////////////////////////////insert
    if((s.substr(0,6)=="INSERT") && (s[s.size()-1]==';')){   //if insert
        if(s.substr(0,11)=="INSERT INTO"){
            int start_shift=12;
            while(s[start_shift]!=' '){
                table_name+=s[start_shift];
                start_shift++;
            }
            int c=0;
            int index_table_name;
            for(int i=0;i<table_name_in_schema.size();i++){
                if(table_name_in_schema[i]==table_name){
                    c+=1;
                    index_table_name=i;
                }    
            }    
            if(c==1){     //if table name exist

                int end_shift=start_shift;
                if(s.substr(end_shift+1,6)=="VALUES"){       //if VALUES
                    int start_par=end_shift+9;

                    int check_parantheses=end_shift+8;
                    string expr;
                    while(s[check_parantheses]!=';'){
                        expr+=s[check_parantheses];
                        check_parantheses++;
                    }     

                    if(correct_parantheses_and(expr)){  //correct expr

                        vector <string> arg_in_s;  //args for line INSERT

                        string ss;
                        while(s[start_par]!=')'){
                            ss+=s[start_par];
                            start_par++;
                        }
                        ss=removeSpaces(ss);
                        //cout<<ss<<" ";
                        string delimiter = ",";
                        size_t pos = 0;
                        string token;
                        while ((pos = ss.find(delimiter)) != std::string::npos) {
                            token = ss.substr(0, pos);
                            arg_in_s.push_back(token);
                            //cout<<token<<" ";
                            ss.erase(0, pos + delimiter.length());
                        }
                        arg_in_s.push_back(ss);
                        //cout<<arg_in_s.size();

                        int mot=0;

                        vector <string>  arg_in_schema;  //each field
                        vector <int>  is_unique;     //is_unique with 1 and 0
                        vector <string>  type_in_schema;    //types in schema
                        vector <int> max_for_char;     //maximum_char

                        args_func_insert(mot,table_name,arg_in_s, arg_in_schema,is_unique,type_in_schema,max_for_char);
                        //cout<<mot;
                        if(mot==arg_in_s.size()){
                            if(table_name=="users_table")
                                info_table(arg_in_s[0],arg_in_s[1]);
                            else if(table_name=="tweets_table")
                                tweets_table(arg_in_s[0],arg_in_s[1]);
                            else if(table_name=="tweet_like_table")
                                tweet_like_table(arg_in_s[0],arg_in_s[1]);
                            else if(table_name=="retweets_table")
                                retweets_table(arg_in_s[0],arg_in_s[1],arg_in_s[2]);
                            else if(table_name=="ret_like_table")
                                ret_like_table(arg_in_s[0],arg_in_s[1]);
                        }
                        else{
                            cout<<"NOT MATCH WITH SCHEMA!!"<<endl;
                            exit(1);
                        }
                    }   
                    else{
                        cout<<"BAD EXPRESSION!!"<<endl;
                        exit(1);
                    } 
                }
                else{
                    cout<<"ERROR"<<endl;   //syntax error
                    exit(1);
                }     
            }
            else{
                cout<<"NO TABLE WITH THIS NAME!!"<<endl;
                exit(1);
            }    
        }
        else{  //syntax error
            cout<<"ERROR"<<endl;
            exit(1);
        }    
    }
    /////////////////////////////////////////////////////////////////////////////////select
    else if((s.substr(0,6)=="SELECT") && (s[s.size()-1]==';') && (s.substr(7,4)=="FROM")){
        vector < vector<int> > help_me_please;
        int start=12;
        while(s[start]!=' '){
            table_name+=s[start];    //table name
            start++;
        }
        int c=0;
        int index_table_name;      
        for(int i=0;i<table_name_in_schema.size();i++){
            if(table_name_in_schema[i]==table_name){
                c+=1;
                index_table_name=i;
            } 
        }    

        string expr;
        if(c==1){    //if table_name in schema
            start++;
            if(s.substr(start,5)=="WHERE"){
                start+=6;
                while(s[start]!=';'){
                    expr+=s[start];      //main expression
                    start++;
                }
                //cout<<expr;
                vector <int> main_id;
                expr_handling(expr,table_name,help_me_please);
                for(int i=0;i<help_me_please.size();i++){
                    for(int j=0;j<help_me_please[i].size();j++){
                        main_id.push_back(help_me_please[i][j]);
                    }
                }
                // for(int i=0;i<main_id.size();i++){
                //     cout<<main_id[i]<<" ";
                // }
                

            }
            else{
                cout<<"SYNTAX ERROR!!"<<endl;
                exit(1);
            }

        }  
        else{
            cout<<"NO TABLE WITH THIS NAME!!"<<endl;
            exit(1);
        }
    }
    else{
        cout<<"SYNTAX ERROR!!"<<endl;
        exit(1);
    }
}


int id=1;
unordered_set <string> user_set;
unordered_set <string> password_set;
unordered_set <int> id_set;

////////////////////////////////////////////////////creating information table
void info_table(string username,string password){
    ofstream user_file("users_table.txt" , ios::app);

    user_file<<id<<"    "<<username<<"          "<<password<<endl;
    id+=1;
    user_file.close();
}

ofstream tweet_file("tweets_table.txt" , ios::app);    //thats for inserting the tweets

///////////////////////////////////////////////tweets table
void tweets_table(string str, string tweet){


    // /////////////////////////////////////error if username wasnt in our file
    // if(user_set.find(str)==user_set.end()){   
    //     cout<<"NOT FOUND!!"<<endl;
    //     display();
    // }
    // /////////////////////////////////////

    ifstream user_file("users_table.txt");
    int id,tweet_id;
    int nth_tweet=1;                      //the second part of tweet_id
    string password,username;

    while(user_file>>id>>username>>password){
        if(str==username){
            tweet_id=id;
        }
    }

    // string tweet;
    // cout<<"enter tweet text: ";
    // auto start = chrono::system_clock::now();
    // cin>>tweet;
    // auto end = chrono::system_clock::now();
    // time_t end_time = chrono::system_clock::to_time_t(end);
    // string time=std::ctime(&end_time);


    ifstream file("tweets_table.txt",ios::in);

    int id1,id2;
    string tweet1,time,us;
    while(file>>id1>>id2>>us){
        getline(file,tweet1);
        getline(file,time);
        if(id1==tweet_id){
            nth_tweet+=1;
        }
    }
    ofstream file_tweet("tweets_table.txt",ios::app);
    file_tweet<<tweet_id<<" "<<nth_tweet<<"    "<<str<<"    "<<tweet<<"    "<< time<<endl;
}

////////////////////////////////////insert likes(usernames) for every tweets
void tweet_like_table(string str,string tweetID){
    ofstream like_file("tweet_like_table.txt",ios::app);

    int id1=int(tweetID[0]-48);
    int id2=int(tweetID[1]-48);

    // /////////////////////////////////////error if username wasnt in our file
    // if(user_set.find(str)==user_set.end()){   
    //     cout<<"NOT FOUND!!"<<endl;
    //     display();
    // }
    // /////////////////////////////////////

    string tweet,time1,us;
    int p1,p2;
    ifstream file("tweets_table.txt");
    while(file>>p1>>p2>>us>>tweet){
        getline(file,time1);
        if((p1==id1) && (p2==id2)){
            like_file<<id1<<" "<<id2<<"   "<<str<<endl;
            like_file.close();
        }
    }
}

///////////////////////////////////////insert likes(usernames) for every retweets
void ret_like_table(string str, string retID){
    ofstream file("ret_like_table.txt",ios::app);

    // /////////////////////////////////////error if username wasnt in our file
    // if(user_set.find(str)==user_set.end()){   
    //     cout<<"NOT FOUND!!"<<endl;
    //     display();
    // }
    // /////////////////////////////////////

    int user_id=int(retID[0]-48);
    int id1=int(retID[1]-48);
    int id2=int(retID[2]-48);

    string ret,user;
    int p0,p1,p2;
    ifstream ret_file("retweets_table.txt");

    while(ret_file>>p0>>p1>>p2>>user){
        getline(ret_file,ret);
        if((p0==user_id) && (p1==id1) && (p2==id2)){
            file<<user_id<<" "<<id1<<" "<<id2<<"    "<<str<<endl;
            file.close();
        }
    }
}


///////////////////////////////////////delete a line containing the given username
void del_info(){
    ifstream file("users_table.txt");
    string str;
    cout<<"enter username: ";
    cin>>str;

    ofstream temp("temp.txt");

    int id,user_id;
    string password,username;
    while(file>>id>>username>>password){
        if(str == username){
            user_id=id;
            continue;
        }
        else{
            temp<<id<<"    "<<username<<"          "<<password<<endl;
        }
    }

    /////////////////////////////////////error if username wasnt in our file
    if(user_set.find(str)==user_set.end()){   
        cout<<"NOT FOUND!!"<<endl;
        display();
    }


    /////////////////////////////////////delete tweets and retweets of cleared user
    else{
        ofstream del_tweets("temp_tweets.txt");     //tweets
        ifstream tw("tweets_table.txt");   

        int p1,p2;
        string tweet,us,time;
        while(tw>>p1>>p2>>us){
            getline(tw,tweet);
            getline(tw,time);
            if(user_id==p1){
                continue;
            }
            else{
                del_tweets<<p1<<" "<<p2<<"    "<<tweet<<endl;
            }
        }
        del_tweets.close();
        remove("tweets_table.txt");
        rename("temp_tweets.txt", "tweets_table.txt");


        ofstream del_ret("temp_ret.txt");    //retweets
        ifstream ret("retweets_table.txt");

        int e0,e1,e2;
        string retweet,use;
        while(ret>>e0>>e1>>e2>>use){
            getline(ret,retweet);
            if(user_id==e0){
                continue;
            }
            else{
                del_ret<<e0<<" "<<e1<<" "<<e2<<"    "<<use<<"    "<<retweet<<endl;
            }
        }
        del_ret.close();
        remove("retweets_table.txt");
        rename("temp_ret.txt","retweets_table.txt");
    }
    ///////////////////////////////////////////////////////////////////////end tweets delete


    ///////////////////////////////////////////////////delete likes of deleted user

    ofstream like_tweet_file("temp_tweet_file.txt");    //tweets_like
    ifstream tw_file("tweet_like_table.txt");

    int u1,u2;
    string tw_like,user_like;
    while(tw_file>>u1>>u2>>user_like){
        getline(tw_file,tw_like);
        if(str==user_like){
            continue;
        }
        else{
            like_tweet_file<<u1<<" "<<u2<<"    "<<str<<"    "<<tw_like<<endl;
        }
    }
    like_tweet_file.close();
    remove("tweet_like_table.txt");
    rename("temp_tweet_file.txt","tweet_like_table.txt");



    ofstream like_ret_file("temp_ret_file.txt");     //retweets_like
    ifstream ret_file("ret_like_table.txt");

    int i0,i1,i2;
    string ret_user,ret_text;

    while(ret_file>>i0>>i1>>i1>>ret_user){
        getline(ret_file,ret_text);
        if(str==ret_user){
            continue;
        }
        else{
            like_ret_file<<i0<<" "<<i1<<" "<<i2<<"    "<<str<<"    "<<ret_text<<endl;
        }
    }
    like_ret_file.close();
    remove("ret_like_table.txt");
    rename("temp_ret_file.txt","ret_like_table.txt");
    ///////////////////////////////////////////////////////////end like delete


    temp.close();
    remove("users_table.txt");
    rename("temp.txt","users_table.txt");
    display();
}
///////////////////////////////////////////update password with given username
void update_password(){
    ifstream file("users_table.txt");
    string str;
    cout<<"enter user u want to change its password: ";
    cin>>str;

    /////////////////////////////////////error if username wasnt in our file
    if(user_set.find(str)==user_set.end()){   
        cout<<"NOT FOUND!!"<<endl;
        display();
    }
    /////////////////////////////////////
    
    ofstream temp("temp.txt");
    int id;
    string password,username;

    while(file>>id>>username>>password){
        if(str==username){
            cout<<"enter your old password: ";
            string check_pass;
            cin>>check_pass;
            if(check_pass == password){
                cout<<"enter your new password: ";
                string new_pass;
                cin>>new_pass;
                password=new_pass;
            }
            else{
                while(check_pass!=password){
                cout<<"enter your new password: ";
                string new_pass;
                cin>>new_pass;
                password=new_pass;
                }
            }
        }
        temp<<id<<"    "<<username<<"          "<<password<<endl;       // if user wasnt in file ??
    }
    temp.close();
    remove("users_table.txt");
    rename("temp.txt","users_table.txt");
    display();
}

///////////////////////////////////////////////////update username by giving the old one
void update_username(){
    ifstream file("users_table.txt");
    string str;
    cout<<"enter username u want to change : ";
    cin>>str;

    /////////////////////////////////////error if username wasnt in our file
    if(user_set.find(str)==user_set.end()){   
        cout<<"NOT FOUND!!"<<endl;
        display();
    }
    /////////////////////////////////////

    ofstream temp("temp.txt");
    int id;
    string password,username;

    while(file>>id>>username>>password){
        if(str==username){
            cout<<"enter your new username: ";
            string new_user;
            cin>>new_user;

            if(user_set.find(new_user)==user_set.end()){      //duplicated username
                user_set.insert(new_user);
                username=new_user;
            }
            else{
                while(!(user_set.find(new_user)==user_set.end())){
                    cout<<"this username has already being used! "<<endl;
                    cout<<"enter your username: ";
                    cin>>new_user;
                    username=new_user;
                }
            }
        }
        temp<<id<<"    "<<username<<"          "<<password<<endl;
    }
    temp.close();
    remove("users_table.txt");
    rename("temp.txt","users_table.txt");
    display();
}

///////////////////////////////////////////////////retweets_table
void retweets_table(string str,string tweetID,string tweet){
    ofstream ret_file("retweets_table.txt", ios::app);

    int id1=int(tweetID[0]-48);
    int id2=int(tweetID[1]-48);
    // /////////////////////////////////////error if username wasnt in our file
    // if(user_set.find(str)==user_set.end()){   
    //     cout<<"NOT FOUND!!"<<endl;
    //     display();
    // }
    // /////////////////////////////////////

    ifstream user_file("users_table.txt");
    string password,username;
    int user_id;

    while(user_file>>id>>username>>password){
        if(str==username){
            user_id=id;
        }
    }

    ifstream tweet_file("tweets_table.txt");
    int p1,p2;
    string us,time;

    while(tweet_file>>p1>>p2>>us){
        getline(tweet_file,tweet);
        getline(tweet_file,time);
        if((p1==id1) && (p2=id2)){
            ret_file<<user_id<<" "<<id1<<" "<<id2<<"    "<<str<<"    "<<tweet<<endl;
            ret_file.close();
        }
    }
}
////////////////////////////////////////////////for checking the expr
bool correct_parantheses_and(string expr) { 
	stack<char> st; 
	char ch; 
	for (int i = 0; i < expr.length(); i++) { 
		if (expr[i] == '(' || expr[i] == '<') { 
			st.push(expr[i]); 
			continue; 
		} 
		if (st.empty()) 
			return false; 

		switch (expr[i]) { 
		case ')': 
			ch = st.top(); 
			st.pop(); 
			if (ch == '<') 
				return false; 
			break; 
		case '>': 
			ch=st.top(); 
			st.pop(); 
			if (ch == '(') 
				return false; 
			break; 
		} 
	} 
	return (st.empty()); 
} 