
///Inserare
#include <bits/stdc++.h>
using namespace std;

// Clasa prin care implementam un nod
class Node
{
public:
    int key;
    Node **forward;
    Node(int, int);

};

Node::Node(int key, int level)
{
    this->key = key;

    // Alocam memorie pt forward
    forward = new Node*[level+1];

    // Vom umple blocul de memorie din forward cu 0-uri
    memset(forward, 0, sizeof(Node*)*(level+1));
};

// Clasa pentru skip-list
class SkipList
{
    int MAXLVL;
    // P- secventa de noduri de nivel i care au i+1 pointeri
    float P;
    // level- nivelul curent din skip-list
    int level;
    // pointer catre header-node (nodul de la inceputul listei)
    Node *header;
public:
    SkipList(int, float);
    int randomLevel();
    Node* createNode(int, int);
    void insertElement(int);
    void deleteElement(int);
    void searchElement(int);
    void displayList();
    Node* predecesor(int);
    Node* succesor(int);
};

SkipList::SkipList(int MAXLVL, float P)
{
    this->MAXLVL = MAXLVL;
    this->P = P;
    level = 0;

    // cream header-node-ul si il initializam cu -1
    header = new Node(-1, MAXLVL);
};

// cream un randomLevel pt nod
int SkipList::randomLevel()
{
    float r = (float)rand()/RAND_MAX;
    int lvl = 0;
    while (r < P && lvl < MAXLVL)
    {
        lvl++;
        r = (float)rand()/RAND_MAX;
    }
    return lvl;
};

// crearea unui nod nou
Node* SkipList::createNode(int key, int level)
{
    Node *n = new Node(key, level);
    return n;
};

// Inseram cheia data in skip-list
void SkipList::insertElement(int key)
{
    Node *current = header;

    // cream un update-array si il initializam
    Node *update[MAXLVL+1];
    memset(update, 0, sizeof(Node*)*(MAXLVL+1));

    for (int i = level; i >= 0; i--)
    {
        while (current->forward[i] != NULL &&
              current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }
    current = current->forward[0];

    if (current == NULL || current->key != key)
    {
        int rlevel = randomLevel();
        if (rlevel > level)
        {
            for (int i=level+1;i<rlevel+1;i++)
                update[i] = header;

            // Updatam lista la nivelul curent
            level = rlevel;
        }

        // cream un nod nou la un nivel random
        Node* n = createNode(key, rlevel);
        for (int i=0;i<=rlevel;i++)
        {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }
        cout << "Ai inserat cheia cu succes! " << key << "\n";
    }
};
// Stergerea unui element din Skiplist
void SkipList::deleteElement(int key)
{
    Node *current = header;
    Node *update[MAXLVL+1];
    memset(update, 0, sizeof(Node*)*(MAXLVL+1));
    for(int i = level; i >= 0; i--)
    {
        while(current->forward[i] != NULL  &&
              current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }
    current = current->forward[0];
    if(current != NULL and current->key == key)
    {
        for(int i=0;i<=level;i++)
        {
            if(update[i]->forward[i] != current)
                break;

            update[i]->forward[i] = current->forward[i];
        }

        // Stergem nivelurile care nu contin niciun element
        while(level>0 &&
              header->forward[level] == 0)
            level--;
         cout<<"Successfully deleted key "<<key<<"\n";
    }
};

// Cautarea unui element in Skiplist
void SkipList::searchElement(int key)
{
    Node *current = header;
    for(int i = level; i >= 0; i--)
    {
        while(current->forward[i] &&
               current->forward[i]->key < key)
            current = current->forward[i];

    }
    current = current->forward[0];
    if(current and current->key == key)
        cout<<"Found key: "<<key<<"\n";
};
// Predecesor
Node *SkipList::predecesor(int key)
{
    Node *current = header;
    if (key < current -> key)
        return nullptr;
    for (int i = level; i >= 0; i--)
    {
      while(current->forward[i] &&
               current->forward[i]->key < key)
            current = current->forward[i];
    }
    return current;

}
// Succesor
Node *SkipList::succesor(int key)
{
    Node *current = header;
    for (int i = level; i >= 0; i--)
    {
      while(current->forward[i] &&
               current->forward[i]->key < key)
            current = current->forward[i];
    }
    if( current == nullptr || current -> key == key)
        return current;
     current = current->forward[0];
     return current;
}
// Afisarea pe nivele
void SkipList::displayList()
{
    cout<<"\n*****Skip List*****"<<"\n";
    for (int i=0;i<=level;i++)
    {
        Node *node = header->forward[i];
        cout << "Level " << i << ": ";
        while (node != NULL)
        {
            cout << node->key<<" ";
            node = node->forward[i];
        }
        cout << "\n";
    }
};

// Testarea codului
int main()
{
    srand((unsigned)time(0));

    SkipList lst(4, 0.5);

    lst.insertElement(3);
    lst.insertElement(6);
    lst.insertElement(7);
    lst.insertElement(9);
    lst.insertElement(12);
    lst.insertElement(19);
    lst.insertElement(17);
    lst.insertElement(26);
    lst.insertElement(21);
    lst.insertElement(14);
    lst.insertElement(15);
    lst.insertElement(16);
    lst.insertElement(17);
    lst.displayList();

    lst.searchElement(19);
    lst.deleteElement(19);
    lst.displayList();
//Nu am inteles cerinta cu afisare elemente sortat, insa elementele mele indiferent in ce ordine sunt inserate acestea
//vor fi afisate in ordine
}
