#ifndef MYSTACK_H_
#define MYSTACK_H_
#include <string>

class Stack{
    struct Node {
        Node *next;
        std::string value;
        Node();
        Node(std::string start_value);
    };
    
    public:
    Stack ();
    
    void SPUSH(std::string value);
    void SPOP();
    void PRINT();
    void OPEN(std::string struct_filename);
    void CLOSE(std::string struct_filename);

    private:
    size_t _size;
    Node* _head;
};

#endif //MYSTACK_H_
