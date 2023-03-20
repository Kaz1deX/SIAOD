#include <iostream>
#include <windows.h>
using namespace std;

struct node              // Структура для представления узлов дерева
{
    int key;             // Ключ
    unsigned int height; // Высота поддерева с корнем в данном узле
    node* left;          // Указатель на левое поддерево
    node* right;         // Указатель на правое поддерево
    node(int k)          // Создание узла
    {
        key = k;
        left = nullptr;
        right = nullptr;
        height = 0;
    }
};

unsigned int height(node* p)                       // Возврат высоты
{
    return p?p->height:0;
}

int bfactor(node* p)                               // Вычисление разности между высотами левого и правого поддерева
{
    return height(p->right)- height(p->left);
}

void fixheight(node* p)                            // Восстановление корректного значения поля height заданного узла
{
    unsigned int hl = height(p->left);
    unsigned int hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

node* rotateright(node* p) // Правый поворот вокруг p
{
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node* rotateleft(node* q) // Левый поворот вокруг q
{
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node* balance(node* p) // Балансировка узла p
{
    fixheight(p);
    if(bfactor(p)==2)
    {
        if(bfactor(p->right) < 0)
        {
            p->right = rotateright(p->right);
        }
        return rotateleft(p);
    }
    if(bfactor(p)==-2)
    {
        if(bfactor(p->left) > 0)
        {
            p->left = rotateleft(p->left);
        }
        return rotateright(p);
    }
    return p; // Балансировка не нужна
}

node* insert(node* p, int k) // Вставка ключа k в дерево с корнем p
{
    if(!p)
    {
        return new node(k);
    }
    if(k<(p->key))
    {
        p->left = insert(p->left,k);
    }
    else
    {
        p->right = insert(p->right,k);
    }
    return balance(p);
}

node* findmin(node* p) // Поиск узла с минимальным ключом в дереве p
{
    return p->left?findmin(p->left):p;
}

node* removemin(node* p) // Удаление узла с минимальным ключом из дерева p
{
    if(p->left == 0)
    {
        return p->right;
    }
    p->left = removemin(p->left);
    return balance(p);
}

node* remove(node* p, int k) // Удаление ключа k из дерева p
{
    if(!p)
    {
        return 0;
    }
    if(k < p->key)
    {
        p->left = remove(p->left,k);
    }
    else if(k > p->key)
    {
        p->right = remove(p->right,k);
    }
    else
    {
        node* q = p->left;
        node* r = p->right;
        delete p;
        if(!r)
        {
            return q;
        }
        node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

void inorder(node **p) // Симметричный обход
{
    if((*p) != NULL)
    {
        inorder(&(*p)->left);
        cout << (*p)->key << " ";
        inorder(&(*p)->right);
    }
}

void postorder(node **p) // Обратный обход
{
    if((*p) != NULL)
    {
        postorder(&(*p)->left);
        postorder(&(*p)->right);
        cout << (*p)->key << " ";
    }
}

void summ_lists(node **p, int &sum)
{
    if((*p) != NULL)
    {
        summ_lists(&(*p)->left, sum);
        summ_lists(&(*p)->right, sum);
        if(((*p)->left == 0) and ((*p)->right == 0))
        {
            sum += (*p)->key;
        }
    }
}

void out(node * root, int space = 0) {
    if (!root)
        return;
    //формирование текущего отступа
    space += 2;
    out(root->right, space);
    for (int i = 2; i < space; ++i)
        cout << "//";
    cout << root->key << endl;
    out(root->left, space);
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    //node main_node(20);
    //node *p = &main_node;

    node *p = NULL;
    int n;
    int s;
    int sum = 0;
    for (int i = 0; i < 10; ++i)
    {
        cin >> s;
        p = insert(p, s);
    }
    //inorder(&p);

    out(p);

    return 0;
}