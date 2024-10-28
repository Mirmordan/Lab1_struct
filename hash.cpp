#include <iostream>
#include <fstream>
#include <sstream>
#include "hash.h"
using namespace std;

Hash::Node::Node(){
    _next_node=nullptr;
}

Hash::Hash(){
    _bucket_ammount=5;
    _size=0;
    _buckets=new Node*[_bucket_ammount];
    for(int i=0;i<_bucket_ammount;i++){
        _buckets[i]=new Node;
    }
}

void Hash::HSET (string key,string value){
    Node *set_node=_buckets[Hash_Function(key)];
    while(set_node->_next_node!=nullptr and set_node->_key!=key) 
        set_node=set_node->_next_node;
    set_node->_key=key;
    set_node->_value=value;
    if(set_node->_next_node==nullptr)
        set_node->_next_node=new Node;
}

int Hash::HDEL (string key){
    Node **search_node=&_buckets[Hash_Function(key)]; 
    while((*search_node)->_next_node!=nullptr and (*search_node)->_key!=key){
        search_node=&((*search_node)->_next_node);
    }
    if((*search_node)->_next_node!=nullptr){
        Node *delete_node=*search_node;
        *search_node=delete_node->_next_node;
        delete delete_node;
        return 1;
    }
    return -1;
    PRINT();
}
    
string Hash::HGET(string key){
    Node* get_node=_buckets[Hash_Function(key)];
    while(get_node->_next_node!=nullptr and get_node->_key!=key ) 
        get_node=get_node->_next_node;
    if (get_node->_key==key) 
        return get_node->_value;
    else
        return "-1";
}

size_t Hash::size(){
    return _size;
}

void Hash::PRINT(){
    for(size_t i=0;i<_bucket_ammount;i++){
        Node *print_node=_buckets[i];
        while (print_node->_next_node!=nullptr){
            cout<<print_node->_key<<" "<<print_node->_value<<endl;
            print_node=print_node->_next_node;
        }
    }
}

size_t Hash::Hash_Function(string key){
    size_t index=0;
    for(size_t i:key){
        index+=i;
        index%=_bucket_ammount;
    }
    return index%_bucket_ammount;
}

void Hash::OPEN(string struct_filename){
    ifstream struct_file(struct_filename);
    string key,value,input;
    while (getline(struct_file,input,'\n')){
        stringstream line(input);
        getline(line,key,':');
        getline(line,value);
        HSET(key,value);
    }
    struct_file.close();
}

void Hash::CLOSE(string struct_filename){
    ofstream struct_file(struct_filename);
    for(size_t i=0;i<_bucket_ammount;i++){
        Node *print_node=_buckets[i];
        while (print_node->_next_node!=nullptr){
            struct_file<<print_node->_key<<":"<<print_node->_value<<endl;
            print_node=print_node->_next_node;
            if(print_node->_next_node!=nullptr)
                struct_file<<endl;
        }
    }
}
    