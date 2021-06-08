// CPP problem to illustrate arithmetic operations of
// very large numbers using Doubly Linked List
#include <iostream>
using namespace std;
  
// Structure of Double Linked List
struct node {
      
    // To store a single digit
    int data;
  
    // Pointers to the previous and next digit
    struct node* next;
    struct node* prev;
    node(int);
};
  
// To initialize the structure with a single digit
node::node(int val)
{
    data = val;
    next = prev = NULL;
}
  
class HugeInt {
public:
    HugeInt();
    ~HugeInt();
  
    // To insert a digit in front
    void insertInFront(int);
  
    // To insert a digit at the end
    void insertInEnd(int);
  
    // To display the large number
    void display();
  
    int length();
    void add(HugeInt*, HugeInt*);
    void mul(HugeInt*, HugeInt*);
    void dif(HugeInt*, HugeInt*);
    void quo(HugeInt*, HugeInt*);
    int cmp(HugeInt*, HugeInt*);
    node* head;
    node* tail;
    int size;
};
  
// Constructor of the Class
HugeInt::HugeInt()
{
    head = tail = NULL;
    size = 0;
}
  
// To insert at the beginning of the list
void HugeInt::insertInFront(int value)
{
    node* temp = new node(value);
      
    if (head == NULL)
        head = tail = temp;
    else {
        head->prev = temp;
        temp->next = head;
        head = temp;
    }
    size++;
}
  
