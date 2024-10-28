#include "array.h"
#include <exception>
#include <string>
#include <iostream>
#include <fstream> 
using namespace std;

Array::Array(size_t start_size=0,string start_string="lol"){ //Инициализатор
        _size=start_size;
        if(start_size<8) capacity=16;
        else capacity=start_size*1.5;
        array=new string[capacity];
        for(auto i=0;i<_size;i++){
            array[i]=start_string;
        }
}
Array::Array(){
    _size=0;
    capacity=16;
    array=new string[capacity];
}

size_t Array::size(){ //Функция, выводящая размер
        return _size;
}
    
void Array::MPUSH(int index,string input){ //Добавление по индексу со сдвигом
    if(_size==capacity)RESIZE();
    check_index(index);
    _size++;
    for(auto i=_size-1;i>index;i--){
         array[i]=array[i-1];
    }
    array[index]=input;
}

void Array::MPUSH_BACK(string input){ //Добавление в конец
    if(_size==capacity)RESIZE();
    array[_size]=input;
    _size++;
}

void Array::MDEL (size_t index){  //Удаление по индексу сдвигом
    check_index(index);
    _size--;
    for(auto i=index;i<_size;i++){
        array[i]=array[i+1];
    }
}

string Array::MGET(int index){ //Получение по индексу
    check_index(index);
    return array[index];
}

void Array::PRINT(){ //Вывод массива
    for(auto i=0;i<_size;i++) cout<<array[i]<<" ";
    cout<<endl;
}

string& Array::operator[](size_t index){ //Доступ оп индексу
    return array[index];
}

void Array::RESIZE(){ // Метод реаллокации с увеличением размера
    capacity*=1.5;
    string *new_array=new string[capacity];
    for(auto i=0;i<_size;i++){
            new_array[i]=array[i];
    }
    delete[] array;
    array=new_array;
}

void Array::check_index(size_t index){ //Проверка индекса
    if (index<0 or index>_size-1){
        throw logic_error("List out of range");
    }
}

void Array::OPEN(string struct_filename){
    ifstream array_file(struct_filename);
    string input;
    while (getline(array_file,input,'\n'))
        MPUSH_BACK(input);
    array_file.close();
}

void Array::CLOSE(string struct_filename){   
    ofstream array_file(struct_filename);
    for(int i=0;i<_size;i++){
        array_file<<array[i];
        if(i<_size-1)
            array_file<<endl;
    }
    
}