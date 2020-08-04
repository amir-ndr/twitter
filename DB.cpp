#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h> 
using namespace std;

void info_table();
void tweets_table();
void tweet_like_table();
void del_info();
void update_password();
void update_username();
void retweets_table();
void ret_like_table();
void display();

int main()
{
    display();
    return 0;
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


    cout<<"enter number: ";
    int choice;
    cin>>choice;

    switch(choice) {
        case 1:
            info_table();
            break;
        case 2:
            tweets_table();
            break;
        case 3:
            tweet_like_table();
            break;
        case 4:
            del_info();
            break;
        case 5:
            update_password();
            break;
        case 6:
            update_username();
            break;
        case 7:
            retweets_table();
            break;
        case 8:
            ret_like_table();
            break;    
    }
}


int id=1;
unordered_set <string> user_set;
unordered_set <string> password_set;
unordered_set <int> id_set;

////////////////////////////////////////////////////creating information table
void info_table(){
    ofstream user_file("users_table.txt" , ios::app);

    string username;
    string password;
    
    cout<<"enter your username: "<<endl;
    cin>>username;

    if(user_set.find(username)==user_set.end()){      //duplicated username
        user_set.insert(username);
    }
    else{
        while(!(user_set.find(username)==user_set.end())){
            cout<<"this username has already being used! "<<endl;
            cout<<"enter your username: ";
            cin>>username;
        }
    }
    

    cout<<"enter your password: "<<endl;
    cin>>password;
    password_set.insert(password);

    // if(id_set.find(id)==id_set.end()){      //duplicated id
    //     id_set.insert(id);
    // }
    // else{
    //     while(!(id_set.find(id)==id_set.end())){
    //         id+=1;
    //     }
    // }

    user_file<<id<<"    "<<username<<"          "<<password<<endl;
    id+=1;
    user_file.close();

    // unordered_set<int> :: iterator itr; 
    // for (itr = id_set.begin(); itr != id_set.end(); itr++) 
    //     cout << (*itr) << endl; 
    // unordered_set<string> :: iterator itr2; 
    // for (itr2 = password_set.begin(); itr2 != password_set.end(); itr2++) 
    //     cout << (*itr2) << endl; 

    display();
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
    cin>>tweet;

    ifstream file("tweets_table.txt",ios::in);

    int id1,id2;
    string tweet1;
    while(file>>id1>>id2){
        getline(file,tweet1);
        if(id1==tweet_id){
            nth_tweet+=1;
        }
    }
    ofstream file_tweet("tweets_table.txt",ios::app);
    file_tweet<<tweet_id<<" "<<nth_tweet<<"    "<<tweet<<endl;
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

    string tweet;
    int p1,p2;
    ifstream file("tweets_table.txt");
    while(file>>p1>>p2){
        getline(file,tweet);
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