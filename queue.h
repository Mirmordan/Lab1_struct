#ifndef MYQUEUE_H_
#define MYQUEUE_H_
#include <string>

class Queue{
    struct Node {
        Node *next;
        std::string value;
        Node();
        Node(std::string start_value);
    };
    
    public:
    Queue ();
    
    void QPUSH(std::string value);
    void PRINT();
    void QPOP();
    void OPEN(std::string struct_filename);
    void CLOSE(std::string struct_filename);

    private:
    size_t _size;
    Node _head;
    Node* _tail;
};

#endif //MYQUEUE_H_
