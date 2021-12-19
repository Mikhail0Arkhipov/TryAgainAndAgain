/**
    класс B дерева
*/
class BTree {
    //узел дерева
    struct Node {
        int* keys;  //массив ключей
        int t;     //минимальная степень (определяет диапазон ключей)
        Node** C; //массив дочерних элементов
        int n;    //кол-во ключей
        bool leaf; //true - лист, false - не лист

        /**
            конструктор
        */
        Node(int t, bool leaf) {

        }

        /**
            индекс ключа, который больше либо равен k
        */
        int findKey(int k) {

        }

        /**
            обертка для удаления ключа
        */
        void remove(int k) {

        }

        /**
            удаление из листа
        */
        void removeFromLeaf(int idx) {

        }

        /**
            удаление не из листа
        */
        void removeFromNonLeaf(int idx) {

        }

        /**
            получение предшественника
        */
        int getPrev(int idx) {

        }

        /**
            получение преемника
        */
        int getSucc(int idx) {

        }

        /**
            заполнение узла idx у которого меньше t-1 ключей
        */
        void fill(int idx) {

        }

        /**
            берем ключ из C[idx-1] помещаем в C[idx]
        */
        void stealFromPrev(int idx) {

        }

        /**
            берем у C[idx+1]
        */
        void stealFromNext(int idx) {

        }

        /**
            слияние C[idx] с C[idx+1]
        */
        void merge(int idx) {

        }

        /**
            вставка в незаполненный узел
        */
        void insertNonFull(int k) {

        }

        /**
            для разделения дочернего узла
        */
        void splitChild(int i, Node* y) {

        }

        /**
            обход всех поддеревьев
        */
        void traverse() {

        }

        /**
            обход всех поддеревьев с их сохранением в vector
        */
        void traverse(vector<int>& key) {

        }

        /**
            очистка всего дерева
        */
        void clear() {

        }

        /**
            поиск ключа в дереве
        */
        Node* search(int k) {

        }
    };

    Node* root; //корень дерева
    int t;  //минимальная степень

public:
    /**
        конструктор
    */
    BTree(int t) {

    }

    /**
        обход дерева
    */
    void traverse() {

    }

    /**
        обход дерева с получением каждого числа в виде вектора
    */
    void traverse(vector<int>& key) {

    }

    /**
        вставка нового элемента в дерево
    */
    void insert(int k) {

    }

    /**
        удаление ключа
    */
    void remove(int k) {

    }

    /**
        редактирование ключа
    */
    void edit(int oldkey, int newkey) {

    }

    /**
        очистка всего дерева
    */
    void clear() {

    }

    /**
        поиск в дереве
    */
    Node* search(int k) {

    }

    /**
        деструктор
    */
    ~BTree() {

    }
};
