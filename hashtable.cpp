#include <iostream>

const int TABLE_SIZE = 128;

class ForwardListNode {
public:
    int key;
    int value;
    ForwardListNode* next;

    ForwardListNode(int key, int value) {
        this->key = key;
        this->value = value;
        this->next = nullptr;
    }
};

// Forward List class
class ForwardList {
private:
    ForwardListNode* head;

public:
    ForwardList() {
        head = nullptr;
    }

    ~ForwardList() {
        while (head != nullptr) {
            ForwardListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(int key, int value) {
        ForwardListNode* node = new ForwardListNode(key, value);
        node->next = head;
        head = node;
    }

    bool remove(int key) {
        ForwardListNode* current = head;
        ForwardListNode* prev = nullptr;

        while (current != nullptr && current->key != key) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            return false;
        }

        if (prev == nullptr) {
            head = current->next;
        } else {
            prev->next = current->next;
        }

        delete current;
        return true;
    }

    int search(int key) {
        ForwardListNode* current = head;

        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }

        return -1;
    }

    bool update(int key, int value) {
        ForwardListNode* current = head;

        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return true;
            }
            current = current->next;
        }

        return false;
    }
};

class HashTable {
private:
    ForwardList* table;
    int elementCount;

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    HashTable() {
        table = new ForwardList[TABLE_SIZE];
        elementCount = 0;
    }

    ~HashTable() {
        delete[] table;
    }

    void insert(int key, int value) {
        int hash = hashFunction(key);

        if (!table[hash].update(key, value)) {
            table[hash].insert(key, value);
            elementCount++;
        }

        checkLoadFactor();
    }

    int search(int key) {
        int hash = hashFunction(key);
        return table[hash].search(key);
    }

    void remove(int key) {
        int hash = hashFunction(key);
        if (table[hash].remove(key)) {
            elementCount--;
        }
    }

    double getLoadFactor() {
        return static_cast<double>(elementCount) / TABLE_SIZE;
    }

    void checkLoadFactor() {
        double loadFactor = getLoadFactor();
        if (loadFactor > 0.75) {
            std::cout << "Warning: Load factor exceeded 0.75" << std::endl;
        }
    }
};

int main() {
    HashTable hashTable;
    hashTable.insert(1, 10);
    hashTable.insert(2, 20);
    hashTable.insert(3, 30);
    
    std::cout << "Value at key 1: " << hashTable.search(1) << std::endl;
    std::cout << "Value at key 2: " << hashTable.search(2) << std::endl;
    std::cout << "Value at key 3: " << hashTable.search(3) << std::endl;
    
    hashTable.remove(2);
    std::cout << "Value at key 2 after removal: " << hashTable.search(2) << std::endl;

    std::cout << "Current Load Factor: " << hashTable.getLoadFactor() << std::endl;

    return 0;
}
