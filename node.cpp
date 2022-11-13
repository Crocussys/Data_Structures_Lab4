#include "node.h"

Node::Node()
{
    id = -1;
    number = 0;
    count_sons = 0;
    sons = nullptr;
}
int Node::getId()
{
    return id;
}
int Node::getNumber()
{
    return number;
}
int Node::getCount_sons(){
    return count_sons;
}
Node** Node::getSons(){
    return sons;
}
void Node::setId(int ind)
{
    id = ind;
}
void Node::setNumber(int n)
{
    number = n;
}
void Node::add_Son(Node* node){
    Node** temp = new Node* [count_sons];
    for (int i = 0; i < count_sons; i++){
        temp[i] = sons[i];
    }
    delete [] sons;
    count_sons++;
    sons = new Node* [count_sons];
    for (int i = 0; i < count_sons - 1; i++){
        sons[i] = temp[i];
    }
    sons[count_sons - 1] = node;
    delete [] temp;
}
bool Node::remove_Son(int id){
    for (int i = 0; i < count_sons; i++){
        if (sons[i]->getId() == id){
            Node** temp = new Node* [count_sons];
            for (int j = 0; j < count_sons; j++){
                temp[j] = sons[j];
            }
            delete [] sons;
            count_sons--;
            sons = new Node* [count_sons];
            bool flag = false;
            for (int j = 0; j < count_sons + 1; j++){
                if (temp[j]->getId() == id){
                    flag = true;
                    continue;
                }
                if (flag){
                    sons[j - 1] = temp[j];
                }else{
                    sons[j] = temp[j];
                }
            }
            delete [] temp;
            return true;
        }
    }
    return false;
}
void Node::print(int step)
{
    if (id == -1)
        return;
    int new_step = step + 4;  // Вычисляем отступ
    float n = number;
    while (n >= 1){
        new_step++;
        n /= 10;
    }
    bool flag = false;
    cout << number;
    for (int i = 0; i < count_sons; i++){
        if (flag){
            cout << endl;
            for (int i = 0; i < step; i++){
                cout << " ";
            }
            cout << number;
        }
        cout << " -> ";
        sons[i]->print(new_step);
        flag = true;
    }
}
