#include<bits/stdc++.h>
#define inf INT_MAX
using namespace std;

//Insert(H,x)
//Minimum(H)
//Extract_Min(H)
//Union(H1,H2)
//Decrease_Key(H,x,k)
//Delete(H,x)

struct Node
{
    int data;
	int degree;
    Node *child, *sibling, *parent;
};

Node *newNode(int key)
{
	Node *temp=new Node;
	temp->data=key;
	temp->degree=0;
	temp->child=temp->parent=temp->sibling=NULL;
	return temp;
}

list<Node*> Merge(list<Node*> l1,list<Node*> l2)
{
	list<Node*> nHeap;
	list<Node*> :: iterator i=l1.begin();
	list<Node*> :: iterator j=l2.begin();
	
	while( i!=l1.end() && j!=l2.end())
	{
		if( (*i)->degree <= (*j)->degree )
		{
			nHeap.push_back(*i);
			i++;
		}
		else
		{
			nHeap.push_back(*j);
			j++;
		}
	}
	while( i!=l1.end() )
	{
		nHeap.push_back(*i);
		i++;
	}
	while( j!=l2.end() )
	{
		nHeap.push_back(*j);
		j++;
	}
	return nHeap;
}

Node* Link(Node *b1, Node *b2)
{
    if (b1->data > b2->data)
        swap(b1, b2);
    b2->parent=b1;
    b2->sibling=b1->child;
    b1->child=b2;
    b1->degree++;
    return b1;
}

list<Node*> Union(list<Node*> heap,list<Node*> heap2)
{
	heap=Merge(heap,heap2);
	if(heap.size() <= 1)
		return heap;
	list<Node*> nHeap;
	list<Node*> :: iterator it1=heap.begin(),it2=heap.begin(),it3=heap.begin();
	if(heap.size()==2)
	{
		it2=it1;
		it2++;
		it3=heap.end();
	}
	else
	{
		it2++;
        it3=it2;
        it3++;
	}
	while( it1!=heap.end() )
	{
		if(it2==heap.end())
			it1++;
		else if( (*it1)->degree < (*it2)->degree )
		{
			it1++;
			it2++;
			if(it3!=heap.end())
				it3++;
		}
		else if(it3!=heap.end() && (*it1)->degree == (*it2)->degree && (*it2)->degree == (*it3)->degree)
		{
			it1++;
			it2++;
			it3++;
		}
		else if( (*it1)->degree == (*it2)->degree )
		{
			Node *temp;
			*it1=Link(*it1,*it2);
			it2=heap.erase(it2);
            if(it3!=heap.end())
                it3++;
		}
	}
	return heap;
}

list<Node*> Insert(list<Node*> heap,int key)
{
	Node *temp=newNode(key);
	list<Node*> nHeap;
	nHeap.push_back(temp);
	return Union(heap,nHeap);
}

Node* getMin(list<Node*> heap)
{
	list<Node*> :: iterator it=heap.begin();
	Node *temp=*it;
	while(it!=heap.end())
	{
		if( (*it)->data < temp->data )
			temp=*it;
		it++;
	}
	return temp;
}

list<Node*> removeElement(Node *root)
{
	list<Node*> heap;
	Node *temp=root->child;
	Node *lo=temp;
	while(temp)
	{
		lo=temp;
		temp=temp->sibling;
		lo->sibling=NULL;
		heap.push_front(lo);
	}
	return heap;
}

list<Node*> ExtractMin(list<Node*> heap)
{
	Node *temp=getMin(heap);
	list<Node*> nHeap,sHeap;
	list<Node*> :: iterator it=heap.begin();
	while( it!=heap.end() )
	{
		if( (*it)!=temp )
			nHeap.push_back(*it);
		it++;
	}
	sHeap=removeElement(temp);
	nHeap=Union(nHeap,sHeap);
	return nHeap;
}

void printRootList(Node *root)
{
	while(root!=NULL)
	{
		cout<<root->data<<" ";
		printRootList(root->child);
		root=root->sibling;
	}
}

void printHeap(list<Node*> heap)
{
	list<Node*> :: iterator it;
	it=heap.begin();
	while( it!=heap.end() )
	{
		printRootList(*it);
		it++;
	}
}

void findInRoot(Node *root,int key,Node *&temp)
{
	while(root!=NULL)
	{
		if(root->data==key)
		{
			temp=root;
			return;
		}
		findInRoot(root->child,key,temp);
		root=root->sibling;
	}
	return;
}

void find(list<Node*> heap,int key,Node *&temp)
{
	list<Node*> :: iterator it;
	it=heap.begin();
	while( it!=heap.end() )
	{
		findInRoot(*it,key,temp);
		if(temp!=NULL)
		return;
		it++;
	}
	return;
}

list<Node*> DecreaseKey(list<Node*> heap,int key,int val)
{
	Node *x=NULL;
	find(heap,key,x);
	if(x==NULL)
	{
		cout<<"Key Not Found in the heap\n";
		return heap;
	}
	if(val>key)
	{
		cout<<"Value to update should be less than the original one\n";
		return heap;
	}
	x->data=val;
	Node *y=x;
	Node *z=y->parent;
	while( z!=NULL && z->data > y->data)
	{
		swap(z->data,y->data);
		y=z;
		z=y->parent;
	}
	cout<<"Done!\n";
	return heap;
}

list<Node*> Delete(list<Node*> heap,int key)
{
	Node *temp=NULL;
	find(heap,key,temp);
	if(temp==NULL)
	{
		cout<<"Value Not Found\n";
		return heap;
	}
	heap=DecreaseKey(heap,key,-1*inf);
	heap=ExtractMin(heap);
	return heap;
}

int main()
{
	list<Node*> heap;
	int choice,key,val;
	while(1)
	{
		cout<<"\n1.Insert\n2.PrintHeap\n3.GetMin\n4.ExtractMin\n5.DecreaseKey\n6.Delete Key\n7.Exit\n";
		cout<<"Enter Your Choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"Enter Key To insert : ";
				cin>>key;
				heap=Insert(heap,key);
				cout<<key<<" Successfully Inserted in heap.\n";
				break;
			case 2:
				cout<<"Heap is-\n";
				printHeap(heap);
				cout<<endl;
				break;
			case 3:
				cout<<"Minimum key in the heap is "<<getMin(heap)->data<<endl;
				break;
			case 4:
				heap=ExtractMin(heap);
				cout<<"Minimum Key is Deleted.\n";
				break;
			case 5:
				cout<<"Enter Key To change its value: ";
				cin>>key;
				cout<<"Enter New Value: ";
				cin>>val;
				heap=DecreaseKey(heap,key,val);
				break;
			case 6:
				cout<<"Enter Value To Delete: ";
				cin>>key;
				heap=Delete(heap,key);
				break;
			case 7:
				cout<<"\nThanks.\n";
				return 0;
			default:
				cout<<"Invalid Entry\n";
				break;
		}
	}
}

