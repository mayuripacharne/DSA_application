#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    int data;
    int height;
    Node* left;
    Node* right;
};

int getHeight(Node* node) {
    if (node == NULL)
        return 0;

    return node->height;
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

int getBalance(Node* node) {
    if (node == NULL)
        return 0;

    return getHeight(node->left)
         - getHeight(node->right);
}

// Right Rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + maxValue(
        getHeight(y->left),
        getHeight(y->right)
    );

    x->height = 1 + maxValue(
        getHeight(x->left),
        getHeight(x->right)
    );

    return x;
}

// Left Rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + maxValue(
        getHeight(x->left),
        getHeight(x->right)
    );

    y->height = 1 + maxValue(
        getHeight(y->left),
        getHeight(y->right)
    );

    return y;
}

// Insert value into AVL tree
Node* insert(Node* root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->data) {
        root->left = insert(root->left, value);
    }
    else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    else {
        cout << "Duplicate value ignored: "
             << value << endl;
        return root;
    }

    root->height = 1 + maxValue(
        getHeight(root->left),
        getHeight(root->right)
    );

    int balance = getBalance(root);

    // LL Case
    if (balance > 1 &&
        value < root->left->data)
        return rightRotate(root);

    // RR Case
    if (balance < -1 &&
        value > root->right->data)
        return leftRotate(root);

    // LR Case
    if (balance > 1 &&
        value > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Case
    if (balance < -1 &&
        value < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Inorder Traversal
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);

        cout << root->data
             << "(BF=" << getBalance(root) << ") ";

        inorder(root->right);
    }
}

// Preorder Traversal
void preorder(Node* root) {
    if (root != NULL) {
        cout << root->data
             << "(BF=" << getBalance(root) << ") ";

        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder Traversal
void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);

        cout << root->data
             << "(BF=" << getBalance(root) << ") ";
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

        cout << current->data
             << "(BF=" << getBalance(current) << ") ";

        if (current->left != NULL)
            q.push(current->left);

        if (current->right != NULL)
            q.push(current->right);
    }
}

// Store inorder values in a vector
void storeInorder(Node* root, vector<int>& values) {
    if (root == NULL)
        return;

    storeInorder(root->left, values);
    values.push_back(root->data);
    storeInorder(root->right, values);
}

// Verify sorted inorder traversal
bool verifySorted(Node* root) {
    vector<int> values;

    storeInorder(root, values);

    for (int i = 1; i < (int)values.size(); i++) {
        if (values[i] <= values[i - 1])
            return false;
    }

    return true;
}

// Display all traversals
void displayTraversals(Node* root) {
    if (root == NULL) {
        cout << "\nTree is empty.\n";
        return;
    }

    cout << "\nInorder Traversal:\n";
    inorder(root);

    cout << "\n\nPreorder Traversal:\n";
    preorder(root);

    cout << "\n\nPostorder Traversal:\n";
    postorder(root);

    cout << "\n\nLevel Order Traversal:\n";
    levelOrder(root);

    cout << "\n";
}

int main() {
    Node* root = NULL;
    int n, value, choice;

    cout << "====================================\n";
    cout << " AVL TREE TRAVERSAL SYSTEM\n";
    cout << "====================================\n";

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

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Display All Traversals\n";
        cout << "2. Insert Additional Values\n";
        cout << "3. Verify Inorder Sorted Order\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                displayTraversals(root);
                break;

            case 2: {
                int count;

                cout << "How many values to insert? ";
                cin >> count;

                if (count <= 0) {
                    cout << "Enter a positive count.\n";
                    break;
                }

                cout << "Enter " << count
                     << " new values:\n";

                for (int i = 0; i < count; i++) {
                    cin >> value;
                    root = insert(root, value);
                }

                cout << "Tree updated successfully.\n";
                break;
            }

            case 3:
                if (root == NULL) {
                    cout << "FAIL: Tree is empty.\n";
                }
                else if (verifySorted(root)) {
                    cout << "PASS: Inorder traversal "
                         << "is sorted.\n";
                }
                else {
                    cout << "FAIL: Inorder traversal "
                         << "is not sorted.\n";
                }
                break;

            case 4:
                cout << "Exiting program. Thank you!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}