#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;

/* Класс узла дерева */
class Node
{
private:
    int id;
    int number;
    int count_sons;
    Node** sons;
public:
    Node();
    ~Node();
    int getId();
    int getNumber();
    int getCount_sons();
    Node** getSons();
    void setId(int ind);
    void setNumber(int number);
    void add_Son(Node* node);
    void print(int step = 0);   // Вывести дерево на экран
};

#endif // NODE_H
