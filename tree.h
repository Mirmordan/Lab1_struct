#ifndef MYTREE_H_
#define MYTREE_H_
#include <iostream>
#include <fstream>
using namespace std;

class Tree{
    struct Node {
        Node *left;
        Node *right;
        int height;
        int value;
        Node ();
        Node (int input);
    };
    public:
    Tree();
    
    void TINSERT (int value);
    void TDEL(int value);
    bool TGET(int value);
    void PRINT();
    void OPEN(std::string struct_filename);
    void CLOSE(std::string struct_filename);

    private:
    void insert_recursion(Node *& node,int new_value);
    void delete_recursion(Node *&node,int value);
    void print_recursion(Node* print_node,ofstream &output);
    void print_tree(Node* node,size_t deep, bool isRight);

    int get_height(Node* node);        //Балансировка
    void check_height(Node* check_node);
    int get_balance(Node* node);
    void check_balance(Node* check_node);
    void swap_values(Node* first,Node *second);
    void R_ROTATE (Node *rotate_node);
    void L_ROTATE (Node *rotate_node);

    private:
    size_t _size;
    Node* _root;
    Node * max_ptr();
};
#endif //MYTREE_H_