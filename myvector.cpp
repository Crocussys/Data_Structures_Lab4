#include "myvector.h"

MyVector::MyVector()
{
    size = 0;
    array = nullptr;
}
void MyVector::push_back(Node* node)
{
    Node* new_array[size+1];          // Создаём временный массив
    for (int i = 0; i < size; i++){
        new_array[i] = array[i];     // Переносим всё туда
    }
    new_array[size] = node;          // Добавляем вставляемый элемент
    size++;
    array = new Node* [size];           // Переопределяем массив с новым размером
    for (int i = 0; i < size; i++){
        array[i] = new_array[i];     // Возвращаем всё обратно
    }
}
bool MyVector::erase(int id){
    for (int i = 0; i < size; i++){
        if (array[i]->getId() == id){
            Node** temp = new Node* [size];
            for (int j = 0; j < size; j++){
                temp[j] = array[j];
            }
            delete [] array;
            size--;
            array = new Node* [size];
            bool flag = false;
            for (int j = 0; j < size + 1; j++){
                if (temp[j]->getId() == id){
                    flag = true;
                    continue;
                }
                if (flag){
                    array[j] = temp[j - 1];
                }else{
                    array[j] = temp[j];
                }
            }
            delete [] temp;
            return true;
        }
    }
    return false;
}
Node* MyVector::get_element(int i)
{
    if (i >= 0 and i < size){  // Проверка
        return array[i];
    }else{
        throw;
    }
}
int MyVector::get_size()
{
    return size;
}
