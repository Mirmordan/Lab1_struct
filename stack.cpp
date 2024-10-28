#include "stack.h"
#include <iostream>
#include <fstream>
using namespace std;
Stack::Node::Node(){
    next=nullptr;
};

Stack::Node::Node(std::string start_value){ //Инициализатор подкласса
    value=start_value;
    next=nullptr;
};

Stack::Stack(){  //Инициализатор класса
    _size=0;
    _head=nullptr;
};
    
void Stack::SPUSH(std::string value){      //Добавление в голову
    Node* new_node = new Node(value); //Новая нода
        
    new_node->next=_head;   //Переподвешиваем голову
    _head=new_node;
        
    _size++;
};
    
void Stack::PRINT(){   //Вывод стека
    Node *out_node=_head;
    while (out_node!=nullptr){
        std::cout<<out_node->value<<" ";
        out_node=out_node->next;
    }
    std::cout<<std::endl;
};
    
void Stack::SPOP(){      //Удаление первого с головы
    if (_size==0) return;

    Node *delete_node=_head;
    _head=delete_node->next;
    delete delete_node;
    _size--;
};

void Stack::OPEN(std::string struct_filename){
    ifstream struct_file(struct_filename);
    string input;
    while (getline(struct_file,input,'\n'))
        SPUSH(input);
    struct_file.close();
}

void Stack::CLOSE(std::string struct_filename){
    ofstream struct_file(struct_filename);
    Node* out_node=_head;
    while (out_node!=nullptr){
        struct_file<<out_node->value;
        out_node=out_node->next;
        if(out_node!=nullptr)
            struct_file<<endl;
    }
    struct_file.close();
}