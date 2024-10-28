#ifndef MY_HASH_H_
#define MY_HASH_H_

#include <iostream>
using namespace std;

class Hash{
    struct Node{
        string _key;
        string _value;
        Node* _next_node;
        Node();
    };
    public:
    Hash();

    void HSET (string key,string value);
    int HDEL (string key);
    string HGET(string key);
    size_t size();
    void PRINT();
    void OPEN(std::string struct_filename);
    void CLOSE(std::string struct_filename);
    
    private:
    void REHASH();
    size_t Hash_Function(string key);
    size_t _bucket_ammount;
    size_t _size;
    Node ** _buckets;
};
#endif //MY_HASH_H_