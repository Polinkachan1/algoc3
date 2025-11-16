#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
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

// Ручная реализация стека для BinaryTree (для итеративных обходов)
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

// Ручная реализация стека для AVLTree (для итеративных обходов)
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

// Ручная реализация очереди для BinaryTree
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

// Ручная реализация очереди для AVLTree
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

// ТРИ ОБХОДА В ГЛУБИНУ (рекурсивные):
void preorderTraversalBinary(BinaryTree* root) {
    if (root == nullptr) return;
    cout << root->data << " ";
    preorderTraversalBinary(root->left);
    preorderTraversalBinary(root->right);
}

void inorderTraversalBinary(BinaryTree* root) {
    if (root == nullptr) return;
    inorderTraversalBinary(root->left);
    cout << root->data << " ";
    inorderTraversalBinary(root->right);
}

void postorderTraversalBinary(BinaryTree* root) {
    if (root == nullptr) return;
    postorderTraversalBinary(root->left);
    postorderTraversalBinary(root->right);
    cout << root->data << " ";
}

// Парсинг скобочной записи дерева
bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isValidBinaryTreeString(const string& str) {
    int balance = 0;
    bool expectingNumber = true;

    for (size_t i = 0; i < str.length(); i++) {
        char c = str[i];

        if (c == ' ') continue;

        if (c == '(') {
            balance++;
            expectingNumber = true;
        }
        else if (c == ')') {
            balance--;
            if (balance < 0) return false;
            expectingNumber = false;
        }
        else if (isDigit(c) || c == '-') {
            if (!expectingNumber) return false;
            if (c == '-' && (i + 1 >= str.length() || !isDigit(str[i + 1]))) {
                return false;
            }
            // Пропускаем остальные цифры числа
            while (i + 1 < str.length() && isDigit(str[i + 1])) {
                i++;
            }
            expectingNumber = false;
        }
        else {
            return false;
        }
    }

    return balance == 0;
}

