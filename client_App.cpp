#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <unordered_set>
#include <ctime>
#include <chrono>

using namespace std;

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    //	hint
    int port = 54000;
    string ip = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &hint.sin_addr);

    int connect1 = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connect1 == -1){
        return 1;
    }

    cout<<endl<<"====================="<<endl;
    cout<<"=========twitter========"<<endl;
    cout<<"====================="<<endl<<endl<<endl;

    char buf[4096];
    string choice;
    unordered_set <string> user_set;
    int login_id;
    string user_login;
    string ret;

    while(true){
        
        cout<<endl<<endl<<"1.for register "<<endl;
        cout<<"2.for log in "<<endl;
        cout<<"3.for tweet "<<endl;
        cout<<"4.for retweet "<<endl;
        cout<<"5.for show tweets(view) "<<endl;
        cout<<"6.for like a tweet "<<endl;
        cout<<"7.for like a retweet "<<endl;
        cout<<"8.for show likes of a tweet "<<endl;
        cout<<"9.for delete account "<<endl<<endl;
        cout<<"enter your number: ";
        getline(cin,choice);

        //////////////////////////////////////////////// register
        if(choice=="1"){
            string for_send;
            string username,password;
            cout<<"enter your username: ";
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
                user_set.insert(username);
            }

            cout<<"enter your password: ";
            cin>>password;
            for_send+=choice+','+username+','+password;

            int send1 = send(sock, for_send.c_str(), for_send.size() + 1, 0);
            if (send1 == -1){
                cout << "Could not send to server!\r\n";
                continue;
            }

            memset(buf, 0, 4096);
            int rec = recv(sock, buf, 4096, 0);
            if (rec == -1){
                cout << "There was an error getting response from server\r\n";
            }
        }

        ///////////////////////////////////////// log in
        else if(choice=="2"){      
            string username,password;
            cout<<"enter your username: ";
            cin>>username;
            while(user_set.find(username)==user_set.end()){
                cout<<"NOT FOUND "<<endl;
                cout<<"enter your username: ";
                cin>>username;
            }
            cout<<"enter your password: ";
            cin>>password;
            ifstream us("users_table.txt");
            string user,pass;
            int id;
            while(us>>id>>user>>pass){
                if(username==user){
                    while(password!=pass){
                        cout<<"WRONG PASSWORD "<<endl;
                        cout<<"enter your password: ";
                        cin>>password;
                    }
                    user_login=username;
                    login_id=id;
                }
            }
        }

        /////////////////////////////////////////// tweet
        else if(choice=="3"){
            string username,tweet,time,for_send;

            cout<<"enter your tweet text: ";
            auto start = chrono::system_clock::now();
            getline(cin,tweet);
            auto end = chrono::system_clock::now();
            time_t end_time = chrono::system_clock::to_time_t(end);
            time=std::ctime(&end_time);

            for_send+=choice+','+user_login+','+tweet+','+time;
            int send1 = send(sock, for_send.c_str(), for_send.size() + 1, 0);
            if (send1 == -1){
                cout << "Could not send to server!\r\n";
                continue;
            }

            memset(buf, 0, 4096);
            int rec = recv(sock, buf, 4096, 0);
            if (rec == -1){
                cout << "There was an error getting response from server\r\n";
            }

        }

        /////////////////////////////////////// retweets
        else if(choice=="4"){
            string tweetID,for_send;

            cout<<"enter the tweet id: ";
            cin>>tweetID;

            int id1=int(tweetID[0]-48);
            int id2=int(tweetID[1]-48);

            ifstream tweet_file("tweets_table.txt");
            int p1,p2;
            string us,time,tweet;

            while(tweet_file>>p1>>p2>>us){
                getline(tweet_file,tweet);
                getline(tweet_file,time);
                if((p1==id1) && (p2==id2)){
                    ret=tweet;
                }
            }
            for_send+=choice+','+user_login+','+tweetID+','+ret;
            int send1 = send(sock, for_send.c_str(), for_send.size() + 1, 0);
            if (send1 == -1){
                cout << "Could not send to server!\r\n";
                continue;
            }

            memset(buf, 0, 4096);
            int rec = recv(sock, buf, 4096, 0);
            if (rec == -1){
                cout << "There was an error getting response from server\r\n";
            }
        }

        /////////////////////////////////////  like a tweet
        else if(choice=="6"){
            string tweetID,for_send;
            cout<<"enter the tweetID: ";
            cin>>tweetID;

            for_send+=choice+','+user_login+','+tweetID;
            int send1 = send(sock, for_send.c_str(), for_send.size() + 1, 0);
            if (send1 == -1){
                cout << "Could not send to server!\r\n";
                continue;
            }

            memset(buf, 0, 4096);
            int rec = recv(sock, buf, 4096, 0);
            if (rec == -1){
                cout << "There was an error getting response from server\r\n";
            }
        }

        //////////////////////////////////// like a retweet
        else if(choice=="7"){
            string retID,for_send;

            cout<<"enter the retweet_id: ";
            cin>>retID;
            for_send+=choice+','+user_login+','+retID;
            int send1 = send(sock, for_send.c_str(), for_send.size() + 1, 0);
            if (send1 == -1){
                cout << "Could not send to server!\r\n";
                continue;
            }

            memset(buf, 0, 4096);
            int rec = recv(sock, buf, 4096, 0);
            if (rec == -1){
                cout << "There was an error getting response from server\r\n";
            }
        }

        /////////////////////////////////// delete account
        else if(choice=="9"){
            string for_send;
            for_send+=choice+','+user_login;
            int send1 = send(sock, for_send.c_str(), for_send.size() + 1, 0);
            if (send1 == -1){
                cout << "Could not send to server!\r\n";
                continue;
            }

            memset(buf, 0, 4096);
            int rec = recv(sock, buf, 4096, 0);
            if (rec == -1){
                cout << "There was an error getting response from server\r\n";
            }
        }

        /////////////////////////////////// show tweets
        else if(choice=="5"){
            string for_send;
            for_send+=choice;

            int send1 = send(sock, for_send.c_str(), for_send.size() + 1, 0);
            if (send1 == -1){
                cout << "Could not send to server!\r\n";
                continue;
            }

            memset(buf, 0, 4096);
            int rec = recv(sock, buf, 4096, 0);
            if (rec == -1){
                cout << "There was an error getting response from server\r\n";
            }
            else{
                cout<<"tweets are: \n";
                cout << endl<< string(buf, rec) << "\r\n";
            }
        }

        ////////////////////////////////// show likes of a tweet
        else if(choice=="8"){
            string for_send,ID;
            cout<<"enter the tweet ID: ";
            cin>>ID;
            for_send+=choice+','+ID;

            int send1 = send(sock, for_send.c_str(), for_send.size() + 1, 0);
            if (send1 == -1){
                cout << "Could not send to server!\r\n";
                continue;
            }

            memset(buf, 0, 4096);
            int rec = recv(sock, buf, 4096, 0);
            if (rec == -1){
                cout << "There was an error getting response from server\r\n";
            }
            else{
                cout<<"users are: \n";
                cout << endl<< string(buf, rec) << "\r\n";
            }
        }
    }
    close(sock);

    return 0;
}