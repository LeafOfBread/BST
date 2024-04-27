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
    if (root->numbers != data){ //liest zwei gleiche zahlen nicht ein
    if (data < root->numbers) root->left = insertTree(root->left, data);   //links weiter
    else if (data > root->numbers) root->right = insertTree(root->right, data); //rechts weiter
    }
    return root;
}

int minimum(tree* root)
{   //solange links traversen wie moeglich = kleinste zahl
    if (root == NULL) cout << "Tree is empty!\n";
    else if (root->left == NULL) return root->numbers;
    return minimum(root->left);
}

int maximum(tree* root)
{   //solange rechts traversen wie moeglich = groeﬂte zahl
    if (root == NULL) cout << "Tree is empty!\n";
    else if (root->right == NULL) return root->numbers;
    return maximum(root->right);
}

int nodeCounter(tree* root)
{   //zaehlt fuer jeden node +1, ergibt anzahl aller nodes zusammen
    if (root == NULL) return 0;
    return nodeCounter(root->left) + nodeCounter(root->right) +1;
}

int sum(tree* root)
{   //zaehlt rekursiv alle numbers der nodes zusammen
    if (root == NULL) return 0;
    return sum(root->left) + sum(root->right) + root->numbers;
}

bool searchTree(tree* root, int data, bool* searchCheck)
{   //falls null
    if (root==NULL)
    {
        cout << data << " not found!\n";
        *searchCheck = false;
        return false;
    }
    else if (root->numbers == data) //wenn zahlen uebereinstimmen, zahl gefunden
    {
        cout << data << " found ";
        *searchCheck = true;    //check auf true fuer path funktion
        return true;
    }
    else if (data < root->numbers) return searchTree(root->left, data, searchCheck); //falls kleiner, am linken node weitersuchen
    else return searchTree(root->right, data, searchCheck); //falls groesser, am rechten node weitersuchen
}

void path(tree* root, int data)
{
    if (root==NULL) cout << "not present!\n";
    else if (root->numbers == data) //falls gefunden, print number
    {
        cout << root->numbers << "\n";
        return; //breche funktion ab
    }
    else if (data < root->numbers)  //wenn kleiner, suche links weiter, und printe den "zwischen-node"
    {
        cout << root->numbers << ", ";
        return path(root->left, data);
    }
    else    //wenn groesser, suche rechts weiter und printe den "zwischen-node"
    {
        cout << root->numbers << ", ";
        return path(root->right, data);
    }
}

void deleteTree(tree* root)
{
    if (root != NULL)   //solange nicht leer, suche links und rechts weiter
    {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;    //loesche von unten nach oben alle nodes
    }
}

int depth(tree* root)
{
    if (root == NULL) return 0;
    int left = depth(root->left);
    int right = depth(root->right);
    return max(left, right) +1; //gib die laengste tiefe des baumes aus +1
}

bool check_if_subtree(tree* Starting_Point,tree* End_Point)
{
    if(Starting_Point->numbers==End_Point->numbers&&Starting_Point!=NULL) return true;
    if(Starting_Point->left==NULL&&Starting_Point->right==NULL) return false;
    else
    {   //links und rechts weiter checken
        return(check_if_subtree(Starting_Point->left,End_Point));
        return(check_if_subtree(Starting_Point->right,End_Point));
    }
}

void printTree(tree* root)
{   //debugging - printed alle nodes' values
    if (root == nullptr) return;
    printTree(root->right);
    cout << root->numbers << " ";
    printTree(root->left);
}

int main()
{
    tree* root = nullptr;   //root initializen und auf null setzen

    ifstream inputFile("bst1.txt");
    if (!inputFile)
    {
        cout << "File could not be read!\n";    //error handling
        return 1;
    }
    int num;
    while (inputFile >> num)    //liest jeden wert ein und inserted in den baum
    {
        root = insertTree(root, num);
        int depthCheck = depth(root->right)-depth(root->left);  //checkt sofort die tiefe
        if (depthCheck>=2 || depthCheck <=-2) cout << "bal(" << num << ") = " << depthCheck << " (AVL Violation!)\n"; //AVL check
        else cout << "bal(" << num << ") = " << depthCheck << "\n"; //formatting
    }
    inputFile.close();  //close file again
    int depthCheck = depth(root->right)-depth(root->left); //initialize again for whole tree avl check

    double avg = (double)sum(root)/(double)nodeCounter(root);   //calculate average value
    if (depthCheck <2 && depthCheck >-2) cout << "AVL: yes\n";  //avl konform check
    else cout << "AVL: no\n";
    cout << "min: " << minimum(root) << ", max: " << maximum(root) << ", avg: " << std::fixed << std::setprecision(2) << avg << "\n\n\n";   //statistik

    bool searchCheck;   //check ob suche erfolgreich
    ifstream searchFile("bstsearch1.txt");  //liesst neues file ein zum values suchen
    if (!searchFile)
    {
        cout << "File could not be read!\n";
        return 2;
    }
    tree* subTree = nullptr;    //neuer tree ist gleich null
    int intSearch;
    while (searchFile >> intSearch)
    {
        searchTree(root, intSearch, &searchCheck);  //sucht ob integer im maintree vorhanden ist
        if (searchCheck == true) path(root, intSearch); //output path
        subTree = insertTree(subTree, intSearch);   //inserted value in neuen tree
    }
    searchFile.close();

    /*cout << "Contents of Root: "; //debugging
    printTree(root);
    cout << "\n";
    cout << "Contents of Subtree: ";
    printTree(subTree);
    cout << "\n";*/

    if(check_if_subtree(root,subTree)) cout<<"\nSubtree found."<<endl;
    else cout<<"\nSubtree not found."<<endl;

    deleteTree(root);   //trees wieder loeschen
    deleteTree(subTree);
    return 0;
}
