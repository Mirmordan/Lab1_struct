#include "list.h"
#include <fstream>
#include <iostream>
using namespace std;

List::Node::Node(){
    next=nullptr;
    previous=nullptr;
};

List::Node::Node(int input){
    next=nullptr;
    previous=nullptr;
    value = input;
};

List::List(){
    _size=0;
    head.next=&tail;
    tail.previous=&head;
};

void List::LPUSH(int value){      //Добавление в голову
    Node* new_node = new Node(value); //Новая нода
        
    new_node->next=head.next;   //Переподвешиваем ноду после головы к новой
    head.next->previous=new_node;
        
    new_node->previous=&head;  //Переподвешиваем голову к новой ноде
    head.next = new_node;
        
    _size++;
};
    
void List::LPUSH_BACK(int value){      //Добавление в хвост
    Node* new_node = new Node(value); //Новая нода
        
    new_node->previous=tail.previous;   //Переподвешиваем ноду перед хвостом к новой
    tail.previous->next=new_node;
        
    new_node->next=&tail;  //Переподвешиваем хвост к новой ноде
    tail.previous = new_node;
        
    _size++;
};
    
void List::PRINT(){   //Вывод списка
        Node *out_node=head.next;
        while (out_node!=&tail){
            cout<<out_node->value<<" ";
            out_node=out_node->next;
        }
        cout<<endl;
};
    
void List::POP(Node *node_deleted){ //Удаление элемента по указателю
        node_deleted->previous->next=node_deleted->next;
        node_deleted->next->previous=node_deleted->previous;
        delete node_deleted;
        _size--;
};
    
void List::LPOP(){      //Удаление первого с головы
    if (_size=0) 
        return;
    POP(head.next);
};
    
void List::LPOP_BACK(){ //Удаление первого с хвоста
    if (_size=0) 
        return;
    POP(tail.previous);
};
    
void List::LDEL(int delete_value){   //Удаление по значению
    Node *search_pointer=head.next; 
        
    while(search_pointer!=&tail){  //Пробегаемся указателем по списку
        if (search_pointer->value==delete_value){ //Находим значение - вырезаем по указателю
            POP(search_pointer);
            return;
        }
        search_pointer=search_pointer->next;
    }
};
    
int List::LGET(int get_value){ //Возвращает номер элемента по значению (-1 если такого нет)
    Node *search_pointer=head.next;
    int index=0;
        
    while(search_pointer!=&tail){  //Пробегаемся указателем по списку
        if (search_pointer->value==get_value){ 
            return index;
        }
        search_pointer=search_pointer->next;
        index++;
    }
    return -1;
};

void List::OPEN(std::string struct_filename){
    ifstream struct_file(struct_filename);
    string input;
    while (getline(struct_file,input,'\n'))
        LPUSH_BACK(stoi(input));
    struct_file.close();
}

void List::CLOSE(std::string struct_filename){
    ofstream struct_file(struct_filename);
    Node* out_node=head.next;
        while (out_node!=&tail){
            struct_file<<out_node->value;
            out_node=out_node->next;
            if(out_node!=&tail)
                struct_file<<endl;
        }
    struct_file.close();
}


