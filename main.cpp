#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class BTree {
    struct Node {
        int* keys;
        int t;
        Node** C;
        int n;
        bool leaf;

        Node(int t, bool leaf) {
            this->t = t;
            this->leaf = leaf;
            keys = new int[2 * t - 1];
            C = new Node * [2 * t];
            n = 0;
        }

        int findKey(int k) {
            int idx = 0;
            while (idx < n && keys[idx] < k)
                ++idx;
            return idx;
        }

        void remove(int k) {
            int idx = findKey(k);
            if (idx < n && keys[idx] == k) {
                if (leaf)
                    removeFromLeaf(idx);
                else
                    removeFromNonLeaf(idx);
            }
            else {
                if (leaf) {
                    cout << "The key " << k << " is does not exist in the tree\n";
                    return;
                }
                bool flag = ((idx == n) ? true : false);
                if (C[idx]->n < t)
                    fill(idx);
                if (flag && idx > n)
                    C[idx - 1]->remove(k);
                else
                    C[idx]->remove(k);
            }
            return;
        }

        void removeFromLeaf(int idx) {
            for (int i = idx + 1; i < n; ++i)
                keys[i - 1] = keys[i];
            n--;
            return;
        }

        void removeFromNonLeaf(int idx) {
            int k = keys[idx];
            if (C[idx]->n >= t) {
                int pred = getPrev(idx);
                keys[idx] = pred;
                C[idx]->remove(pred);
            }
            else if (C[idx + 1]->n >= t) {
                int succ = getSucc(idx);
                keys[idx] = succ;
                C[idx + 1]->remove(succ);
            }
            else {
                merge(idx);
                C[idx]->remove(k);
            }
            return;
        }

        int getPrev(int idx) {
            Node* cur = C[idx];
            while (!cur->leaf)
                cur = cur->C[cur->n];
            return cur->keys[cur->n - 1];
        }

        int getSucc(int idx) {
            Node* cur = C[idx + 1];
            while (!cur->leaf)
                cur = cur->C[0];
            return cur->keys[0];
        }

        void fill(int idx) {
            if (idx != 0 && C[idx - 1]->n >= t)
                stealFromPrev(idx);
            else if (idx != n && C[idx + 1]->n >= t)
                stealFromNext(idx);
            else {
                if (idx != n)
                    merge(idx);
                else
                    merge(idx - 1);
            }
            return;
        }

        void stealFromPrev(int idx) {
            Node* child = C[idx];
            Node* sibling = C[idx - 1];
            for (int i = child->n - 1; i >= 0; --i)
                child->keys[i + 1] = child->keys[i];
            if (!child->leaf) {
                for (int i = child->n; i >= 0; --i)
                    child->C[i + 1] = child->C[i];
            }
            child->keys[0] = keys[idx - 1];
            if (!child->leaf)
                child->C[0] = sibling->C[sibling->n];
            keys[idx - 1] = sibling->keys[sibling->n - 1];
            child->n += 1;
            sibling->n -= 1;
            return;
        }

        void stealFromNext(int idx) {
            Node* child = C[idx];
            Node* sibling = C[idx + 1];
            child->keys[(child->n)] = keys[idx];
            if (!(child->leaf))
                child->C[(child->n) + 1] = sibling->C[0];
            keys[idx] = sibling->keys[0];
            for (int i = 1; i < sibling->n; ++i)
                sibling->keys[i - 1] = sibling->keys[i];
            if (!sibling->leaf) {
                for (int i = 1; i <= sibling->n; ++i)
                    sibling->C[i - 1] = sibling->C[i];
            }
            child->n += 1;
            sibling->n -= 1;
            return;
        }

        void merge(int idx) {
            Node* child = C[idx];
            Node* sibling = C[idx + 1];
            child->keys[t - 1] = keys[idx];
            for (int i = 0; i < sibling->n; ++i)
                child->keys[i + t] = sibling->keys[i];
            if (!child->leaf) {
                for (int i = 0; i <= sibling->n; ++i)
                    child->C[i + t] = sibling->C[i];
            }
            for (int i = idx + 1; i < n; ++i)
                keys[i - 1] = keys[i];
            for (int i = idx + 2; i <= n; ++i)
                C[i - 1] = C[i];
            child->n += sibling->n + 1;
            n--;
            delete sibling;
            return;
        }

        void insertNonFull(int k) {
            int i = n - 1;
            if (leaf) {
                while (i >= 0 && keys[i] > k) {
                    keys[i + 1] = keys[i];
                    i--;
                }
                keys[i + 1] = k;
                n = n + 1;
            }
            else {
                while (i >= 0 && keys[i] > k)
                    i--;
                if (C[i + 1]->n == 2 * t - 1) {
                    splitChild(i + 1, C[i + 1]);
                    if (keys[i + 1] < k)
                        i++;
                }
                C[i + 1]->insertNonFull(k);
            }
        }

        void splitChild(int i, Node* y) {
            Node* z = new Node(y->t, y->leaf);
            z->n = t - 1;
            for (int j = 0; j < t - 1; j++)
                z->keys[j] = y->keys[j + t];
            if (!y->leaf) {
                for (int j = 0; j < t; j++)
                    z->C[j] = y->C[j + t];
            }
            y->n = t - 1;
            for (int j = n; j >= i + 1; j--)
                C[j + 1] = C[j];
            C[i + 1] = z;
            for (int j = n - 1; j >= i; j--)
                keys[j + 1] = keys[j];
            keys[i] = y->keys[t - 1];
            n = n + 1;
        }

        void traverse() {
            int i;
            for (i = 0; i < n; i++) {
                if (!leaf)
                    C[i]->traverse();
                cout << " " << keys[i];
            }
            if (!leaf)
                C[i]->traverse();
        }

        void traverse(vector<int>& key) {
            int i;
            for (i = 0; i < n; i++) {
                if (!leaf)
                    C[i]->traverse(key);
                key.push_back(keys[i]);
            }
            if (!leaf)
                C[i]->traverse(key);
        }

        void clear() {
            int i;
            if (leaf) {
                delete[] keys;
            }
            else {
                for (i = 0; i < n; i++) {
                    C[i]->clear();
                    delete C[i];
                }
                C[i]->clear();
                delete C[i];
                delete[] keys;
            }
            delete[] C;
        }

        Node* search(int k) {
            int i = 0;
            while (i < n && k > keys[i])
                i++;
            if (keys[i] == k)
                return this;
            if (leaf)
                return nullptr;
            return C[i]->search(k);
        }
    };

    Node* root;
    int t;

