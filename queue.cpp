#include "queue.h"
#include <iostream>
#include <fstream>
using namespace std;
Queue::Node::Node(){
    next=nullptr;
};

Queue::Node::Node(std::string start_value){ //Инициализатор подкласса
    value=start_value;
    next=nullptr;
};

Queue::Queue(){  //Инициализатор класса
    _size=0;
    _tail=&_head;
};
    
void Queue::QPUSH(std::string value){      //Добавление в хвост
    Node* new_node = new Node(value); //Новая нода
    _tail->next=new_node;
    _tail=new_node;
    _size++;
};

void Queue::QPOP(){      //Удаление первого с головы
    if (_size==0) return;
    Node *delete_node=_head.next;
    _head.next=delete_node->next;
    delete delete_node;
    _size--;
};

void Queue::PRINT(){   //Вывод стека
    Node *out_node=_head.next;
    while (out_node!=nullptr){
        cout<<out_node->value<<" ";
        out_node=out_node->next;
    }
    cout<<endl;
};

void Queue::OPEN(std::string struct_filename){
    ifstream queue_file(struct_filename);
    string input;
    while (getline(queue_file,input,'\n'))
        QPUSH(input);
    queue_file.close();
}
void Queue::CLOSE(std::string struct_filename){
    ofstream queue_file(struct_filename);
    Node* out_node=_head.next;
    while (out_node!=nullptr){
        queue_file<<out_node->value;
        out_node=out_node->next;
        if(out_node!=nullptr)
            queue_file<<endl;
    }
    queue_file.close();
}