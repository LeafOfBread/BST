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
    if (root == nullptr) root = newtree(data);  //wenn root leer, neuen baum anlegen
    if (root->numbers != data){
    if (data < root->numbers) root->left = insertTree(root->left, data);   //links weiter
    else if (data > root->numbers) root->right = insertTree(root->right, data); //rechts weiter
    }
    return root;
}

int minimum(tree* root)
{
    if (root == NULL) cout << "Tree is empty!\n";
    else if (root->left == NULL) return root->numbers;
    return minimum(root->left);
}

int maximum(tree* root)
{
    if (root == NULL) cout << "Tree is empty!\n";
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

bool searchTree(tree* root, int data, bool* searchCheck)
{
    if (root==NULL)
    {
        cout << data << " not found!\n";
        *searchCheck = false;
        return false;
    }
    else if (root->numbers == data)
    {
        cout << data << " found ";
        *searchCheck = true;
        return true;
    }
    else if (data < root->numbers) return searchTree(root->left, data, searchCheck);
    else return searchTree(root->right, data, searchCheck);
}

void path(tree* root, int data)
{
    if (root==NULL) cout << "not present!\n";
    else if (root->numbers == data)
    {
        cout << root->numbers << "\n";
        return;
    }
    else if (data < root->numbers)
    {
        cout << root->numbers << ", ";
        return path(root->left, data);
    }
    else
    {
        cout << root->numbers << ", ";
        return path(root->right, data);
    }
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

bool check_if_subtree(tree* Starting_Point,tree* End_Point)
{
    if(Starting_Point->numbers==End_Point->numbers&&Starting_Point!=NULL) return true;
    if(Starting_Point->left==NULL&&Starting_Point->right==NULL) return false;
    else
    {
        return(check_if_subtree(Starting_Point->left,End_Point));
        return(check_if_subtree(Starting_Point->right,End_Point));
    }


}

void printTree(tree* root)
{
    if (root == nullptr) return;
    printTree(root->right);
    cout << root->numbers << " ";
    printTree(root->left);
}

int main()
{
    tree* root = nullptr;
    bool searchCheck;

    ifstream inputFile("bst1.txt");
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
    cout << "min: " << minimum(root) << ", max: " << maximum(root) << ", avg: " << std::fixed << std::setprecision(2) << avg << "\n\n\n";

    ifstream searchFile("bstsearch1.txt");
    if (!searchFile)
    {
        cout << "File could not be read!\n";
        return 2;
    }
    tree* subTree = nullptr;
    int intSearch;
    while (searchFile >> intSearch)
    {
        searchTree(root, intSearch, &searchCheck);
        if (searchCheck == true) path(root, intSearch);
        subTree = insertTree(subTree, intSearch);
    }
    searchFile.close();

    cout << "Contents of Root: "; //debugging
    printTree(root);
    cout << "\n";
    cout << "Contents of Subtree: ";
    printTree(subTree);
    cout << "\n";

    if(check_if_subtree(root,subTree))
    {
        cout<<"\nSubtree found."<<endl;
    }
    else
    {
        cout<<"\nSubtree not found."<<endl;
    }

    deleteTree(root);
    deleteTree(subTree);
    return 0;
}
