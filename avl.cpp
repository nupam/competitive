#include <iostream>
#include <cstdio>
using std::cin;
using std::cout;
using std::endl;


int max(const int& a, const int& b){
    return a>b?a:b;
}

class node{
public:
    node* l, *r;
    int v;
    node(int v=0, node* l = NULL, node* r = NULL): v(v), l(l), r(r) { }
}*root;

class avl{
public:
    //node* root;
    //int s;
    int height(node* n);
    int bf(node* n);
    node* ll(node*);
    node* lr(node*);
    node* rr(node*);
    node* rl(node*);
    node* bal(node*);
    node* insert(node *, const int& );
    void display(node *ptr, int level);
    avl(){root = NULL;}
};


int main()

{

    int choice, item;

    avl a;

    while (1)
    {

        cout<<"\n---------------------"<<endl;

        cout<<"AVL Tree Implementation"<<endl;

        cout<<"\n---------------------"<<endl;

        cout<<"1.Insert Element into the tree"<<endl;

        cout<<"2.Display Balanced AVL Tree"<<endl;

        cout<<"3.InOrder traversal"<<endl;

        //cout<<"4.PreOrder traversal"<<endl;

        //cout<<"5.PostOrder traversal"<<endl;

        cout<<"6.Exit"<<endl;

        cout<<"Enter your Choice: ";

        cin>>choice;

        switch(choice)

        {

        case 1:

            cout<<"Enter value to be inserted: ";

            cin>>item;

            root = a.insert(root, item);

            break;

        case 2:

            if (root == NULL)

            {

                cout<<"Tree is Empty"<<endl;

                continue;

            }

            cout<<"Balanced AVL Tree:"<<endl;

            a.display(root, 1);

            break;

        case 6:

            break;

        default:

            cout<<"Wrong Choice"<<endl;

        }

    }

    return 0;

}


int avl::height(node* n){
    if(!n)
        return 0;
    return (max(height(n->l), height(n->r)) + 1);
}

int avl::bf(node* n){
    return (height(n->l) - height(n->r));
}

node* avl::ll(node* p){
    node* temp = p->l;
    p->l = temp->r;
    temp->r = p;
    return temp;
}

node* avl::rr(node* p){
    node* temp = p->r;
    p->r = temp->l;
    temp->l = p;
    return temp;
}

node* avl::rl(node* p){
    p->r = ll(p->r);
    return rr(p);
}

node* avl::lr(node* p){
    p->l = rr(p->l);
    return ll(p);
}

node* avl::bal(node* n){
    int f = bf(n);
    if(f>1){
        if(bf(n->l) > 0)
            return ll(n);
        else
            return lr(n);
    }
    else if(f < -1){
        if(bf(n->r) < 0)
            return rr(n);
        else
            return rl(n);
    }
    return n;
}

node* avl::insert(node* root, const int& v){
    if(!root){
        //root = ;
        return new node(v);
    }
    if(root->v < v){
        root->r = insert(root->r, v);
        root = bal(root);
    }
    else{
        root->l = insert(root->l, v);
        root = bal(root);
    }
    return root;
}

void avl::display(node *ptr, int level){

    int i;
    if (ptr!=NULL){
        display(ptr->r, level + 1);
        printf("\n");
        if (ptr == root)
        cout<<"Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout<<"        ";
        cout<<ptr->v;
        display(ptr->l, level + 1);
    }
}


