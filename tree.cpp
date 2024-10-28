#include <iostream>
#include <math.h>
#include <functional>
#include <string>
#include "tree.h"
using namespace std;

Tree::Node::Node(){
        left=nullptr;
        right=nullptr;
        height=0;
}
Tree::Node::Node (int input){
    left=nullptr;
    right=nullptr;
    height=0;
    value=input;
}
Tree::Tree(){
    _size=0;
    _root=nullptr;
}

void Tree::TINSERT (int value){    //Вставляем рекурсивно от корня
    insert_recursion(_root,value);
    _size++;
}
bool Tree::TGET(int value){        //Поиск через цикл

        Node* search_pointer=_root;   //Идём от корня
        while(true){
        if (search_pointer->value==value) return true;  //Нашли элемент
        if (search_pointer->value>value){  //Сравнение с текущим элементом, выбор ветви
            if(search_pointer->left==nullptr) return false; //Идём налево, некуда - нет элемента
            search_pointer=search_pointer->left;
        }
        else{
            if(search_pointer->right==nullptr) return false; //Идём направо, некуда - нет элемента
            search_pointer=search_pointer->right;
        }
    }
}
void Tree::TDEL(int value){
        if(_size!=0)
        delete_recursion(_root,value);
}
void Tree::PRINT(){
    print_tree(_root,0,true);
}

void Tree::print_tree(Node* node,size_t deep=0, bool isRight = true) {
    if (node == nullptr) return;

    size_t int_deep=2;
    int number=node->value;
    while(number>9) {
        int_deep++;
        number/=10;
    }
    bool is_parent_right=node->right!=nullptr;
    bool is_parent_left=node->left!=nullptr;

    if(is_parent_right) 
        print_tree(node->right,deep+int_deep);
    
    for(size_t i=0;i<deep;i++) cout<<" ";
    if(isRight) 
        cout<<"╔";
    else 
        cout<<"╚";
    cout<<node->value;
    if(is_parent_right)
        if(is_parent_left)
            cout<<"╣";
        else
            cout<<"╝";
    else
        if(is_parent_left)
            cout<<"╗";
        else
            cout<<"╡";
    cout<<endl;

    if(is_parent_left) 
        print_tree(node->left,deep+int_deep,false);
}

void Tree::insert_recursion(Node *& node,int new_value){ //Рекурсивная вставка по предку
        if (node==nullptr){             //Свободно - запихиваем
            node=new Node(new_value);
            return;
        };
        if(node->value<new_value){    //Если не свободно, вызываем вставку от ветви
            insert_recursion(node->right,new_value);
        }
        else{
            insert_recursion(node->left,new_value);
        }
        check_balance(node); //После вставки в обратном порядке проверяем баланс
}

void Tree::delete_recursion(Node *&node,int value){ //Рекурсивное удаление
        if(node->value==value){
            Node* delete_node=node;
            size_t key=(node->right!=nullptr) + (node->left!=nullptr);
            switch(key){
                case 0:{
                    node=nullptr;
                    delete delete_node;
                    _size--;
                    break;
                }
                case 1:{
                    if(node->right!=nullptr)
                        node=node->right;
                    else
                        node=node->left;
                    delete delete_node;
                    _size--;
                    break;
                }
                case 2:{
                    function<void(Node*&)> find=[&](Node*&node_ptr){
                        if(node_ptr->right!=nullptr){
                            find(node_ptr->right);
                            check_balance(node_ptr);
                        }
                        else{
                            swap_values(node_ptr,delete_node);
                            delete_recursion(node_ptr,value);
                        }
                    };
                    find(node->left);
                }
            }
        }
        else{
            if(node->right!=nullptr) 
                delete_recursion(node->right,value);
            if(node->left!=nullptr) 
                delete_recursion(node->left,value);
            check_balance(node);
        }
}
void Tree::print_recursion(Node* print_node,ofstream &output){
    if(print_node->left!=nullptr)
        print_recursion(print_node->left,output);
    output<<(print_node->value);
    if(max_ptr()!=print_node)
        output<<endl;
    if(print_node->right!=nullptr) 
    print_recursion(print_node->right,output);
}

int Tree::get_height(Node * node){
    if(node==nullptr) 
        return -1;
    else 
        return node->height;
}
void Tree::check_height(Node* node){
    if(node==nullptr)
        return;
    node->height=max(get_height(node->right),get_height(node->left))+1;
}
int Tree::get_balance(Node *node){ //Проверка баланса (<0 перевес влево, >0 перевес вправо)
        return get_height(node->right)-get_height(node->left); 
}
void Tree::check_balance(Node* check_node){     //Проверка баланса и правка
        int balance=get_balance(check_node);
        if(balance*balance < 4) 
            check_height(check_node); //Если баланс впорядке, обновляем высоту
        else {
            if (balance<0){ //Если баланс страдает, то крутим влево или вправо
                if(get_balance(check_node->left)>0) 
                    L_ROTATE(check_node->left);
                R_ROTATE(check_node);
            }
            else{
                if(get_balance(check_node->right)<0)
                    R_ROTATE(check_node->right);
                L_ROTATE(check_node);
            }
            check_height(check_node);
        }
    }
void Tree::swap_values(Node* first,Node *second){
    int swap=first->value;
    first->value=second->value;
    second->value=swap;
}
void Tree::R_ROTATE (Node *rotate_node){
    Node *left_node=rotate_node->left;
    swap_values(rotate_node,left_node);
    rotate_node->left=left_node->left;
    left_node->left=left_node->right;
    left_node->right=rotate_node->right;
    rotate_node->right=left_node;

    check_balance(left_node);
    check_balance(rotate_node);
}
void Tree::L_ROTATE (Node *rotate_node){
    Node *right_node=rotate_node->right;
    swap_values(rotate_node,right_node);
    rotate_node->right=right_node->right;
    right_node->right=right_node->left;
    right_node->left=rotate_node->left;
    rotate_node->left=right_node;

    check_balance(right_node);
    check_balance(rotate_node);
}

void Tree::OPEN(std::string struct_filename){
    ifstream struct_file(struct_filename);
    string input;
    while (getline(struct_file,input,'\n'))
        TINSERT(stoi(input));
    struct_file.close();
}

void Tree::CLOSE(std::string struct_filename){
    ofstream struct_file(struct_filename);
    if(_size>0)
        print_recursion(_root,struct_file);
    struct_file.close();
}
Tree::Node* Tree::max_ptr(){
    Node* result=_root;
    while(result->right!=nullptr)
        result=result->right;
    return result;
}
