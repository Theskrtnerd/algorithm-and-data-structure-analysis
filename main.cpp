#include <iostream>
#include <unordered_set>
#include <sstream>
using namespace std;

class TreeNode {
    public:
        TreeNode* left;
        TreeNode* right;
        int height;
        int bal;
        int value;
        TreeNode(int value) {
            this->value = value;
            this->left = nullptr;
            this->right = nullptr;
            this->height = 1;
            this->bal = 0;
        };
};

class AVLTree {
    public:
        TreeNode* root;
        unordered_set<int> s;
        AVLTree() {
            root = nullptr;
        }
        TreeNode* insertNode(TreeNode* node, int val) {
            if(s.find(val) != s.end()) return node;
            if (node == nullptr) {
                node = new TreeNode(val);
                s.insert(val);
                return node;
            }
            if (val < node->value) {
                node->left = insertNode(node->left, val);
            }
            else if(val > node->value) {
                node->right = insertNode(node->right, val);
            }
            updateNode(node);
            if(node->bal > 1) {
                if (val < node->left->value) {
                    return rightRotate(node);
                }
                else if (val > node->left->value) {
                    node->left = leftRotate(node->left);
                    return rightRotate(node);
                }
            }
            else if (node->bal < -1) {
                if (val > node->right->value) {
                    return leftRotate(node);
                }
                else if (val < node->right->value) {
                    node->right = rightRotate(node->right);
                    return leftRotate(node);
                }
            }
            return node;
        };
        TreeNode* removeNode(TreeNode* node, int val) {
            if(s.find(val) == s.end()) return node;
            if(val < node->value) {
                node->left = removeNode(node->left, val);
            }
            else if(val > node->value) {
                node->right = removeNode(node->right, val);
            }
            else {
                if(!node->left && !node->right) {
                    s.erase(val);
                    node = nullptr;
                }
                else if (node->left && node->right) {
                    TreeNode* temp = node->right;
                    while(temp->left) {
                        temp = temp->left;
                    }
                    node->value = temp->value;
                    temp = temp->right;
                    s.erase(val);
                }
                else {
                    s.erase(val);
                    TreeNode* temp = node->left ? node->left : node->right;
                    node = temp;
                    delete temp;
                }
            }

            if (!node) return node;
            updateNode(node);
            if (node->bal > 1) {
                if (node->left->bal >= 0) {
                    return rightRotate(node);
                }
                else {
                    node->left = leftRotate(node->left);
                    return rightRotate(node);
                }
            }
            if (node->bal < -1) {
                if (node->right->bal <= 0) {
                    return leftRotate(node);
                }
                else {
                    node->right = rightRotate(node->right);
                    return leftRotate(node);
                }
            }

            return node;
        };
        void updateNode(TreeNode* node) {
            int hL =0, hR =0;
            if(node->left) {
                hL = node->left->height;
            }
            if(node->right) {
                hR = node->right->height;
            }
            node->height = 1 + max(hL, hR); 
            node->bal = hL-hR;
            return;
        }
        TreeNode* leftRotate(TreeNode* node) {
            TreeNode *nodeR = node->right; 
            TreeNode *nodeRL = nodeR->left; 
            nodeR->left = node; 
            node->right = nodeRL;
            this->updateNode(node);
            this->updateNode(nodeR);
            return nodeR; 
        }
        TreeNode* rightRotate(TreeNode* node) {
            TreeNode *nodeL = node->left; 
            TreeNode *nodeLR = nodeL->right; 
            nodeL->right = node; 
            node->left = nodeLR;
            this->updateNode(node);
            this->updateNode(nodeL);
            return nodeL; 
        }
        void printTree(TreeNode* node, string type) {
            if (s.empty()) {
                cout << "EMPTY" << endl;
                return;
            }
            if(type == "PRE") {
                if (!node) return;
                cout << node->value << " ";
                if (node->left) printTree(node->left, type);
                if (node->right) printTree(node->right, type);
            }
            else if (type == "POST") {
                if (!node) return;
                if (node->left) printTree(node->left, type);
                if (node->right) printTree(node->right, type);
                cout << node->value << " ";
            }
            else if (type == "IN") {
                if (!node) return;
                if (node->left) printTree(node->left, type);
                cout << node->value << " ";
                if (node->right) printTree(node->right, type);
            }
        }
};

int main() {
    AVLTree* mytree = new AVLTree();
    string input;
    getline(cin, input);
    stringstream ss(input);
    string word;
    while (ss >> word) {
        if (word[0] == 'A') {
            int x = stoi(word.substr(1));
            mytree->root = mytree->insertNode(mytree->root, x);
        } else if (word[0] == 'D') {
            int x = stoi(word.substr(1));
            mytree->root = mytree->removeNode(mytree->root, x);
        } else {
            // Process the final word for printTree(x)
            if (word == "IN" || word == "PRE" || word == "POST") {
                mytree->printTree(mytree->root, word);
            }
        }
    }

    return 0;
}