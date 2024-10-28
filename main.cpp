#include "array.h"
#include "list.h"
#include "olist.h"
#include "queue.h"
#include "stack.h"
#include "tree.h"
#include "hash.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

using namespace std;

class Parser{
    string request;
    string base_filename;
    public:
    Parser(int argc,char* argv[]);
    void parse();
    string get_struct(string base_filename,string struct_filename);
};

int main(int argc, char *argv[]){
    Parser parser(argc,argv);
    parser.parse();
}

Parser::Parser(int argc,char* argv[]){
    string unit;
    base_filename=="file.data";
    for(int i=1;i<argc;i++){
        unit=argv[i];
        if(unit.substr(0,6)=="--file"){
            base_filename=argv[i+1];
            i++;
            continue;
        }
        if(unit=="--query"){
            request=argv[i+1];
            i++;
            continue;
        }
        i++;
    }
};

string Parser::get_struct(string base_filename,string struct_filename){
    string input,unit;
    ifstream base_file(base_filename);
    while(getline(base_file,input)){
        stringstream input_stream(input);
        input_stream>>unit;
        if(unit==struct_filename){
            input_stream>>unit;
            base_file.close();
            return unit;
        }
    }
    throw logic_error("Can't found struct file.");
    base_file.close();
    return "array";
}

void Parser::parse(){
    stringstream request_string(request);
    string command, struct_filename,key,value;
    int index;
    request_string>>command;
    request_string>>struct_filename;
    string struct_type=get_struct(base_filename,struct_filename);
    if (struct_type=="array"){
        Array myarray;
        myarray.OPEN(struct_filename);
        if(command=="MPUSH"){
            request_string>>index;
            request_string>>value;
            myarray.MPUSH(index,value);
        }
        if(command=="MPUSH_BACK"){
            request_string>>value;
            myarray.MPUSH_BACK(value);
        }
        if(command=="MDEL"){
            request_string>>index;
            myarray.MDEL(index);
        }
        if(command=="MSET"){
            request_string>>index;
            request_string>>value;
            myarray[index]=value;
        }
        if(command=="MGET"){
            request_string>>index;
            cout<<myarray.MGET(index)<<endl;
        }
        if(command=="MSIZE")
            cout<<myarray.size()<<endl;
        if(command=="PRINT")
            myarray.PRINT();
        myarray.CLOSE(struct_filename);
    }
    if (struct_type=="list"){
        List mylist;
        mylist.OPEN(struct_filename);
        if(command=="LPUSH"){
            request_string>>index;
            mylist.LPUSH(index);
        }
        if(command=="LPUSH_BACK"){
            request_string>>index;
            mylist.LPUSH_BACK(index);
        }
        if(command=="PRINT")
            mylist.PRINT();
        if(command=="LPOP")
            mylist.LPOP();
        if(command=="LPOP_BACK")
            mylist.LPOP_BACK();
        if(command=="LDEL"){
            request_string>>index;
            mylist.LDEL(index);
        }
        if(command=="LGET"){
            request_string>>index;
            mylist.LGET(index);
        }
        mylist.CLOSE(struct_filename);
    }
    if (struct_type=="olist"){
        OWList myolist;
        myolist.OPEN(struct_filename);
        if(command=="LPUSH"){
            request_string>>index;
            myolist.LPUSH(index);
        }
        if(command=="LPUSH_BACK"){
            request_string>>index;
            myolist.LPUSH_BACK(index);
        }
        if(command=="PRINT")
            myolist.PRINT();
        if(command=="LPOP")
            myolist.LPOP();
        if(command=="LPOP_BACK")
            myolist.LPOP_BACK();
        if(command=="LDEL"){
            request_string>>index;
            myolist.LDEL(index);
        }
        if(command=="LGET"){
            request_string>>index;
            myolist.LGET(index);
        }
        myolist.CLOSE(struct_filename);
    }
    if (struct_type=="queue"){
        Queue myqueue;
        myqueue.OPEN(struct_filename);
        if(command=="QPUSH"){
            request_string>>value;
            myqueue.QPUSH(value);
        }
        if(command=="QPOP")
            myqueue.QPOP();
        if(command=="PRINT")
            myqueue.PRINT();
        myqueue.CLOSE(struct_filename);
    }
    if (struct_type=="stack"){
        Stack mystack;
        mystack.OPEN(struct_filename);
        if(command=="SPUSH"){
            request_string>>value;
            mystack.SPUSH(value);
        }
        if(command=="SPOP")
            mystack.SPOP();
        if(command=="PRINT")
            mystack.PRINT();
        mystack.CLOSE(struct_filename);
    }
    if (struct_type=="tree"){
        Tree mytree;
        mytree.OPEN(struct_filename);
        if(command=="TINSERT"){
            request_string>>index;
            mytree.TINSERT(index);
        }
        if(command=="TDEL"){
            request_string>>index;
            mytree.TDEL(index);
        }
        if(command=="TGET"){
            request_string>>index;
            mytree.TGET(index);
        }
        if(command=="PRINT")
            mytree.PRINT();
        mytree.CLOSE(struct_filename);
    }
    if (struct_type=="hash"){
        Hash myhash;
        myhash.OPEN(struct_filename);
        if(command=="HSET"){
            request_string>>key;
            request_string>>value;
            myhash.HSET(key,value);
        }
        if(command=="HDEL"){
            request_string>>key;
            myhash.HDEL(key);
        }
        if(command=="HGET"){
            request_string>>key;
            cout<<myhash.HGET(key)<<endl;
        }
        if(command=="SIZE"){
            cout<<myhash.size()<<endl;
        }
        if(command=="PRINT")
            myhash.PRINT();
        myhash.CLOSE(struct_filename);
    }
}
