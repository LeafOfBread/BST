#include <iostream>
#include <fstream>

using namespace std;

struct tree
{
    int numbers;
    tree* left;
    tree* right;
};

tree* newtree(int data)
{
    tree* newNode = new tree();
    newNode->numbers = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;

}

tree* insert(tree* root, int data)
{
    if (root == NULL)
    {
        root = newtree(data);
        cout << "new node initialized\n";
    }
    else if (data <= root->numbers)
    {
        cout << "left\n";
        root->left = insert(root->left, data);
    }
    else if (data > root->numbers)
    {
        cout << "right\n";
        root->right = insert(root->right, data);
    }
    return root;
}

bool search(tree* root, int data)
{
    if (root==NULL) return false;
    else if (root->numbers == data) return true;
    else if (data <= root->numbers) return search(root->left, data);
    else return search(root->right, data);
}

int main()
{
    tree* root = NULL;
    ifstream inputFile("bst.txt");
    if (!inputFile)
    {
        cout << "File could not be read!\n";
        return 1;
    }

    int num;

    while (inputFile >> num)
    {
        root = insert(root, num);
    }
    inputFile.close();

    cout << "What Integer would you like to search for?\n";
    int input;
    cin >> input;

    if (search(root, input)==true) cout << "Integer has been found!";
    else cout << "Integer has not been found!";
    return 0;
}
