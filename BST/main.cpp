#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

struct tree
{
    int numbers;
    tree* left;
    tree* right;
};

tree* newtree(int data) //neuen baum anlegen
{
    tree* newNode = new tree();
    newNode->numbers = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;

}

tree* insertTree(tree* root, int data)
{
    if (root == nullptr) root = newtree(data);
    else if (data < root->numbers) root->left = insertTree(root->left, data);
    else if (data > root->numbers) root->right = insertTree(root->right, data);
    else if (data == root->numbers) return nullptr;
    return root;
}

int minimum(tree* root)
{
    if (root == NULL) cout << "Tree is empty!";
    else if (root->left == NULL) return root->numbers;
    return minimum(root->left);
}

int maximum(tree* root)
{
    if (root == NULL) cout << "Tree is empty!";
    else if (root->right == NULL) return root->numbers;
    return maximum(root->right);
}

int nodeCounter(tree* root)
{
    if (root == NULL) return 0;
    return nodeCounter(root->left) + nodeCounter(root->right) +1;
}

int sum(tree* root)
{
    if (root == NULL) return 0;
    return sum(root->left) + sum(root->right) + root->numbers;
}

bool searchTree(tree* root, int data)
{
    if (root==NULL) return false;
    else if (root->numbers == data) return true;
    else if (data < root->numbers) return searchTree(root->left, data);
    else return searchTree(root->right, data);
}

void deleteTree(tree* root)
{
    if (root != NULL)
    {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

int depth(tree* root)
{
    if (root == NULL) return 0;
    int left = depth(root->left);
    int right = depth(root->right);
    return max(left, right) +1;
}

int main()
{
    tree* root = nullptr;

    ifstream inputFile("bst.txt");
    if (!inputFile)
    {
        cout << "File could not be read!\n";
        return 1;
    }
    int num;
    while (inputFile >> num)
    {
        root = insertTree(root, num);
        int depthCheck = depth(root->right)-depth(root->left);
        if (depthCheck>=2 || depthCheck <=-2) cout << "bal(" << num << ") = " << depthCheck << " (AVL Violation!)\n";
        else cout << "bal(" << num << ") = " << depthCheck << "\n";
    }
    inputFile.close();
    int depthCheck = depth(root->right)-depth(root->left);

    double avg = (double)sum(root)/(double)nodeCounter(root); //alter sind doubles retarded in c++, wtf..
    if (depthCheck <2 && depthCheck >-2) cout << "AVL: yes\n";
    else cout << "AVL: no\n";
    cout << "min: " << minimum(root) << ", max: " << maximum(root) << ", avg: " << std::fixed << std::setprecision(2) << avg << "\n";


    deleteTree(root);
    return 0;
}