BinaryTree* parseBinaryTreeFromString(const string& str, size_t& pos) {
    // Пропускаем пробелы
    while (pos < str.length() && str[pos] == ' ') pos++;

    if (pos >= str.length() || str[pos] != '(') {
        return nullptr;
    }

    pos++; // Пропускаем '('

    // Пропускаем пробелы
    while (pos < str.length() && str[pos] == ' ') pos++;

    // Проверяем на пустой узел
    if (pos < str.length() && str[pos] == ')') {
        pos++;
        return nullptr;
    }

    // Читаем число
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

    // Обрабатываем левого потомка
    node->left = parseBinaryTreeFromString(str, pos);

    // Обрабатываем правого потомка
    node->right = parseBinaryTreeFromString(str, pos);

    // Пропускаем пробелы и закрывающую скобку
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

AVLTree* insertAVL(AVLTree* root, int key) {
    if (!root) return new AVLTree(key);

    if (key < root->data) {
        root->left = insertAVL(root->left, key);
    }
    else if (key > root->data) {
        root->right = insertAVL(root->right, key);
    }
    else {
        return root; // Дубликаты не разрешены
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && key < root->left->data) {
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && key > root->right->data) {
        return leftRotate(root);
    }

    // Left Right Case
    if (balance > 1 && key > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && key < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

AVLTree* minValueNode(AVLTree* node) {
    AVLTree* current = node;
    while (current->left) {
        current = current->left;
    }
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

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

bool searchAVL(AVLTree* root, int key) {
    if (!root) return false;

    if (key == root->data) return true;
    if (key < root->data) return searchAVL(root->left, key);
    return searchAVL(root->right, key);
}

// Итеративные обходы для АВЛ дерева

// Прямой обход (КЛП) - итеративный
void preorderIterativeAVL(AVLTree* root) {
    if (!root) return;

    AVLTreeStack stack(100);
    stack.push(root);

    while (!stack.isEmpty()) {
        AVLTree* current = stack.pop();
        cout << current->data << " ";

        if (current->right) stack.push(current->right);
        if (current->left) stack.push(current->left);
    }
}

// Центрированный обход (ЛКП) - итеративный
void inorderIterativeAVL(AVLTree* root) {
    if (!root) return;

    AVLTreeStack stack(100);
    AVLTree* current = root;

    while (current || !stack.isEmpty()) {
        while (current) {
            stack.push(current);
            current = current->left;
        }

        current = stack.pop();
        cout << current->data << " ";
        current = current->right;
    }
}

// Обратный обход (ЛПК) - итеративный
void postorderIterativeAVL(AVLTree* root) {
    if (!root) return;

    AVLTreeStack stack1(100), stack2(100);
    stack1.push(root);

    while (!stack1.isEmpty()) {
        AVLTree* current = stack1.pop();
        stack2.push(current);

        if (current->left) stack1.push(current->left);
        if (current->right) stack1.push(current->right);
    }

    while (!stack2.isEmpty()) {
        cout << stack2.pop()->data << " ";
    }
}

// Обход в ширину для АВЛ дерева - итеративный
void breadthFirstTraversalAVL(AVLTree* root) {
    if (!root) return;

    AVLTreeQueue q(100);
    q.enqueue(root);

    while (!q.isEmpty()) {
        AVLTree* current = q.dequeue();
        cout << current->data << " ";

        if (current->left) q.enqueue(current->left);
        if (current->right) q.enqueue(current->right);
    }
}

// Вспомогательные функции для вывода деревьев
void printBinaryTree(BinaryTree* root, int level = 0) {
    if (!root) return;

    printBinaryTree(root->right, level + 1);
    cout << string(level * 4, ' ') << root->data << endl;
    printBinaryTree(root->left, level + 1);
}

void printAVLTree(AVLTree* root, int level = 0) {
    if (!root) return;

    printAVLTree(root->right, level + 1);
    cout << string(level * 4, ' ') << root->data << " (h:" << root->height << ")" << endl;
    printAVLTree(root->left, level + 1);
}

// Освобождение памяти
void deleteBinaryTree(BinaryTree* root) {
    if (!root) return;
    deleteBinaryTree(root->left);
    deleteBinaryTree(root->right);
    delete root;
}

void deleteAVLTree(AVLTree* root) {
    if (!root) return;
    deleteAVLTree(root->left);
    deleteAVLTree(root->right);
    delete root;
}

// Создание АВЛ дерева из обычного двоичного дерева
void convertToAVL(BinaryTree* binaryRoot, AVLTree*& avlRoot) {
    if (!binaryRoot) return;

    // Обход в ширину обычного дерева и вставка в АВЛ
    BinaryTreeQueue q(100);
    q.enqueue(binaryRoot);

    while (!q.isEmpty()) {
        BinaryTree* current = q.dequeue();
        avlRoot = insertAVL(avlRoot, current->data);

        if (current->left) q.enqueue(current->left);
        if (current->right) q.enqueue(current->right);
    }
}

// Меню
void displayMenu() {
    cout << "=== МЕНЮ ДЕРЕВЬЯ ===" << endl;
    cout << "1. Загрузить двоичное дерево из файла" << endl;
    cout << "2. Показать двоичное дерево" << endl;
    cout << "3. Три обхода двоичного дерева в глубину (рекурсивные)" << endl;
    cout << "4. Создать АВЛ дерево из двоичного" << endl;
    cout << "5. Показать АВЛ дерево" << endl;
    cout << "6. Обходы АВЛ дерева (4 способа - итеративные)" << endl;
    cout << "7. Вставка элемента в АВЛ дерево" << endl;
    cout << "8. Удаление элемента из АВЛ дерева" << endl;
    cout << "9. Поиск элемента в АВЛ дереве" << endl;
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
            }
            else {
                cout << "Двоичное дерево не загружено!" << endl;
            }
            break;
        }

        case 3: {
            if (binaryTree) {
                cout << "Прямой обход (КЛП): ";
                preorderTraversalBinary(binaryTree);
                cout << endl;

                cout << "Центрированный обход (ЛКП): ";
                inorderTraversalBinary(binaryTree);
                cout << endl;

                cout << "Обратный обход (ЛПК): ";
                postorderTraversalBinary(binaryTree);
                cout << endl;
            }
            else {
                cout << "Двоичное дерево не загружено!" << endl;
            }
            break;
        }

        case 4: {
            if (binaryTree) {
                if (avlTree) {
                    deleteAVLTree(avlTree);
                    avlTree = nullptr;
                }
                convertToAVL(binaryTree, avlTree);
                cout << "АВЛ дерево успешно создано!" << endl;
            }
            else {
                cout << "Сначала загрузите двоичное дерево!" << endl;
            }
            break;
        }

        case 5: {
            if (avlTree) {
                cout << "АВЛ дерево:" << endl;
                printAVLTree(avlTree);
            }
            else {
                cout << "АВЛ дерево не создано!" << endl;
            }
            break;
        }

        case 6: {
            if (avlTree) {
                cout << "Обход в ширину: ";
                breadthFirstTraversalAVL(avlTree);
                cout << endl;

                cout << "Прямой обход (КЛП) - итеративный: ";
                preorderIterativeAVL(avlTree);
                cout << endl;

                cout << "Центрированный обход (ЛКП) - итеративный: ";
                inorderIterativeAVL(avlTree);
                cout << endl;

                cout << "Обратный обход (ЛПК) - итеративный: ";
                postorderIterativeAVL(avlTree);
                cout << endl;
            }
            else {
                cout << "АВЛ дерево не создано!" << endl;
            }
            break;
        }

        case 7: {
            if (avlTree) {
                cout << "Введите значение для вставки: ";
                cin >> value;
                avlTree = insertAVL(avlTree, value);
                cout << "Элемент вставлен!" << endl;
            }
            else {
                cout << "АВЛ дерево не создано!" << endl;
            }
            break;
        }

        case 8: {
            if (avlTree) {
                cout << "Введите значение для удаления: ";
                cin >> value;
                avlTree = deleteAVL(avlTree, value);
                cout << "Элемент удален!" << endl;
            }
            else {
                cout << "АВЛ дерево не создано!" << endl;
            }
            break;
        }

        case 9: {
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