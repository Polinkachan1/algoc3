#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

// Структура для обычного двоичного дерева
struct BinaryTree {
    int data;
    BinaryTree* left;
    BinaryTree* right;

    BinaryTree(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Структура для АВЛ дерева
struct AVLTree {
    int data;
    AVLTree* left;
    AVLTree* right;
    int height;

    AVLTree(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

struct BinaryTreeStack {
    BinaryTree** data;
    int capacity;
    int top;

    BinaryTreeStack(int size) {
        capacity = size;
        data = new BinaryTree * [capacity];
        top = -1;
    }

    ~BinaryTreeStack() {
        delete[] data;
    }

    void push(BinaryTree* node) {
        if (top < capacity - 1) {
            data[++top] = node;
        }
    }

    BinaryTree* pop() {
        if (top >= 0) {
            return data[top--];
        }
        return nullptr;
    }

    bool isEmpty() {
        return top == -1;
    }
};

struct AVLTreeStack {
    AVLTree** data;
    int capacity;
    int top;

    AVLTreeStack(int size) {
        capacity = size;
        data = new AVLTree * [capacity];
        top = -1;
    }

    ~AVLTreeStack() {
        delete[] data;
    }

    void push(AVLTree* node) {
        if (top < capacity - 1) {
            data[++top] = node;
        }
    }

    AVLTree* pop() {
        if (top >= 0) {
            return data[top--];
        }
        return nullptr;
    }

    bool isEmpty() {
        return top == -1;
    }
};

struct BinaryTreeQueue {
    BinaryTree** data;
    int capacity;
    int front;
    int rear;
    int count;

    BinaryTreeQueue(int size) {
        capacity = size;
        data = new BinaryTree * [capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    ~BinaryTreeQueue() {
        delete[] data;
    }

    void enqueue(BinaryTree* node) {
        if (count < capacity) {
            rear = (rear + 1) % capacity;
            data[rear] = node;
            count++;
        }
    }

    BinaryTree* dequeue() {
        if (count > 0) {
            BinaryTree* node = data[front];
            front = (front + 1) % capacity;
            count--;
            return node;
        }
        return nullptr;
    }

    bool isEmpty() {
        return count == 0;
    }
};

struct AVLTreeQueue {
    AVLTree** data;
    int capacity;
    int front;
    int rear;
    int count;

    AVLTreeQueue(int size) {
        capacity = size;
        data = new AVLTree * [capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    ~AVLTreeQueue() {
        delete[] data;
    }

    void enqueue(AVLTree* node) {
        if (count < capacity) {
            rear = (rear + 1) % capacity;
            data[rear] = node;
            count++;
        }
    }

    AVLTree* dequeue() {
        if (count > 0) {
            AVLTree* node = data[front];
            front = (front + 1) % capacity;
            count--;
            return node;
        }
        return nullptr;
    }

    bool isEmpty() {
        return count == 0;
    }
};

// Функции для обычного двоичного дерева

void dfsBinaryTree(BinaryTree* root) {
    if (root == nullptr) return;

    cout << root->data << " ";
    dfsBinaryTree(root->left);
    dfsBinaryTree(root->right);
}

void printBinaryTree(BinaryTree* root, int level = 0) {
    if (root == nullptr) {
        return;
    }
    printBinaryTree(root->right, level + 1);
    cout << setw(level * 4) << "";
    cout << "--> " << root->data << endl;
    printBinaryTree(root->left, level + 1);
}

void collectPreOrder(BinaryTree* root, vector<int>& elements) {
    if (root == nullptr) return;

    elements.push_back(root->data);
    collectPreOrder(root->left, elements);
    collectPreOrder(root->right, elements);
}

int countNodes(BinaryTree* root) {
    if (root == nullptr) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

void deleteBinaryTree(BinaryTree* root) {
    if (root == nullptr) return;

    deleteBinaryTree(root->left);
    deleteBinaryTree(root->right);
    delete root;
}

// Функции для АВЛ дерева

int getHeight(AVLTree* node) {
    return node ? node->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getBalance(AVLTree* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

bool isBalanced(AVLTree* node) {
    if (!node) return true;
    int balance = getBalance(node);
    return (balance >= -1 && balance <= 1) && isBalanced(node->left) && isBalanced(node->right);
}

void checkBalance(AVLTree* root) {
    bool balanced = isBalanced(root);
    cout << "Дерево " << (balanced ? "сбалансировано." : "несбалансировано.") << endl;
}

AVLTree* rightRotate(AVLTree* y) {
    AVLTree* x = y->left;
    AVLTree* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLTree* leftRotate(AVLTree* x) {
    AVLTree* y = x->right;
    AVLTree* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVLTree* insertAVL(AVLTree* node, int key) {
    if (!node) return new AVLTree(key);

    if (key < node->data) {
        node->left = insertAVL(node->left, key);
    }
    else if (key > node->data) {
        node->right = insertAVL(node->right, key);
    }
    else {
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);
    if (balance > 1 && key < node->left->data) {
        return rightRotate(node);
    }

    if (balance < -1 && key > node->right->data) {
        return leftRotate(node);
    }

    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVLTree* searchAVL(AVLTree* root, int key) {
    if (!root || root->data == key)
        return root;
    if (key < root->data)
        return searchAVL(root->left, key);
    else
        return searchAVL(root->right, key);
}

AVLTree* minValueNode(AVLTree* node) {
    AVLTree* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

AVLTree* deleteAVL(AVLTree* root, int key) {
    if (!root) return root;

    if (key < root->data) {
        root->left = deleteAVL(root->left, key);
    }
    else if (key > root->data) {
        root->right = deleteAVL(root->right, key);
    }
    else {
        if (!root->left || !root->right) {
            AVLTree* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            }
            else {
                *root = *temp; 
            }
            delete temp;
        }
        else {
            AVLTree* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteAVL(root->right, temp->data);
        }
    }

    if (!root) return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void printAVLTree(AVLTree* root, int level = 0) {
    if (root == nullptr) {
        return;
    }
    printAVLTree(root->right, level + 1);
    cout << setw(level * 4) << "";
    cout << "--> " << root->data << " (h:" << root->height << ")" << endl;
    printAVLTree(root->left, level + 1);
}

void deleteAVLTree(AVLTree* root) {
    if (root == nullptr) return;

    deleteAVLTree(root->left);
    deleteAVLTree(root->right);
    delete root;
}

// Обходы для АВЛ дерева
void breadthFirstTraversalAVL(AVLTree* root) {
    if (!root) return;

    AVLTreeQueue q(100);
    q.enqueue(root);

    cout << "Обход в ширину: ";
    while (!q.isEmpty()) {
        AVLTree* current = q.dequeue();
        cout << current->data << " ";

        if (current->left) q.enqueue(current->left);
        if (current->right) q.enqueue(current->right);
    }
    cout << endl;
}

void preorderIterativeAVL(AVLTree* root) {
    if (!root) return;

    AVLTreeStack stack(100);
    stack.push(root);

    cout << "Прямой обход: ";
    while (!stack.isEmpty()) {
        AVLTree* current = stack.pop();
        cout << current->data << " ";

        if (current->right) stack.push(current->right);
        if (current->left) stack.push(current->left);
    }
    cout << endl;
}

void inorderIterativeAVL(AVLTree* root) {
    if (!root) return;

    AVLTreeStack stack(100);
    AVLTree* current = root;

    cout << "Симметричный обход: ";
    while (current || !stack.isEmpty()) {
        while (current) {
            stack.push(current);
            current = current->left;
        }

        current = stack.pop();
        cout << current->data << " ";
        current = current->right;
    }
    cout << endl;
}

void postorderIterativeAVL(AVLTree* root) {
    if (!root) return;

    AVLTreeStack stack1(100), stack2(100);
    stack1.push(root);

    cout << "Обратный обход: ";
    while (!stack1.isEmpty()) {
        AVLTree* current = stack1.pop();
        stack2.push(current);

        if (current->left) stack1.push(current->left);
        if (current->right) stack1.push(current->right);
    }

    while (!stack2.isEmpty()) {
        cout << stack2.pop()->data << " ";
    }
    cout << endl;
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isValidBinaryTreeString(const string& str) {
    int balance = 0;
    for (char c : str) {
        if (c == '(') balance++;
        else if (c == ')') balance--;
        if (balance < 0) return false;
    }
    return balance == 0;
}

BinaryTree* parseBinaryTreeFromString(const string& str, size_t& pos) {
    while (pos < str.length() && str[pos] == ' ') pos++;

    if (pos >= str.length() || str[pos] != '(') {
        return nullptr;
    }

    pos++; 
    while (pos < str.length() && str[pos] == ' ') pos++;

    if (pos < str.length() && str[pos] == ')') {
        pos++;
        return nullptr;
    }

    string numStr = "";
    bool isNegative = false;

    if (str[pos] == '-') {
        isNegative = true;
        pos++;
    }

    while (pos < str.length() && isDigit(str[pos])) {
        numStr += str[pos];
        pos++;
    }

    if (numStr.empty()) {
        return nullptr;
    }

    int num = stoi(numStr);
    if (isNegative) {
        num = -num;
    }

    BinaryTree* node = new BinaryTree(num);

    node->left = parseBinaryTreeFromString(str, pos);

    node->right = parseBinaryTreeFromString(str, pos);

    while (pos < str.length() && str[pos] == ' ') pos++;
    if (pos < str.length() && str[pos] == ')') {
        pos++;
    }

    return node;
}

BinaryTree* createBinaryTreeFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return nullptr;
    }

    string line;
    getline(file, line);
    file.close();

    cout << "Прочитанная строка из файла: " << line << endl;

    if (!isValidBinaryTreeString(line)) {
        cout << "Ошибка: неверный формат скобочной записи!" << endl;
        return nullptr;
    }

    size_t pos = 0;
    BinaryTree* root = parseBinaryTreeFromString(line, pos);

    if (root == nullptr) {
        cout << "Ошибка при парсинге дерева!" << endl;
    }
    else {
        cout << "Двоичное дерево успешно создано!" << endl;
    }

    return root;
}

void convertToAVL(BinaryTree* binaryRoot, AVLTree*& avlRoot) {
    if (!binaryRoot) return;
    vector<int> elements;
    collectPreOrder(binaryRoot, elements);

    cout << "Элементы в порядке КЛП: ";
    for (int elem : elements) {
        cout << elem << " ";
    }
    cout << endl;
    for (int elem : elements) {
        avlRoot = insertAVL(avlRoot, elem);
    }
}

bool isValidAVL(AVLTree* root) {
    if (!root) return true;

    int balance = getBalance(root);
    if (balance < -1 || balance > 1) {
        cout << "Нарушен баланс в узле " << root->data << ": balance = " << balance << endl;
        return false;
    }

    if (root->left && root->left->data >= root->data) {
        cout << "Нарушено свойство: " << root->left->data << " >= " << root->data << endl;
        return false;
    }
    if (root->right && root->right->data <= root->data) {
        cout << "Нарушено свойство: " << root->right->data << " <= " << root->data << endl;
        return false;
    }

    return isValidAVL(root->left) && isValidAVL(root->right);
}
void displayMenu() {
    cout << "Лаба 3 - деревья" << endl;
    cout << "1. Загрузить двоичное дерево из файла" << endl;
    cout << "2. Показать двоичное дерево" << endl;
    cout << "3. Создать АВЛ дерево из двоичного" << endl;
    cout << "4. Показать АВЛ дерево" << endl;
    cout << "5. Обходы АВЛ дерева (4 способа - итеративные)" << endl;
    cout << "6. Вставка элемента в АВЛ дерево" << endl;
    cout << "7. Удаление элемента из АВЛ дерева" << endl;
    cout << "8. Поиск элемента в АВЛ дереве" << endl;
    cout << "9. Проверить балансировку АВЛ дерева" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите действие: ";
}

int main() {
    setlocale(0, "");
    BinaryTree* binaryTree = nullptr;
    AVLTree* avlTree = nullptr;
    string filename;
    int choice, value;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Введите имя файла: ";
            cin >> filename;

            if (binaryTree) {
                deleteBinaryTree(binaryTree);
                binaryTree = nullptr;
            }

            binaryTree = createBinaryTreeFromFile(filename);
            break;
        }

        case 2: {
            if (binaryTree) {
                cout << "Двоичное дерево:" << endl;
                printBinaryTree(binaryTree);
                cout << "Прямой обход в глубину: ";
                dfsBinaryTree(binaryTree);
                cout << endl;
            }
            else {
                cout << "Двоичное дерево не загружено!" << endl;
            }
            break;
        }

        case 3: {
            if (binaryTree) {
                if (avlTree) {
                    deleteAVLTree(avlTree);
                    avlTree = nullptr;
                }

                convertToAVL(binaryTree, avlTree);
                cout << "АВЛ дерево успешно создано!" << endl;

                if (isValidAVL(avlTree)) {
                    cout << "АВЛ дерево корректно!" << endl;
                }
                else {
                    cout << "Ошибка: АВЛ дерево некорректно!" << endl;
                }
                checkBalance(avlTree);
            }
            else {
                cout << "Сначала загрузите двоичное дерево!" << endl;
            }
            break;
        }

        case 4: {
            if (avlTree) {
                cout << "АВЛ дерево:" << endl;
                printAVLTree(avlTree);
            }
            else {
                cout << "АВЛ дерево не создано!" << endl;
            }
            break;
        }

        case 5: {
            if (avlTree) {
                cout << "\n=== ОБХОДЫ АВЛ ДЕРЕВА ===" << endl;
                breadthFirstTraversalAVL(avlTree);
                preorderIterativeAVL(avlTree);
                inorderIterativeAVL(avlTree);
                postorderIterativeAVL(avlTree);
            }
            else {
                cout << "АВЛ дерево не создано!" << endl;
            }
            break;
        }

        case 6: {
            if (avlTree) {
                cout << "Введите значение для вставки: ";
                cin >> value;
                avlTree = insertAVL(avlTree, value);
                cout << "Элемент вставлен!" << endl;
                checkBalance(avlTree);
            }
            else {
                cout << "АВЛ дерево не создано!" << endl;
            }
            break;
        }

        case 7: {
            if (avlTree) {
                cout << "Введите значение для удаления: ";
                cin >> value;

                AVLTree* found = searchAVL(avlTree, value);
                if (!found) {
                    cout << "Элемент " << value << " не найден в дереве!" << endl;
                }
                else {
                    avlTree = deleteAVL(avlTree, value);
                    cout << "Элемент удален!" << endl;
                    checkBalance(avlTree);
                }
            }
            else {
                cout << "АВЛ дерево не создано!" << endl;
            }
            break;
        }

        case 8: {
            if (avlTree) {
                cout << "Введите значение для поиска: ";
                cin >> value;
                if (searchAVL(avlTree, value)) {
                    cout << "Элемент найден!" << endl;
                }
                else {
                    cout << "Элемент не найден!" << endl;
                }
            }
            else {
                cout << "АВЛ дерево не создано!" << endl;
            }
            break;
        }

        case 9: {
            if (avlTree) {
                checkBalance(avlTree);
            }
            else {
                cout << "АВЛ дерево не создано!" << endl;
            }
            break;
        }

        case 0: {
            if (binaryTree) deleteBinaryTree(binaryTree);
            if (avlTree) deleteAVLTree(avlTree);
            cout << "Выход!" << endl;
            return 0;
        }

        default: {
            cout << "Неверный выбор!" << endl;
            break;
        }
        }

        cout << endl;
    }

    return 0;
}