// To insert in the end
void HugeInt::insertInEnd(int value)
{
    node* temp = new node(value);
      
    if (tail == NULL)
        head = tail = temp;
    else {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
    size++;
}
  
/*
To display the number can be 
modified to remove leading zeros*/
void HugeInt::display()
{
    node* temp = head;
      
    while (temp != NULL) {
        cout << temp->data;
        temp = temp->next;
    }
}
  
// Returns the number of digits
int HugeInt::length()
{
    return size;
}
  
/*
Uses simple addition method that we 
follow using carry*/
void HugeInt::add(HugeInt* a, HugeInt* b)
{
    int c = 0, s;
    HugeInt* a1 = new HugeInt(*a);
    HugeInt* b1 = new HugeInt(*b);
  
    // default copy constructor
    // Copy Constructor - used to copy objects
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
  
    while (a1->tail != NULL || b1->tail != NULL) {
        if (a1->tail != NULL && b1->tail != NULL) {
            s = ((a1->tail->data) + (b1->tail->data) + c) % 10;
            c = ((a1->tail->data) + (b1->tail->data) + c) / 10;
            a1->tail = a1->tail->prev;
            b1->tail = b1->tail->prev;
        }
        else if (a1->tail == NULL && b1->tail != NULL) {
            s = ((b1->tail->data) + c) % 10;
            c = ((b1->tail->data) + c) / 10;
            b1->tail = b1->tail->prev;
        }
        else if (a1->tail != NULL && b1->tail == NULL) {
            s = ((a1->tail->data) + c) % 10;
            c = ((a1->tail->data) + c) / 10;
            a1->tail = a1->tail->prev;
        }
          
        // Inserting the sum digit
        insertInFront(s);
    }
      
    // Inserting last carry
    if (c != 0)
        insertInFront(c);
}
  
// Normal subtraction is done by borrowing
void HugeInt::dif(HugeInt* a, HugeInt* b)
{
    int c = 0, s;
    HugeInt* a1 = new HugeInt(*a);
    HugeInt* b1 = new HugeInt(*b);
  
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
      
    while (a1->tail != NULL || b1->tail != NULL) {
        if (a1->tail != NULL && b1->tail != NULL) {
            if ((a1->tail->data) + c >= (b1->tail->data)) {
                s = ((a1->tail->data) + c - (b1->tail->data));
                c = 0;
            }
            else {
                s = ((a1->tail->data) + c + 10 - (b1->tail->data));
                c = -1;
            }
            a1->tail = a1->tail->prev;
            b1->tail = b1->tail->prev;
        }
        else if (a1->tail != NULL && b1->tail == NULL) {
            if (a1->tail->data >= 1) {
                s = ((a1->tail->data) + c);
                c = 0;
            }
            else {
                if (c != 0) {
                    s = ((a1->tail->data) + 10 + c);
                    c = -1;
                }
                else
                    s = a1->tail->data;
            }
            a1->tail = a1->tail->prev;
        }
        insertInFront(s);
    }
}
  
// This compares the two numbers and returns 
// true or 1 when a is greater
int HugeInt::cmp(HugeInt* a, HugeInt* b)
{
    if (a->size != b->size)
        return ((a->size > b->size) ? 1 : 0);
    else {
        HugeInt* a1 = new HugeInt(*a);
        HugeInt* b1 = new HugeInt(*b);
        while (a1->head != NULL && b1->head != NULL) {
            if (a1->head->data > b1->head->data)
                return 1;
            else if (a1->head->data < b1->head->data)
                return 0;
            else {
                a1->head = a1->head->next;
                b1->head = b1->head->next;
            }
        }
        return 2;
    }
}
  
// Returns the quotient using Normal Division
// Multiplication is used to find what factor 
// is to be multiplied
void HugeInt::quo(HugeInt* a, HugeInt* b)
{
    HugeInt* a1 = new HugeInt(*a);
    HugeInt* b1 = new HugeInt(*b);
    HugeInt* ex = new HugeInt();
    HugeInt* mp = new HugeInt();
    HugeInt* pr = new HugeInt();
    int i = 0;
    for (i = 0; i < b1->size; i++) {
        ex->insertInEnd(a1->head->data);
        a1->head = a1->head->next;
    }
  
    for (i = 0; i < 10; i++) {
        HugeInt* b2 = new HugeInt(*b);
        mp->insertInEnd(i);
        pr->mul(b2, mp);
        if (!cmp(ex, pr))
            break;
        mp->head = mp->tail = NULL;
        pr->head = pr->tail = NULL;
        mp->size = pr->size = 0;
    }
  
    mp->head = mp->tail = NULL;
    pr->head = pr->tail = NULL;
    mp->size = pr->size = 0;
  
    mp->insertInEnd(i - 1);
    pr->mul(b1, mp);
    ex->dif(ex, pr);
    insertInEnd(i - 1);
    mp->head = mp->tail = NULL;
    pr->head = pr->tail = NULL;
    mp->size = pr->size = 0;
  
    while (a1->head != NULL) {
        ex->insertInEnd(a1->head->data);
        while (ex->head->data == 0) {
            ex->head = ex->head->next;
            ex->size--;
        }
        for (i = 0; i < 10; i++) {
            HugeInt* b2 = new HugeInt(*b);
            mp->insertInEnd(i);
            pr->mul(b2, mp);
            if (!cmp(ex, pr))
                break;
            mp->head = mp->tail = NULL;
            pr->head = pr->tail = NULL;
            mp->size = pr->size = 0;
        }
  
        mp->head = mp->tail = NULL;
        pr->head = pr->tail = NULL;
        mp->size = pr->size = 0;
  
        mp->insertInEnd(i - 1);
        pr->mul(b1, mp);
        ex->dif(ex, pr);
  
        insertInEnd(i - 1);
  
        mp->head = mp->tail = NULL;
        pr->head = pr->tail = NULL;
        mp->size = pr->size = 0;
  
        a1->head = a1->head->next;
    }
  
    cout << endl
        << "\nModulus :" << endl;
    ex->display();
}
  
// Normal multiplication is used i.e. in one to all way
void HugeInt::mul(HugeInt* a, HugeInt* b)
{
    int k = 0, i;
    HugeInt* tpro = new HugeInt();
    while (b->tail != NULL) {
        int c = 0, s = 0;
        HugeInt* temp = new HugeInt(*a);
        HugeInt* pro = new HugeInt();
        while (temp->tail != NULL) {
            s = ((temp->tail->data) * (b->tail->data) + c) % 10;
            c = ((temp->tail->data) * (b->tail->data) + c) / 10;
            pro->insertInFront(s);
            temp->tail = temp->tail->prev;
        }
        if (c != 0)
            pro->insertInFront(c);
  
        for (i = 0; i < k; i++)
            pro->insertInEnd(0);
  
        add(this, pro);
        k++;
        b->tail = b->tail->prev;
        pro->head = pro->tail = NULL;
        pro->size = 0;
    }
}
  
// Structure of Double Linked List
struct Node
{
    // To store a single digit
    int data;
  
    // Pointers to the previous and next digit
    struct Node* next;
    struct Node* prev;
    Node(int);
};
  
// To initialize the structure with a single digit
Node::Node(int val)
{
    data = val;
    next = prev = NULL;
}
  
class HugeIntLL
{
public:
    HugeIntLL();
    ~HugeIntLL();
  
    // To insert a digit in front
    void insertInFront(int);
  
    // To insert a digit at the end
    void insertInEnd(int);
  
    // To display the large number
    void display();
  
    int length();
    void add(HugeIntLL*, HugeIntLL*);
    void mul(HugeIntLL*, HugeIntLL*);
    void dif(HugeIntLL*, HugeIntLL*);
    void quo(HugeIntLL*, HugeIntLL*);
    int cmp(HugeIntLL*, HugeIntLL*);
    Node* head;
    Node* tail;
    int size;
};
  
// Constructor of the Class
HugeIntLL::HugeIntLL()
{
    head = tail = NULL;
    size = 0;
}
  
// To insert at the beginning of the list
void HugeIntLL::insertInFront(int value)
{
    Node* temp = new Node(value);
  
    if (head == NULL)
        head = tail = temp;
    else
    {
        head->prev = temp;
        temp->next = head;
        head = temp;
    }
    size++;
}
  
// To insert in the end
void HugeIntLL::insertInEnd(int value)
{
    Node* temp = new Node(value);
  
    if (tail == NULL)
        head = tail = temp;
    else
    {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
    size++;
}
  
/*
To display the number can be
modified to remove leading zeros*/
void HugeIntLL::display()
{
    Node* temp = head;
  
    while (temp != NULL)
    {
        cout << temp->data;
        temp = temp->next;
    }
}
  
// Returns the number of digits
int HugeIntLL::length()
{
    return size;
}
  
/* Uses simple addition method that we
   follow using carry*/
void HugeIntLL::add(HugeIntLL* a, HugeIntLL* b)
{
    int c = 0, s;
    HugeIntLL* a1 = new HugeIntLL(*a);
    HugeIntLL* b1 = new HugeIntLL(*b);
  
    // default copy constructor
    // Copy Constructor - used to copy objects
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
  
    while (a1->tail != NULL || b1->tail != NULL)
    {
        if (a1->tail != NULL && b1->tail != NULL)
        {
            s = ((a1->tail->data) + (b1->tail->data) + c) % 10;
            c = ((a1->tail->data) + (b1->tail->data) + c) / 10;
            a1->tail = a1->tail->prev;
            b1->tail = b1->tail->prev;
        }
        else if (a1->tail == NULL && b1->tail != NULL)
        {
            s = ((b1->tail->data) + c) % 10;
            c = ((b1->tail->data) + c) / 10;
            b1->tail = b1->tail->prev;
        }
        else if (a1->tail != NULL && b1->tail == NULL)
        {
            s = ((a1->tail->data) + c) % 10;
            c = ((a1->tail->data) + c) / 10;
            a1->tail = a1->tail->prev;
        }
  
        // Inserting the sum digit
        insertInFront(s);
    }
  
    // Inserting last carry
    if (c != 0)
        insertInFront(c);
}
  
// Normal subtraction is done by borrowing
void HugeIntLL::dif(HugeIntLL* a, HugeIntLL* b)
{
    int c = 0, s;
    HugeIntLL* a1 = new HugeIntLL(*a);
    HugeIntLL* b1 = new HugeIntLL(*b);
  
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
  
    while (a1->tail != NULL || b1->tail != NULL)
    {
        if (a1->tail != NULL && b1->tail != NULL)
        {
            if ((a1->tail->data) + c >= (b1->tail->data))
            {
                s = ((a1->tail->data) + c - (b1->tail->data));
                c = 0;
            }
            else
            {
                s = ((a1->tail->data) + c + 10 - (b1->tail->data));
                c = -1;
            }
            a1->tail = a1->tail->prev;
            b1->tail = b1->tail->prev;
        }
        else if (a1->tail != NULL && b1->tail == NULL)
        {
            if (a1->tail->data >= 1)
            {
                s = ((a1->tail->data) + c);
                c = 0;
            }
            else
            {
                if (c != 0)
                {
                    s = ((a1->tail->data) + 10 + c);
                    c = -1;
                }
                else
                    s = a1->tail->data;
            }
            a1->tail = a1->tail->prev;
        }
        insertInFront(s);
    }
}
  
// This compares the two numbers and returns
// true or 1 when a is greater
int HugeIntLL::cmp(HugeIntLL* a, HugeIntLL* b)
{
    if (a->size != b->size)
        return ((a->size > b->size) ? 1 : 0);
  
    HugeIntLL* a1 = new HugeIntLL(*a);
    HugeIntLL* b1 = new HugeIntLL(*b);
    while (a1->head != NULL && b1->head != NULL)
    {
        if (a1->head->data > b1->head->data)
            return 1;
        else if (a1->head->data < b1->head->data)
            return 0;
        else
        {
            a1->head = a1->head->next;
            b1->head = b1->head->next;
        }
    }
    return 2;
}
  
// Returns the quotient using Normal Division
// Multiplication is used to find what factor
// is to be multiplied
void HugeIntLL::quo(HugeIntLL* a, HugeIntLL* b)
{
    HugeIntLL* a1 = new HugeIntLL(*a);
    HugeIntLL* b1 = new HugeIntLL(*b);
    HugeIntLL* ex = new HugeIntLL();
    HugeIntLL* mp = new HugeIntLL();
    HugeIntLL* pr = new HugeIntLL();
    int i = 0;
    for (i = 0; i < b1->size; i++)
    {
        ex->insertInEnd(a1->head->data);
        a1->head = a1->head->next;
    }
  
    for (i = 0; i < 10; i++)
    {
        HugeIntLL* b2 = new HugeIntLL(*b);
        mp->insertInEnd(i);
        pr->mul(b2, mp);
        if (!cmp(ex, pr))
            break;
        mp->head = mp->tail = NULL;
        pr->head = pr->tail = NULL;
        mp->size = pr->size = 0;
    }
  
    mp->head = mp->tail = NULL;
    pr->head = pr->tail = NULL;
    mp->size = pr->size = 0;
  
    mp->insertInEnd(i - 1);
    pr->mul(b1, mp);
    ex->dif(ex, pr);
    insertInEnd(i - 1);
    mp->head = mp->tail = NULL;
    pr->head = pr->tail = NULL;
    mp->size = pr->size = 0;
  
    while (a1->head != NULL)
    {
        ex->insertInEnd(a1->head->data);
        while (ex->head->data == 0)
        {
            ex->head = ex->head->next;
            ex->size--;
        }
        for (i = 0; i < 10; i++)
        {
            HugeIntLL* b2 = new HugeIntLL(*b);
            mp->insertInEnd(i);
            pr->mul(b2, mp);
            if (!cmp(ex, pr))
                break;
            mp->head = mp->tail = NULL;
            pr->head = pr->tail = NULL;
            mp->size = pr->size = 0;
        }
  
        mp->head = mp->tail = NULL;
        pr->head = pr->tail = NULL;
        mp->size = pr->size = 0;
  
        mp->insertInEnd(i - 1);
        pr->mul(b1, mp);
        ex->dif(ex, pr);
  
        insertInEnd(i - 1);
  
        mp->head = mp->tail = NULL;
        pr->head = pr->tail = NULL;
        mp->size = pr->size = 0;
  
        a1->head = a1->head->next;
    }
  
    cout << endl
         << "\nModulus :" << endl;
    ex->display();
}
  
// Normal multiplication is used i.e. in one to all way
void HugeIntLL::mul(HugeIntLL* a, HugeIntLL* b)
{
    int k = 0, i;
    HugeIntLL* tpro = new HugeIntLL();
    while (b->tail != NULL)
    {
        int c = 0, s = 0;
        HugeIntLL* temp = new HugeIntLL(*a);
        HugeIntLL* pro = new HugeIntLL();
        while (temp->tail != NULL)
        {
            s = ((temp->tail->data) * (b->tail->data) + c) % 10;
            c = ((temp->tail->data) * (b->tail->data) + c) / 10;
            pro->insertInFront(s);
            temp->tail = temp->tail->prev;
        }
        if (c != 0)
            pro->insertInFront(c);
  
        for (i = 0; i < k; i++)
            pro->insertInEnd(0);
  
        add(this, pro);
        k++;
        b->tail = b->tail->prev;
        pro->head = pro->tail = NULL;
        pro->size = 0;
    }
}
  
// Driver code
int main()
{
    HugeIntLL* m = new HugeIntLL();
    HugeIntLL* n = new HugeIntLL();
    HugeIntLL* s = new HugeIntLL();
    HugeIntLL* p = new HugeIntLL();
    HugeIntLL* d = new HugeIntLL();
    HugeIntLL* q = new HugeIntLL();
  
    string s1 = "12345678912345678912345678"
                 "9123456789123456789123456789";
    string s2 = "45678913456789123456789123456"
                 "789123456789123456789";
  
    for (int i = 0; i < s1.length(); i++)
        m->insertInEnd(s1.at(i) - '0');
  
    for (int i = 0; i < s2.length(); i++)
        n->insertInEnd(s2.at(i) - '0');
  
    // Creating copies of m and n
    HugeIntLL* m1 = new HugeIntLL(*m);
    HugeIntLL* n1 = new HugeIntLL(*n);
    HugeIntLL* m2 = new HugeIntLL(*m);
    HugeIntLL* n2 = new HugeIntLL(*n);
    HugeIntLL* m3 = new HugeIntLL(*m);
    HugeIntLL* n3 = new HugeIntLL(*n);
  
    cout << "Product :" << endl;
    s->mul(m, n);
    s->display();
    cout << endl;
  
    cout << "Sum :" << endl;
    p->add(m1, n1);
    p->display();
    cout << endl;
  
    cout << "Difference (m-n) : m>n:" << endl;
  
    d->dif(m2, n2);
    d->display();
    q->quo(m3, n3);
    cout << endl;
  
    cout << "Quotient :" << endl;
    q->display();
    return 0;
}