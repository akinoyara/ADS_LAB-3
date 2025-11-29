#include "iostream"
#include <fstream>

using namespace std;


template <typename T>
class StackNode {
public:
	T value;
	StackNode<T>* next=nullptr;
public:
	StackNode(T value) {
		this->value = value;
	}
};


template <typename T>
class Stack {
public:
	StackNode<T>* top;

public:
	Stack<T>() {
		top = nullptr;
	}
	~Stack() {
		while (!isEmpty()) {
			pop();
		}
	}
	void push(T value) {
		StackNode<T>* temp = new StackNode<T>(value);
		temp->next = top;
		top = temp;
	}

	void pop() {
		if (!isEmpty()) {
			StackNode<T>* temp = top;
			temp = top->next;
			delete top;
			top = temp;
		}
		else {
			cout << "Стэк и так пуст";
			return;
		}
	}

	bool isEmpty() {
		return (top==nullptr);
	}

	T get() {
		if (!isEmpty()) {
			return top->value;
		}
		else {
			cout << "Стэк пуст";
			return T();
		}
	}
	
	int size() {
		StackNode<T>* cur = top;
		int count(0);
		while (cur) {
			cur = cur->next;
			count++;
		}
		return count;
	}

};

template <typename T>
class Queue{
public:
    StackNode<T>* head;
    StackNode<T>* tail;
    int size=0;
public:
    Queue<T>(){
        this->head = nullptr;
        this->tail=nullptr;
    }
    ~Queue<T>(){
        while (!isEmpty()) {
			pop();
		}
    }
    bool isEmpty(){
        return (head==nullptr);
    }
    void push (T value){
        StackNode<T>* temp = new StackNode<T>(value);
        temp -> next = nullptr;
        if (!isEmpty()){
            tail->next = temp;
            tail=temp;
        }
        else{
            head=tail=temp;
        }
        size++;
    }
    StackNode<T>* front(){
        if(!isEmpty()){
            return head;
        }
        else{
            cout << "Очередь пуста" << endl;
            return nullptr;
        }
    }
    void pop(){
        if(!isEmpty()){
            StackNode<T>* temp = head;
            head=head->next;
            delete temp;
            size--;
            if (head==nullptr){
                tail=nullptr;
            }
        }
        else{
            cout << "Очередь пуста" << endl;
            return;
        }
    }
};