public:
    BTree(int t) {
        root = nullptr;
        this->t = t;
    }

    void traverse() {
        if (root)
            root->traverse();
    }

    void traverse(vector<int>& key) {
        if (root)
            root->traverse(key);
    }

    void insert(int k) {
        if (!root) {
            root = new Node(t, true);
            root->keys[0] = k;
            root->n = 1;
        }
        else {
            if (root->n == 2 * t - 1) {
                Node* s = new Node(t, false);
                s->C[0] = root;
                s->splitChild(0, root);
                int i = 0;
                if (s->keys[0] < k)
                    i++;
                s->C[i]->insertNonFull(k);
                root = s;
            }
            else
                root->insertNonFull(k);
        }
    }

    void remove(int k) {
        if (!root) {
            cout << "B-tree is empty\n";
            return;
        }
        root->remove(k);
        if (root->n == 0) {
            Node* tmp = root;
            if (root->leaf)
                root = nullptr;
            else
                root = root->C[0];
            delete tmp;
        }
        return;
    }

    void edit(int oldkey, int newkey) {
        if (search(oldkey)) {
            remove(oldkey);
            insert(newkey);
        }
    }

    void clear() {
        if (root)
            root->clear();
        delete root;
        root = nullptr;
    }

    Node* search(int k) {
        return (!root) ? nullptr : root->search(k);
    }

    ~BTree() {
        clear();
    }
};


int main() {
    vector<int> input = { 4,2,6,1,5,7,1,-1,-6,-4 };
    int t = 3; 
    BTree b(t);

    for (int i = 0; i < input.size(); i++) {
        b.insert(input[i]);
    }
    vector<int> output;

    for (int i = 0; i < input.size(); i++) {
        for (int j = input.size() - 1; j > i; j--) {
            if (input[j] < input[j - 1]) {
                swap(input[j], input[j - 1]);
            }
        }
    }
    b.traverse(output);
    cout << "What expected after insert: ";
    for (auto i : input) {
        cout << i << " ";
    }
    cout << "\nWhat we get: ";
    for (auto i : output) {
        cout << i << " ";
    }
    cout << endl << endl;

    if (b.search(1)) {
        cout << "btree contains 1 - ok." << endl;
    }

    if (!b.search(-5)) {
        cout << "btree don't contains -5 - ok." << endl;
    }

    b.remove(1);
    b.remove(1);
    b.remove(5);
    input.erase(remove(input.begin(), input.end(), 1), input.end());
    input.erase(remove(input.begin(), input.end(), 5), input.end());
    if (!b.search(1) && !b.search(5)) {
        cout << "btree don't contains 1 and 5 after remove - ok." << endl;
    }

    cout << "\nWhat expected after remove: ";
    for (auto i : input) {
        cout << i << " ";
    }

    output.clear();
    b.traverse(output);
    cout << "\nWhat we get: ";
    for (auto i : output) {
        cout << i << " ";
    }
    cout << endl;

    b.edit(6, 10);
    b.edit(-6, 90);
    b.edit(4, 8);

    input.erase(remove(input.begin(), input.end(), 6), input.end());
    input.erase(remove(input.begin(), input.end(), -6), input.end());
    input.erase(remove(input.begin(), input.end(), 4), input.end());

    input.push_back(10);
    input.push_back(90);
    input.push_back(8);
    for (int i = 0; i < input.size(); i++) {
        for (int j = input.size() - 1; j > i; j--) {
            if (input[j] < input[j - 1]) {
                swap(input[j], input[j - 1]);
            }
        }
    }

    cout << "\nWhat expected after edit: ";
    for (auto i : input) {
        cout << i << " ";
    }

    output.clear();
    b.traverse(output);
    cout << "\nWhat we get: ";
    for (auto i : output) {
        cout << i << " ";
    }
    cout << endl;

    cout << endl;
    system("pause");
    return 0;
}