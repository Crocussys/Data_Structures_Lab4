#include <iostream>
#include <fstream>
#include "node.h"

using namespace std;

void usage()
{
    cout << "Lab3 [path]" << endl << endl;
    cout << "path - Файл N-дерева" << endl;
    cout << endl << "Error: Not enough arguments" << endl;
}

Node* newNode(int** array, int nodeID, int lvl = 0)  // Перенос информации из массива в объект
{
    Node* node = new Node;
    int* int_node = array[nodeID];
    node->setId(nodeID);
    node->selLevel(lvl);
    int len = int_node[0];
    node->setNumber(int_node[1]);
    for (int i = 2; i < len; i++){
        int soneId = int_node[i];
        Node* son = newNode(array, soneId, lvl + 1);
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

int search(Node* node, int lvl = 0, int min = -1){
    int count = node->getCount_sons();
    if (count == 0){
        return lvl;
    }else{
        Node** sons = node->getSons();
        for (int i = 0; i < count; i++){
            son_lvl                                       // Чё я делаю...
        }
        if (min == -1){
            return lvl;
        }else{
            if (min > lvl){
                return lvl;
            }else{
                return min;
            }
        }
    }
}

//MyVector search(Node node)
//{
//    Node* left_node = node.getLeft();
//    Node* right_node = node.getRight();
//    MyVector left_path = MyVector();
//    MyVector right_path = MyVector();
//    MyVector ans = MyVector();
//    if (node.getNumber() % 2 == 0){        // Проверка на нечётность по заданию
//        return ans;
//    }
//    if (left_node != nullptr){             // Рекурсивный поиск вглубь слева
//        left_path = search(*left_node);
//    }
//    if (right_node != nullptr){            // и справа
//        right_path = search(*right_node);
//    }
//    if (left_path.get_size() >= right_path.get_size()){  // Выбираем длинный путь
//        ans = left_path;
//    }else{
//        ans = right_path;
//    }
//    ans.push_back(node);  // Добавляем себя
//    return ans;           // Передаём этот путь вверх по дереву
//}

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
    cout << endl << endl;
//    MyVector path = search(*tree);   // Ищем нужный путь
//    cout << "root";                  // Далее вывод результатов на экран
//    int len = path.get_size() - 1;
//    for (int i = len; i >= 0; i--){
//        cout << " -> " << path.get_element(i).getNumber();
//    }
//    cout << endl << "Длина максимального пути: " << len << endl;
    return 0;
}
