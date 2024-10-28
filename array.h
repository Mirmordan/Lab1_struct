#ifndef MYARRAY_H_
#define MYARRAY_H_
#include <string>
using namespace std;

class Array{
    public:
    Array(size_t start_size,string start_string);
    Array();

    void MPUSH(int index,string input);
    void MPUSH_BACK(string input);
    void MDEL (size_t index);
    string MGET(int index);
    size_t size();
    void PRINT();
    string& operator[](size_t index);
    void OPEN(string struct_filename);
    void CLOSE(string struct_filename);

    private:
    void RESIZE();
    void check_index(size_t index);

    size_t capacity; //Поля (вместимость, указатель на массив, число элементов)
    string *array;
    size_t _size;
};
#endif //MYARRAY_H_
