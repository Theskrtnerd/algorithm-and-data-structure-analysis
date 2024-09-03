#include <iostream>
#include <unordered_set>
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
        AVLTree() {
            root = nullptr;
        }
        TreeNode* insertNode(TreeNode* node, int val) {
            if(s.find(val) != s.end()) return;
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
        TreeNode* removeNode(int val) {
            if(s.find(val) == s.end()) return;
            s.erase(val);
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
        void printTree(string type) {

        }
        unordered_set<int> s;
};

int main() {

    return 0;
}