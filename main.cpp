#include <iostream>
#include <fstream>
#include "node.h"
#include "myvector.h"

using namespace std;

void usage()
{
    cout << "Lab3 [path]" << endl << endl;
    cout << "path - Файл N-дерева" << endl;
    cout << endl << "Error: Not enough arguments" << endl;
}

Node* newNode(int** array, int nodeID)  // Перенос информации из массива в объект
{
    Node* node = new Node;
    int* int_node = array[nodeID];
    node->setId(nodeID);
    int len = int_node[0];
    node->setNumber(int_node[1]);
    for (int i = 2; i < len; i++){
        int soneId = int_node[i];
        Node* son = newNode(array, soneId);
        node->add_Son(son);
    }
    return node;
}

int searchRoot(int** array, int size, int rootId = 0)
{
    for (int i = 0; i < size; i++){                           // Проходимся по таблице
        int len = array[i][0];
        for (int j = 2; j < len; j++){
            if (array[i][j] == rootId)
                return searchRoot(array, size, i);
        }
    }
    return rootId;
}

Node* inFile(fstream& file)
{
    int size;
    int len;
    if (!(file >> size)) throw;
    int** array = new int* [size];                 // Переносим таблицу из файла в массив
    for (int i = 0; i < size; i++){
        if (!(file >> len)) throw;
        array[i] = new int [len];
        array[i][0] = len;
        for (int j = 1; j < len; j++){
            if(!(file >> array[i][j])) throw;
        }
    }
    Node* root = newNode(array, searchRoot(array, size));  // Создаём объект дерева
    delete [] array;
    return root;                                   // И возвращаем ссылку на корень
}

void del(Node* node, MyVector dels){
    Node** sons = node->getSons();
    for (int i = 0; i < node->getCount_sons(); i++){
        Node* son = sons[i];
        for (int j = 0; j < dels.get_size(); j++){
            int id = dels.get_element(j)->getId();
            if (son->getId() == id){
                node->remove_Son(id);
                dels.erase(id);
                break;
            }
        }
        del(son, dels);
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2){
        usage();
        return -1;
    }
    fstream file(argv[1], ios::in);
    if (!file){
        cout << "File open error" << endl;
        return -2;
    }
    Node* tree = inFile(file);       // Считываем дерево из файла
    file.close();
    tree->print();                   // Выведем для проверки
    cout << "sd\n" ;

    cout << "\n"<< flush << endl << endl;
    MyVector strm;
    strm.push_back(tree);
    int i = 0;
    int count = strm.get_size();
    bool flag = false;
    MyVector del_ids;
    while (i < strm.get_size()){
        if (flag and i == count) {
            break;
        }
        Node* node = strm.get_element(i);
        if (node->getCount_sons() == 0){
            flag = true;
            del_ids.push_back(node);
        }
        Node** sons = node->getSons();
        for (int j = 0; j < node->getCount_sons(); j++){
            strm.push_back(sons[j]);
        }
        i++;
    }
    del(tree, del_ids);
    tree->print();
    cout << endl << endl;
    return 0;
}
