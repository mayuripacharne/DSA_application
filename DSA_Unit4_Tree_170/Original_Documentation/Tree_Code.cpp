#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    int height;
    Node* left;
    Node* right;
};

int height(Node* n) {
    if (n == NULL)
        return 0;
    return n->height;
}

int maxValue(int a, int b) {
    return (a > b) ? a : b;
}

Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int getBalance(Node* n) {
    if (n == NULL)
        return 0;

    return height(n->left) - height(n->right);
}

// Right Rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + maxValue(height(y->left),
                             height(y->right));

    x->height = 1 + maxValue(height(x->left),
                             height(x->right));

    return x;
}

// Left Rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + maxValue(height(x->left),
                             height(x->right));

    y->height = 1 + maxValue(height(y->left),
                             height(y->right));

    return y;
}

// Insert node into AVL tree
Node* insert(Node* root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);

    else if (value > root->data)
        root->right = insert(root->right, value);

    else
        return root;

    root->height = 1 + maxValue(height(root->left),
                                height(root->right));

    int balance = getBalance(root);

    // LL Case
    if (balance > 1 && value < root->left->data)
        return rightRotate(root);

    // RR Case
    if (balance < -1 && value > root->right->data)
        return leftRotate(root);

    // LR Case
    if (balance > 1 && value > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Case
    if (balance < -1 && value < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Inorder Traversal
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// Preorder Traversal
void preorder(Node* root) {
    if (root != NULL) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder Traversal
void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

// Level Order Traversal
void levelOrder(Node* root) {
    if (root == NULL)
        return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        cout << current->data << " ";

        if (current->left != NULL)
            q.push(current->left);

        if (current->right != NULL)
            q.push(current->right);
    }
}

int main() {
    Node* root = NULL;
    int n, value;

    cout << "AVL Tree Traversal System\n";

    cout << "Enter number of integers: ";
    cin >> n;

    if (n <= 0) {
        cout << "Please enter a positive number.\n";
        return 0;
    }

    cout << "Enter " << n << " integers:\n";

    for (int i = 0; i < n; i++) {
        cin >> value;
        root = insert(root, value);
    }

    cout << "\nInorder Traversal: ";
    inorder(root);

    cout << "\nPreorder Traversal: ";
    preorder(root);

    cout << "\nPostorder Traversal: ";
    postorder(root);

    cout << "\nLevel Order Traversal: ";
    levelOrder(root);

    cout << "\n";

    return 0;
}