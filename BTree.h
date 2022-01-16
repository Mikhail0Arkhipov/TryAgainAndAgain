#pragma once
#include <initializer_list>
#include <vector>

/**
    класс B дерева
*/
class BTree 
{
    struct Node {
        int* keys;  //массив ключей
        int t;     //минимальная степень (определяет диапазон ключей)
        Node** C; //массив дочерних элементов
        int n;    //кол-во ключей
        bool leaf; //true - является листом, false - не является листом
        Node(int t, bool leaf);
        int findKey(const int key);
        void remove(const int key);
        void removeFromLeaf(const int idx);
        void removeFromNonLeaf(const int idx);
        int getPrev(const int idx);
        int getSucc(const int idx);
        void fill(const int idx);
        void stealFromPrev(const int idx);
        void stealFromNext(const int idx);
        void merge(int idx);
        void insertNonFull(int k);
        void splitChild(int i, Node* y);
        void traverse();
        void traverse(std::vector<int>& key);
        void clear();
        Node* search(int k);
    };
    Node* root;
    int t;

public:
    /**
    * \brief Конструктор
    */
    BTree(int t);
    /**
    * \brief Деструктор
    */
    ~BTree();
    /**
    * \brief Обход дерева
    */
    void traverse();
    /**
    * \brief Обход дерева с получением каждого числа в виде вектора
    */
    void traverse(std::vector<int>& key);
    /**
    * \brief вставка нового элемента в дерево
    * \param k Целое число
    */
    void insert(int k);
    /**
    * \brief Удаление ключа
    * \param k Целое число
    */
    void remove(int k);
    /**
    * \brief Редактирование ключа
    * \param oldkey Целое число
    * \param newkey Целое число
    */
    void edit(int oldkey, int newkey);
    /**
    * \brief Очистка всего дерева
    */
    void clear();
    /**
    * \brief Поиск в дереве
    */
    Node* search(int k);
};