class TreeNode{
public:
    int value;
    TreeNode* left;
    TreeNode* right;
public:
    TreeNode(int value, TreeNode* left, TreeNode* right){
        this->value = value;
        this->left = left;
        this->right = right;
    }
    TreeNode(int value){
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
    }
    TreeNode(){
        value = 0;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree{
public:
    TreeNode* root;
    BinaryTree(TreeNode* root){
        this->root = root;
    }
    BinaryTree(){
        this->root = nullptr;
    }
public:
    void insertLeft(TreeNode* parent, int value){
        if (parent==nullptr){
            return;
        }
        if (parent->left!=nullptr){
            return;
        }
        else{
            parent->left = new TreeNode(value);
        }
    }
    void insertRight(TreeNode* parent, int value){
        if (parent==nullptr){
            return;
        }
        if (parent->right!=nullptr){
            return;
        }
        else{
            parent->right = new TreeNode(value);
        }
    }
    TreeNode* findParentElement(TreeNode* root, int value){
        if (!root) return nullptr;
        if ((root->left && root->left->value == value) || (root->right && root->right->value == value)){
            return root;
        }
        TreeNode* leftSearch = findParentElement(root->left, value);
        if (leftSearch) return leftSearch;
        return findParentElement(root->right, value);
    }

    TreeNode* findElement(TreeNode* root, int value){
        if (!root) return nullptr;
        if (root->value == value) return root;
        TreeNode* leftSearch = findElement(root->left, value);
        if (leftSearch) return leftSearch;
        return findElement(root->right, value);
    }
        void remove(int value){
        if (this->root == nullptr) return;

        TreeNode* object = findElement(this->root, value);
        if (object == nullptr) return;

        TreeNode* parentObject = findParentElement(this->root, value);

        if (object->left == nullptr && object->right == nullptr){
            if (parentObject != nullptr){
                if (parentObject->left == object){
                    parentObject->left = nullptr;
                }
                else{
                    parentObject->right = nullptr;
                }
            }
            else{
                this->root = nullptr;
            }
            delete object;
        }
        else if ((object->left != nullptr && object->right == nullptr) || (object->left == nullptr && object->right != nullptr)){
            TreeNode* child;
            if (object->left != nullptr){
                child = object->left;
            }
            else{
                child = object->right;
            }

            if (parentObject != nullptr){
                if (parentObject->left == object){
                    parentObject->left = child;
                }
                else{
                    parentObject->right = child;
                }
                delete object;
            }
            else{
                object->value = child->value;
                object->left = child->left;
                object->right = child->right;
                delete child;
            }
        }
        else if (object->left != nullptr && object->right != nullptr){
            TreeNode* tempParent = object;
            TreeNode* temp = object->right;
            while (temp->left != nullptr){
                tempParent = temp;
                temp = temp->left;
            }

            object->value = temp->value;

            if (tempParent->left == temp){
                if (temp->right != nullptr){
                    tempParent->left = temp->right;
                }
                else{
                    tempParent->left = nullptr;
                }
            }
            else{
                if (temp->right != nullptr){
                    tempParent->right = temp->right;
                }
                else{
                    tempParent->right = nullptr;
                }
            }
            delete temp;
        }
    }

    void levelOrderPrint(TreeNode *root){
        if (root==nullptr){
            return;
        }
        Queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.isEmpty()){
            TreeNode* temp = queue.front()->value;
            cout << temp->value << " ";
            queue.pop();
            if (temp->left!=nullptr){
                queue.push(temp->left);
            }
            if(temp->right!=nullptr){
                queue.push(temp->right);
            }
        }
    }
    void preorderPrint(TreeNode* root){
        if (root==nullptr){
            return;
        }
        cout << root->value << " ";
        preorderPrint(root->left);
        preorderPrint(root->right);
    }

    void symmetricOrderPrint(TreeNode* root){
        if(root==nullptr){
            return;
        }
        symmetricOrderPrint(root->left);
        cout << root->value << " ";
        symmetricOrderPrint(root->right);
    }

    void reverseOrderPrint(TreeNode* root){
        if (root==nullptr){
            return;
        }
        reverseOrderPrint(root->left);
        reverseOrderPrint(root->right);
        cout << root->value << " ";
    }
};


class AVLNode{
public:
    int value;
    unsigned char height;
    AVLNode* left;
    AVLNode* right;
public:
    AVLNode(int value){
        this->value = value;
        this->height = 1;
        this->left = nullptr;
        this->right = nullptr;
    }
    AVLNode(){
        this->value = 0;
        this->height=1;
        this->left = nullptr;
        this->right = nullptr;
    }
};

void symmetricOrderPrintAVL(AVLNode* root) {
    if (!root) return;
    symmetricOrderPrintAVL(root->left);
    cout << root->value << " ";
    symmetricOrderPrintAVL(root->right);
}

unsigned char height(AVLNode* node){
    if(node){
        return node->height;
    } else{
        return 0;
    }
}

int balanceFactor(AVLNode* node){
    return (height(node->left)-height(node->right));
}

void fixHeight(AVLNode* node){
    int heightLeft = height(node->left);
    int heightRight = height(node->right);
    if (heightRight>heightLeft){
        node->height = heightRight+1;
    }
    else{
        node->height = heightLeft+1;
    }
}

AVLNode* smallRightRotate(AVLNode* a){
    AVLNode* b = a->left;
    a->left = b->right;
    b->right = a;
    fixHeight(a);
    fixHeight(b);
    return b;
}

AVLNode* smallLeftRotate(AVLNode* a){
    AVLNode* b = a->right;
    a->right = b->left;
    b->left = a;
    fixHeight(a);
    fixHeight(b);
    return b;
}

AVLNode* balance(AVLNode* node){
    fixHeight(node);
    if (balanceFactor(node)>=2){
        if (balanceFactor(node->left)<0){
            node->left = smallLeftRotate(node->left);
        }
        return smallRightRotate(node);
    }
    if (balanceFactor(node)<=-2){
        if (balanceFactor(node->right) > 0){
            node->right = smallRightRotate(node->right);
        }
        return smallLeftRotate(node);
    }
    return node;
}

AVLNode* insert(AVLNode* node, int value){
    if (!node){
        return new AVLNode(value);
    }
    if (value < node->value){
        node->left = insert(node->left, value);
    } else {
        node->right = insert(node->right, value);
    }
    return balance(node);
}
AVLNode* findMin(AVLNode* node) {
    if (!node) return nullptr;
    AVLNode* cur = node;
    while (cur->left) cur = cur->left;
    return cur;
}

AVLNode* removeMin(AVLNode* node) {
    if (!node) return nullptr;
    if (node->left == nullptr) {
        AVLNode* rightSub = node->right;
        delete node;
        return rightSub;
    }
    node->left = removeMin(node->left);
    return balance(node);
}

AVLNode* deleteNodeAVL(AVLNode* node, int value) {
    if (!node) return nullptr;
    if (value < node->value)
        node->left = deleteNodeAVL(node->left, value);
    else if (value > node->value)
        node->right = deleteNodeAVL(node->right, value);
    else {
        AVLNode* left = node->left;
        AVLNode* right = node->right;
        delete node;
        if (!right) return left;
        AVLNode* min = findMin(right);
        min->right = removeMin(right);
        min->left = left;
        return balance(min);
    }
    return balance(node);
}

TreeNode* parseNode(const char* s, int& pos) {
    while (s[pos] == ' ') pos++;

    if (s[pos] != '(') return nullptr;
    pos++;

    while (s[pos] == ' ') pos++;

    int sign = 1;
    if (s[pos] == '-') { sign = -1; pos++; }

    int val = 0;
    while (s[pos] >= '0' && s[pos] <= '9') {
        val = val * 10 + (s[pos] - '0');
        pos++;
    }
    val *= sign;

    TreeNode* node = new TreeNode(val);

    while (s[pos] == ' ') pos++;

    if (s[pos] == '(')
        node->left = parseNode(s, pos);

    while (s[pos] == ' ') pos++;

    if (s[pos] == '(')
        node->right = parseNode(s, pos);

    while (s[pos] == ' ') pos++;

    if (s[pos] != ')') {
        cout << "Ошибка: ожидалась )\n";
        return nullptr;
    }
    pos++; 

    return node;
}


void iterativePreorder(TreeNode* root) {
    Stack<TreeNode*> st;
    if (root) st.push(root);

    while (!st.isEmpty()) {
        TreeNode* node = st.get();
        st.pop();
        cout << node->value << " ";

        if (node->right) st.push(node->right);
        if (node->left)  st.push(node->left);
    }
}

void iterativeInorder(TreeNode* root) {
    Stack<TreeNode*> st;
    TreeNode* cur = root;

    while (cur || !st.isEmpty()) {
        while (cur) {
            st.push(cur);
            cur = cur->left;
        }
        cur = st.get();
        st.pop();
        cout << cur->value << " ";
        cur = cur->right;
    }
}

void iterativePostorder(TreeNode* root) {
    Stack<TreeNode*> st1, st2;
    if (root) st1.push(root);

    while (!st1.isEmpty()) {
        TreeNode* n = st1.get(); st1.pop();
        st2.push(n);

        if (n->left)  st1.push(n->left);
        if (n->right) st1.push(n->right);
    }

    while (!st2.isEmpty()) {
        cout << st2.get()->value << " ";
        st2.pop();
    }
}

void buildAVLFromBinary(TreeNode* root, AVLNode*& avl) {
    if (!root) return;
    avl = insert(avl, root->value);
    buildAVLFromBinary(root->left, avl);
    buildAVLFromBinary(root->right, avl);
}

void avlInorderRecursive(AVLNode* node) {
    if (!node) return;
    avlInorderRecursive(node->left);
    cout << node->value << " ";
    avlInorderRecursive(node->right);
}

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("tree.txt");
    if (!fin) {
        cout << "Не удалось открыть файл tree.txt\n";
        return 1;
    }

    string input, line;
    while (getline(fin, line)) {
        input += line;
    }
    fin.close();

    if (input.empty()) {
        cout << "Файл пустой\n";
        return 1;
    }
    int pos = 0;
    TreeNode* root = parseNode(input.c_str(), pos);

    if (!root) {
        cout << "Ошибка в скобочной записи\n";
        return 1;
    }

    cout << "Бинарное дерево загружено из файла.\n";

    cout << "Симметричный обход бинарного дерева:\n";
    BinaryTree bt(root);
    bt.symmetricOrderPrint(root);
    cout << "\n";

    AVLNode* avl = nullptr;
    buildAVLFromBinary(root, avl);

    cout << "Симметричный обход AVL:\n";
    avlInorderRecursive(avl);
    cout << "\n";

    return 0;
}
