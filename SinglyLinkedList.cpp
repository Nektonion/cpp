#include <iostream>

/*
 * template class for singly-linked list
 */

using namespace std;

template <typename Type>
class LinkedList
{
private:

    int SIZE;

    template <typename>
    class Node
    {
    public:
        Type data;
        Node *nextNode;

        Node(Type data, Node *nextNode = nullptr)
        {
            this->data = data;
            this->nextNode = nextNode;
        }
    };

    Node<Type>* head;

public:

    LinkedList();
    ~LinkedList();

    int GetSize(){return SIZE;}

    Node<Type>* GetCurrent(int);

    void PushBack(Type);

    void PushFront(Type);

    void PopFront();

    void PopBack();

    void Insert(int, Type);

    void PopAt(int);

    Type& operator [](int);

    void Print();

    void Clear();
};

template <typename Type>
LinkedList<Type>:: LinkedList()
{
    SIZE = 0;
    head = nullptr;
}

template <typename Type>
LinkedList<Type>:: ~LinkedList()
{
    Clear();
}

template <typename Type>
LinkedList<Type>::Node<Type>* LinkedList<Type>:: GetCurrent(int index)
{
    Node<Type>* current = head;

    if(index >= SIZE || index < 0)
        cout << "GetCurent:: index is out of range" << endl;

    else if(index == (SIZE - 1) )
        while(current->nextNode != nullptr)
            current = current->nextNode;
    else
    {
        int counter = 0;
        while(counter == index)
        {
            current = current->nextNode;
            counter++;
        }
    }
    return current;
}

template <typename Type>
void LinkedList<Type>:: PushBack(Type data)
{
    if(head == nullptr)
    {
        head = new Node<Type>(data);
    }
    else
    {
        Node<Type>* current = GetCurrent(SIZE - 1);

        current->nextNode = new Node<Type>(data);
    }
    SIZE++;
}

template <typename Type>
void LinkedList<Type>:: Print()
{
    if(head == nullptr)
        cout << "Print:: List is empty" << endl;
    else
    {
        cout << "Print:: Your list" << endl;
        Node<Type>* current = head;
        while(current->nextNode != nullptr)
        {
            cout << current->data << endl;
            current = current->nextNode;
        }
        cout << current->data << endl;
    }
}

template <typename Type>
Type& LinkedList<Type>:: operator [](int index)
{
    int zero = 0;
    if(index < 0 || index >= SIZE)
    {
        cout << "index is out of range" << endl;
        return head->data;
    }
    else
    {
        Node<Type>* current = GetCurrent(index);
        return current->data;
    }
}

template<typename Type>
void LinkedList<Type>:: PopFront()
{
    if(head == nullptr)
        cout << "PopFront:: List is empty" << endl;
    else
    {
        Node<Type>* temp = head;
        head = head->nextNode;

        delete temp;
        SIZE--;
    }
}

template<typename Type>
void LinkedList<Type>:: PopBack()
{
    if(head == nullptr)
        cout << "PopBack:: List is empty" << endl;
    else
    {
        Node<Type>* current = GetCurrent(SIZE - 2); // get pre-last node

        Node<Type>* temp = current->nextNode;
        current->nextNode = nullptr;
        delete temp;
    }
    SIZE--;
}

template<typename Type>
void LinkedList<Type>:: PushFront(Type data)
{
    head = new Node<Type>(data, head);
    SIZE++;
}

template<typename Type>
void LinkedList<Type>:: Insert(int index, Type data)
{
    if(index >= SIZE || index < 0)
        cout << "Insert:: index is out of range" << endl;
    else if(index == 0)
    {
        PushBack(data);
        SIZE++;
    }
    else
    {
        Node<Type>* current = GetCurrent(index - 1);     // in fact, current is previous :)

        current->nextNode = new Node<Type>(data, current->nextNode);
        SIZE++;
    }
}

template<typename Type>
void LinkedList<Type>:: PopAt(int index)
{
    if(index >= SIZE || index < 0)
        cout << "PopAt:: index is out of range" << endl;
    else if(index == 0)
    {
        PopFront();
        SIZE--;
    }
    else
    {
        Node<Type>* current = GetCurrent(index - 1);     // in fact, current is previous :)

        Node<Type>* temp = current->nextNode;
        current->nextNode = current->nextNode->nextNode;
        delete temp;
        SIZE--;
    }
}

template<typename Type>
void LinkedList<Type>:: Clear()
{
    while (SIZE)
        PopFront();
    Print();
}

int main()
{
    LinkedList<int> l;
    l.PushBack(5);
    l.PushBack(10);
    l.PushBack(15);
    l.Print();
    l.Insert(1, 7);
    l.Print();
    l.PopAt(2);
    l.Print();



    return 0;
}
