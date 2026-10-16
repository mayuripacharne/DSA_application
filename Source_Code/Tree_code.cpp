#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    string word, meaning, synonym, antonym;
    Node *left, *right;
    int height;

    Node(string w, string m, string s, string a) {
        word = w;
        meaning = m;
        synonym = s;
        antonym = a;
        left = right = NULL;
        height = 1;
    }
};

string lowerCase(string s) {
    for (int i = 0; i < (int)s.length(); i++)
        s[i] = tolower((unsigned char)s[i]);
    return s;
}

int getHeight(Node *n) {
    if (n == NULL) return 0;
    return n->height;
}

int balance(Node *n) {
    if (n == NULL) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

void updateHeight(Node *n) {
    if (n != NULL)
        n->height = 1 + max(getHeight(n->left),
                            getHeight(n->right));
}

Node* rotateRight(Node *y) {
    Node *x = y->left;
    Node *t = x->right;

    x->right = y;
    y->left = t;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* rotateLeft(Node *x) {
    Node *y = x->right;
    Node *t = y->left;

    y->left = x;
    x->right = t;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// BST insertion
Node* insertBST(Node *root, string w, string m,
                string s, string a) {
    if (root == NULL)
        return new Node(w, m, s, a);

    if (lowerCase(w) < lowerCase(root->word))
        root->left = insertBST(root->left, w, m, s, a);
    else if (lowerCase(w) > lowerCase(root->word))
        root->right = insertBST(root->right, w, m, s, a);

    return root;
}

// AVL insertion
Node* insertAVL(Node *root, string w, string m,
                string s, string a) {
    if (root == NULL)
        return new Node(w, m, s, a);

    if (lowerCase(w) < lowerCase(root->word))
        root->left = insertAVL(root->left, w, m, s, a);
    else if (lowerCase(w) > lowerCase(root->word))
        root->right = insertAVL(root->right, w, m, s, a);
    else
        return root;

    updateHeight(root);
    int b = balance(root);

    if (b > 1 && lowerCase(w) < lowerCase(root->left->word))
        return rotateRight(root);

    if (b < -1 && lowerCase(w) > lowerCase(root->right->word))
        return rotateLeft(root);

    if (b > 1 && lowerCase(w) > lowerCase(root->left->word)) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (b < -1 && lowerCase(w) < lowerCase(root->right->word)) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Search
Node* search(Node *root, string w, int &count) {
    w = lowerCase(w);

    while (root != NULL) {
        count++;

        if (w == lowerCase(root->word))
            return root;

        if (w < lowerCase(root->word))
            root = root->left;
        else
            root = root->right;
    }

    return NULL;
}

// Inorder traversal
void inorder(Node *root) {
    if (root == NULL) return;

    inorder(root->left);
    cout << root->word << " - " << root->meaning << endl;
    inorder(root->right);
}

// Preorder traversal
void preorder(Node *root) {
    if (root == NULL) return;

    cout << root->word << " ";
    preorder(root->left);
    preorder(root->right);
}

// Postorder traversal
void postorder(Node *root) {
    if (root == NULL) return;

    postorder(root->left);
    postorder(root->right);
    cout << root->word << " ";
}

int countWords(Node *root) {
    if (root == NULL) return 0;

    return 1 + countWords(root->left)
             + countWords(root->right);
}

Node* minimumNode(Node *root) {
    while (root != NULL && root->left != NULL)
        root = root->left;

    return root;
}

Node* maximumNode(Node *root) {
    while (root != NULL && root->right != NULL)
        root = root->right;

    return root;
}

// BST deletion
Node* deleteBST(Node *root, string w) {
    if (root == NULL) return NULL;

    w = lowerCase(w);

    if (w < lowerCase(root->word))
        root->left = deleteBST(root->left, w);
    else if (w > lowerCase(root->word))
        root->right = deleteBST(root->right, w);
    else {
        if (root->left == NULL) {
            Node *temp = root->right;
            delete root;
            return temp;
        }

        if (root->right == NULL) {
            Node *temp = root->left;
            delete root;
            return temp;
        }

        Node *temp = minimumNode(root->right);

        root->word = temp->word;
        root->meaning = temp->meaning;
        root->synonym = temp->synonym;
        root->antonym = temp->antonym;

        root->right = deleteBST(root->right, temp->word);
    }

    return root;
}

// AVL deletion
Node* deleteAVL(Node *root, string w) {
    if (root == NULL) return NULL;

    w = lowerCase(w);

    if (w < lowerCase(root->word))
        root->left = deleteAVL(root->left, w);
    else if (w > lowerCase(root->word))
        root->right = deleteAVL(root->right, w);
    else {
        if (root->left == NULL || root->right == NULL) {
            Node *temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }

        Node *temp = minimumNode(root->right);

        root->word = temp->word;
        root->meaning = temp->meaning;
        root->synonym = temp->synonym;
        root->antonym = temp->antonym;

        root->right = deleteAVL(root->right, temp->word);
    }

    updateHeight(root);
    int b = balance(root);

    if (b > 1 && balance(root->left) >= 0)
        return rotateRight(root);

    if (b > 1 && balance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (b < -1 && balance(root->right) <= 0)
        return rotateLeft(root);

    if (b < -1 && balance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

int main() {
    Node *bst = NULL;
    Node *avl = NULL;
    int choice;

    do {
        cout << "\n===== SMART DICTIONARY =====\n";
        cout << "1. Add Word\n";
        cout << "2. Search Word\n";
        cout << "3. Delete Word\n";
        cout << "4. Display Words (BST)\n";
        cout << "5. Tree Traversals\n";
        cout << "6. First and Last Word\n";
        cout << "7. Compare BST and AVL\n";
        cout << "8. Tree Height and Word Count\n";
        cout << "9. Word of the Day\n";
        cout << "10. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input!\n";
            continue;
        }

        if (choice == 1) {
            string w, m, s, a;

            cout << "Enter word: ";
            cin >> ws;
            getline(cin, w);

            if (w.empty()) {
                cout << "Word cannot be empty!\n";
                continue;
            }

            int c = 0;
            if (search(bst, w, c) != NULL) {
                cout << "Word already exists!\n";
                continue;
            }

            cout << "Enter meaning: ";
            getline(cin, m);
            cout << "Enter synonym: ";
            getline(cin, s);
            cout << "Enter antonym: ";
            getline(cin, a);

            bst = insertBST(bst, w, m, s, a);
            avl = insertAVL(avl, w, m, s, a);

            cout << "Word added successfully!\n";
        }

        else if (choice == 2 || choice == 7) {
            string w;
            int bc = 0, ac = 0;

            cout << "Enter word to search: ";
            cin >> ws;
            getline(cin, w);

            Node *b = search(bst, w, bc);
            Node *v = search(avl, w, ac);

            if (b != NULL) {
                cout << "\nWord: " << b->word << endl;
                cout << "Meaning: " << b->meaning << endl;
                cout << "Synonym: " << b->synonym << endl;
                cout << "Antonym: " << b->antonym << endl;
            } else {
                cout << "Word not found!\n";
            }

            if (choice == 7) {
                cout << "BST comparisons: " << bc << endl;
                cout << "AVL comparisons: " << ac << endl;
                cout << "BST height: " << getHeight(bst) << endl;
                cout << "AVL height: " << getHeight(avl) << endl;
            }
        }

        else if (choice == 3) {
            string w;
            int c = 0;

            cout << "Enter word to delete: ";
            cin >> ws;
            getline(cin, w);

            if (search(bst, w, c) != NULL) {
                bst = deleteBST(bst, w);
                avl = deleteAVL(avl, w);
                cout << "Word deleted successfully!\n";
            } else {
                cout << "Word not found!\n";
            }
        }

        else if (choice == 4) {
            if (bst == NULL)
                cout << "Dictionary is empty. Add words first.\n";
            else {
                cout << "\nWords in alphabetical order:\n";
                inorder(bst);
            }
        }

        else if (choice == 5) {
            if (bst == NULL) {
                cout << "Dictionary is empty.\n";
                continue;
            }

            cout << "\nBST Inorder: ";
            inorder(bst);

            cout << "\nBST Preorder: ";
            preorder(bst);

            cout << "\nBST Postorder: ";
            postorder(bst);

            cout << "\n\nAVL Inorder: ";
            inorder(avl);

            cout << "\nAVL Preorder: ";
            preorder(avl);

            cout << "\nAVL Postorder: ";
            postorder(avl);

            cout << endl;
        }

        else if (choice == 6) {
            Node *first = minimumNode(bst);
            Node *last = maximumNode(bst);

            if (first != NULL && last != NULL) {
                cout << "First word: " << first->word << endl;
                cout << "Last word: " << last->word << endl;
            } else {
                cout << "Dictionary is empty.\n";
            }
        }

        else if (choice == 8) {
            cout << "Total words: " << countWords(bst) << endl;
            cout << "BST height: " << getHeight(bst) << endl;
            cout << "AVL height: " << getHeight(avl) << endl;
        }

        else if (choice == 9) {
            cout << "Word of the Day: Resilient\n";
            cout << "Meaning: Able to recover from difficulties.\n";
        }

        else if (choice == 10) {
            cout << "Thank you for using Smart Dictionary!\n";
        }

        else if (choice < 1 || choice > 10) {
            cout << "Invalid choice!\n";
        }

    } while (choice != 10);

    return 0;
}