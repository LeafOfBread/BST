#include <iostream>

using namespace std;


struct tree{
    int numbers;
    tree* left;
    tree* right;
};

tree* newtree(int data){
    tree* newNode = new tree();
    newNode->numbers = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;

}

tree* insert(tree* root, int data){
    if (root == NULL){
        root = newtree(data);
        cout << "new node initialized\n";
    }
    else if (data <= root->numbers){
        cout << "left\n";
        root->left = insert(root->left, data);
    }
    else if (data > root->numbers){
        cout << "right\n";
        root->right = insert(root->right, data);
    }
    return root;
}

bool search(tree* root, int data){
    if (root==NULL) return false;
    else if (root->numbers == data) return true;
    else if (data <= root->numbers) return search(root->left, data);
    else return search(root->right, data);
}

int main()
{
    tree* root = NULL;
    root = insert(root, 15);
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 12);
    root = insert(root, 16);
    root = insert(root, 24);

    int input;
    cout << "Enter a number to be searched\n";
    cin >> input;
    if (search(root, input) == true) cout << "Number has been found!\n";
    else cout << "Not found in the tree!\n";
    return 0;
}
