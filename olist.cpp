#include "olist.h"
#include <fstream>
#include <iostream>
using namespace std;

OWList::Node::Node(){
    next=nullptr;
};

OWList::Node::Node(int input){
    next=nullptr;
    value = input;
};

OWList::OWList(){
    _size=0;
    head=nullptr;
};

void OWList::LPUSH(int value){      //Добавление в голову
    Node* new_node = new Node(value); //Новая нода

    new_node->next=head;   //Переподвешиваем ноду после головы к новой
    head = new_node;

    _size++;
};
    
void OWList::LPUSH_BACK(int value){      //Добавление в хвост
    Node* new_node = new Node(value); //Новая нода
    Node** insert_pointer=&head;
    while((*insert_pointer)!=nullptr){
        insert_pointer=&((*insert_pointer)->next);
    }
    *insert_pointer=new_node;

    _size++;
};
    
void OWList::PRINT(){   //Вывод списка
        Node *out_node=head;
        while (out_node!=nullptr){
            cout<<out_node->value<<" ";
            out_node=out_node->next;
        }
        cout<<endl;
};
    
void OWList::LPOP(){ //Удаление элемента по указателю
    if(_size==0) 
        return;
    POP(head);
    _size--;
};

void OWList::LPOP_BACK(){ //Удаление элемента по указателю
    if(_size==0)
        return;
    Node** delete_pointer=&head;
    while(((*delete_pointer)->next)!=nullptr){
        delete_pointer=&((*delete_pointer)->next);
    }
    POP(*delete_pointer);
    _size--;
};
int OWList::LDEL(int delete_value){
    if(_size==0)
        return -1;
    Node** delete_pointer=&head;
    while(((*delete_pointer)->next)!=nullptr and (*delete_pointer)->value!=delete_value){
        delete_pointer=&((*delete_pointer)->next);
    }
    if((*delete_pointer)->value==delete_value){
        POP(*delete_pointer);
        _size--;
        return 1;
    }
    else
        return -1;
}
int OWList::LGET(int get_value){
    Node* search_pointer = head;
    int index=0;
    while(search_pointer!=nullptr and search_pointer->value!=get_value){
        search_pointer=search_pointer->next;
        index++;
    }
    if(search_pointer->value==get_value){
        return index;
    }
    else
        return -1;
}

void OWList::POP(Node *&node){ //Удаление элемента по указателю
    Node *node_deleted=node;
    node=node->next;
    delete node_deleted;
    _size--;
};
    


void OWList::OPEN(std::string struct_filename){
    ifstream struct_file(struct_filename);
    string input;
    while (getline(struct_file,input,'\n'))
        LPUSH_BACK(stoi(input));
    struct_file.close();
}

void OWList::CLOSE(std::string struct_filename){
    ofstream struct_file(struct_filename);
    Node* out_node=head;
        while (out_node!=nullptr){
            struct_file<<out_node->value;
            out_node=out_node->next;
            if(out_node!=nullptr)
                struct_file<<endl;
        }
    struct_file.close();
}


