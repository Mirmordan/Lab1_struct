#ifndef OW_LIST_H_
#define OW_LIST_H_
#include <string>
#include <iostream>
class OWList{
    struct Node {
        Node *next;
        int value;
        Node();
        Node(int value);
    };

    public:
    OWList ();

    public:
    void LPUSH(int value);
    void LPUSH_BACK(int value);
    void PRINT();
    void LPOP();
    void LPOP_BACK();
    int LDEL(int delete_value);
    int LGET(int get_value);
    void OPEN(std::string struct_filename);
    void CLOSE(std::string struct_filename);
    
    private:
    void POP(Node *&node_deleted);

    private:
    size_t _size;
    Node* head;
};
#endif //OW_LIST_H_
