#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h> 
#include <chrono>
#include <ctime>
#include <vector>
using namespace std;

void info_table(string , string );
void tweets_table();
void tweet_like_table();
void del_info();
void update_password();
void update_username();
void retweets_table();
void ret_like_table();
bool correct_parantheses_and(string );
int string_to_int(string );
void display();

int main()
{
    display();
    return 0;
}

int string_to_int(string s){
    stringstream hi(s);
    int x = 0; 
    hi >> x; 
    return x;
}

void display(){
    cout<<"=======menu========"<<endl;
    cout<<"1. for inserting on users table"<<endl;
    cout<<"2. for inserting on tweets table"<<endl;
    cout<<"3. for inserting on tweet_like_table"<<endl;
    cout<<"4. for deleting info"<<endl;
    cout<<"5. for updating password"<<endl;
    cout<<"6. for changing username"<<endl;
    cout<<"7. for inserting on retweets table"<<endl;
    cout<<"8. for inserting on retweet_like_table"<<endl;

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

    string s="INSERT INTO <users_table> VALUES (<amir-ndr>,<9092301030>);";

    string table_name;
    if(s.substr(0,6)=="INSERT"){   //if insert
        if(s.substr(0,11)=="INSERT INTO"){
            int start_shift=13;
            while(s[start_shift]!='>'){
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
                if(s.substr(end_shift+2,6)=="VALUES"){       //if VALUES
                    int start_par=end_shift+11;

                    int check_parantheses=end_shift+9;
                    string expr;
                    while(s[check_parantheses]!=';'){
                        expr+=s[check_parantheses];
                        check_parantheses++;
                    }     

                    if(correct_parantheses_and(expr)){  //correct expr

                        vector <string> arg_in_s;  //args for line INSERT
                        while(start_par!=s.size()){
                            string arg;
                            while(s[start_par]!='>'){
                                arg+=s[start_par];
                                start_par++;
                            }
                            arg_in_s.push_back(arg);
                            start_par+=3;
                        }

                        string table_for_parse,s1;
                        vector <string> arg_in_schema;     //field in our table
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

                            vector <int> is_unique;
                            vector <string> type_in_schema;

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

                            }
                            int mot=0;
                            for(int q=0;q<arg_in_schema.size();q++){
                                
                                vector <int> max_for_char;
                                if((type_in_schema[q][0]=='C')){
                                    string max_size;
                                    int start=type_in_schema[q].find('[');
                                    int end=type_in_schema[q].find(']');
                                    for(int a=start+1;a<end;a++){
                                        max_size+=type_in_schema[q][a];
                                    }
                                    int max_int=string_to_int(max_size);
                                    max_for_char.push_back(max_int);
        
                                    if(arg_in_s.size()<=max_int){
                                        mot+=1;
                                    }

                                }


                            }
                            
                            if(mot==arg_in_s.size()){
                                info_table(arg_in_s[0],arg_in_s[1]);
                            }
                            else{
                                cout<<"NOT MATCH WITH SCHEMA!!"<<endl;
                                exit(1);
                            }
                        }
                        else{
                            cout<<"ARGS ARE NOT THE SAME!!";
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
    else{
        cout<<"ERROR"<<endl;
        exit(1);
    }


    // cout<<"enter number: ";
    // int choice;
    // cin>>choice;

    // switch(choice) {
    //     case 1:
    //         info_table();
    //         break;
    //     case 2:
    //         tweets_table();
    //         break;
    //     case 3:
    //         tweet_like_table();
    //         break;
    //     case 4:
    //         del_info();
    //         break;
    //     case 5:
    //         update_password();
    //         break;
    //     case 6:
    //         update_username();
    //         break;
    //     case 7:
    //         retweets_table();
    //         break;
    //     case 8:
    //         ret_like_table();
    //         break;    
    // }
}


int id=1;
unordered_set <string> user_set;
unordered_set <string> password_set;
unordered_set <int> id_set;

////////////////////////////////////////////////////creating information table
void info_table(string username,string password){
    ofstream user_file("users_table.txt" , ios::app);

    // if(user_set.find(username)==user_set.end()){      //duplicated username
    //     user_set.insert(username);
    // }
    // else{
    //     while(!(user_set.find(username)==user_set.end())){
    //         cout<<"this username has already being used! "<<endl;
    //         cout<<"enter your username: ";
    //         cin>>username;
    //     }
    // }

    user_file<<id<<"    "<<username<<"          "<<password<<endl;
    id+=1;
    user_file.close();
}

ofstream tweet_file("tweets_table.txt" , ios::app);    //thats for inserting the tweets

///////////////////////////////////////////////tweets table
void tweets_table(){

    cout<<"enter username: ";
    string str;
    cin>>str;

    /////////////////////////////////////error if username wasnt in our file
    if(user_set.find(str)==user_set.end()){   
        cout<<"NOT FOUND!!"<<endl;
        display();
    }
    /////////////////////////////////////

    ifstream user_file("users_table.txt");
    int id,tweet_id;
    int nth_tweet=1;                      //the second part of tweet_id
    string password,username;

    while(user_file>>id>>username>>password){
        if(str==username){
            tweet_id=id;
        }
    }

    string tweet;
    cout<<"enter tweet text: ";
    auto start = chrono::system_clock::now();
    cin>>tweet;
    auto end = chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(end);
    string time=std::ctime(&end_time);


    ifstream file("tweets_table.txt",ios::in);

    int id1,id2;
    string tweet1;
    while(file>>id1>>id2>>tweet1){
        getline(file,time);
        if(id1==tweet_id){
            nth_tweet+=1;
        }
    }
    ofstream file_tweet("tweets_table.txt",ios::app);
    file_tweet<<tweet_id<<" "<<nth_tweet<<"    "<<tweet<<"    "<< time<<endl;
    display();
    
}

////////////////////////////////////insert likes(usernames) for every tweets
void tweet_like_table(){
    ofstream like_file("tweet_like_table.txt",ios::app);

    cout<<"enter the twitter_id (id1 id2)(separate by space): ";
    int id1,id2;
    cin>>id1>>id2;

    cout<<"enter your username: ";
    string str;
    cin>>str;

    /////////////////////////////////////error if username wasnt in our file
    if(user_set.find(str)==user_set.end()){   
        cout<<"NOT FOUND!!"<<endl;
        display();
    }
    /////////////////////////////////////

    string tweet,time1;
    int p1,p2;
    ifstream file("tweets_table.txt");
    while(file>>p1>>p2>>tweet){
        getline(file,time1);
        if((p1==id1) && (p2==id2)){
            like_file<<id1<<" "<<id2<<"   "<<str<<"    "<<tweet<<endl;
            like_file.close();
        }
    }
    display();
}

///////////////////////////////////////insert likes(usernames) for every retweets
void ret_like_table(){
    ofstream file("ret_like_table.txt",ios::app);

    cout<<"enter your username: ";
    string str;
    cin>>str;

    /////////////////////////////////////error if username wasnt in our file
    if(user_set.find(str)==user_set.end()){   
        cout<<"NOT FOUND!!"<<endl;
        display();
    }
    /////////////////////////////////////

    cout<<"enter your retweet id (id1 id2 id3) (separate by space): ";
    int user_id,id1,id2;
    cin>>user_id>>id1>>id2;

    string ret;
    int p0,p1,p2;
    ifstream ret_file("retweets_table.txt");

    while(ret_file>>p0>>p1>>p2){
        getline(ret_file,ret);
        if((p0==user_id) && (p1==id1) && (p2==id2)){
            file<<user_id<<" "<<id1<<" "<<id2<<"    "<<str<<"    "<<ret<<endl;
            file.close();
        }
    }
    display();
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
        string tweet;
        while(tw>>p1>>p2){
            getline(tw,tweet);
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
        string retweet;
        while(ret>>e0>>e1>>e2){
            getline(ret,retweet);
            if(user_id==e0){
                continue;
            }
            else{
                del_ret<<e0<<" "<<e1<<" "<<e2<<"    "<<retweet<<endl;
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
void retweets_table(){
    ofstream ret_file("retweets_table.txt", ios::app);

    cout<<"enter your username: ";
    string str;
    cin>>str;

    cout<<"enter the tweet id (id1 id2)(separate by space): ";
    int id1,id2;
    cin>>id1>>id2;


    /////////////////////////////////////error if username wasnt in our file
    if(user_set.find(str)==user_set.end()){   
        cout<<"NOT FOUND!!"<<endl;
        display();
    }
    /////////////////////////////////////

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
    string tweet;

    while(tweet_file>>p1>>p2){
        getline(tweet_file,tweet);
        if((p1==id1) && (p2=id2)){
            ret_file<<user_id<<" "<<id1<<" "<<id2<<"    "<<tweet<<endl;
            ret_file.close();
        }
    }
    display();
}
////////////////////////////////////////////////for checking the expr
bool correct_parantheses_and(string expr) 
{ 
	stack<char> s; 
	char x; 

	for (int i = 0; i < expr.length(); i++) { 
		if (expr[i] == '(' || expr[i] == '<') { 
			s.push(expr[i]); 
			continue; 
		} 

		if (s.empty()) 
			return false; 

		switch (expr[i]) { 

		case ')': 
			x = s.top(); 
			s.pop(); 
			if (x == '<') 
				return false; 
			break; 

		case '>': 
			x = s.top(); 
			s.pop(); 
			if (x == '(') 
				return false; 
			break; 
		} 
	} 
	return (s.empty()); 
} 