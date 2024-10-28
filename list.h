#ifndef MYLIST_H_
#define MYLIST_H_
#include <string>
class List{
    struct Node {
        Node *next;
        Node *previous;
        int value;
        Node();
        Node(int value);
    };

    public:
    List ();

    public:
    void LPUSH(int value);
    void LPUSH_BACK(int value);
    void PRINT();
    void LPOP();
    void LPOP_BACK();
    void LDEL(int delete_value);
    int LGET(int get_value);
    void OPEN(std::string struct_filename);
    void CLOSE(std::string struct_filename);
    
    private:
    void POP(Node *node_deleted);

    private:
    size_t _size;
    Node head,tail;
};
#endif //MYLIST_H_
