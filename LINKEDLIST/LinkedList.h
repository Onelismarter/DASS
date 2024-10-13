#include <initializer_list>
#include <iostream>

template <typename T>
class SingleLinkedList
{
private:
    class Node
    {
    private:
        T data;
        Node *next = nullptr;
        Node(T _val) : data(_val) {}

        friend class SingleLinkedList<T>;
    };
    Node* head = nullptr;
    int size = 0;
    Node* currentPos = nullptr;
    void _emptyList();                          //类内部清空链表内容，函数声明没有{};
    void _copy(const SingleLinkedList<T> &_l);  //类内复制

public:
    // 返回当前位置的值
    T getCurrentVal() const;                 //数据对于用户只读，用户不能改数据
    // 设置当前位置的值 
    void setCurrentVal(const T &_val);       //内部不更改用户输入的数据
    // 如果链表为空，返回 true；否则返回 false
    bool isEmpty() const;

    int getSize() const;
    void emptyList();                        //类外部清空链表内容，函数声明没有{};

    SingleLinkedList(){}                                   //默认构造函数
    ~SingleLinkedList();                                   //析构函数，释放动态分配内存避免内存泄漏              
    SingleLinkedList(std::initializer_list<T> _l);         //初始化列表构造函数：列表初始化链表
    void printList() const;
    SingleLinkedList(const SingleLinkedList<T> &_l);       //拷贝构造函数：用于复制构造对象，这里调用类内函数_copy
    SingleLinkedList<T>& operator=(const SingleLinkedList<T> &_l);//赋值运算符，清除当前对象内容，然后复制另一个已存在的对象的内容

    void insert(const T & _val);                           //改成常量引用的方式了

    bool find (const T &_val);    
    //bool find(const T &_val) const;   //不能后面是const，因为在实现过程中改变了成员变量状态
    void remove();                      //删除当前位置的后一个元素                 
};

template<typename T>
T SingleLinkedList<T>::getCurrentVal() const
{
    if (currentPos != nullptr)
    {
        return currentPos->data;           //currentPos是Node类型的指针，取其中的data应该用
    }
    throw std::runtime_error("Empty current position! Can't get value!");
}

template<typename T>
void SingleLinkedList<T>::setCurrentVal(const T &_val)
{
    if (currentPos != nullptr)
    {
        currentPos->data = _val;
    }
    else
    {
        throw std::runtime_error("Empty current position! Can't set value!");
    }
}

template<typename T>
bool SingleLinkedList<T>::isEmpty() const
{
    return head == nullptr;
}

template<typename T>
void SingleLinkedList<T>::insert(const T&  _val)
{
    Node* newNode = new Node(_val);
    if (currentPos == nullptr)  //当前节点的指针是空的，在第一个插入
    {
        newNode->next = head;    // _val对应的节点里面的next指针指向 等于 本来的头部指针指向
        head = newNode;          //_val对应的节点成为头部指针
        currentPos = head;       //令当前节点的指针位于头部指针
    }
    else
    {
        newNode->next = currentPos->next; //_val对应的节点里面的next指针指向 等于 现在节点的next指针指向
        currentPos->next = newNode;       //当前节点的next指针指向等于_val对应的节点
        currentPos = newNode;             //令当前节点的指针等于新节点的指针
    }
    ++size;
}

template<typename T>
void SingleLinkedList<T>::remove()
{
    if (currentPos == nullptr) 
    {
        //当前位置为空，不进行操作
        return;
    }
    if (head == currentPos && currentPos->next == nullptr)
    {
        // 链表只有一个元素
        delete head;
        head = nullptr;
        currentPos = nullptr;
    }
    else if (currentPos->next != nullptr)
    {
        // 链表有多个元素且当前位置不为最后一个
        Node* toDelete = currentPos->next;
        currentPos->next = toDelete->next;    //相当于本来是当前的下下个，现在变成当前的下一个
        delete toDelete;
    }
    else
    {
        //链表有多个元素且当前位置位于最后一个
        std::cout << "Current position is at the end! Can't remove next element!" << std::endl;
    }    
    --size;
}  

/*  
//注：remove 函数的更改：
//注：此时会删去find函数所查找的元素，而不是find函数查找的后一个元素

template<typename T>
void SingleLinkedList <T>::remove() {
    if (currentPos == nullptr) {
        // 当前节点为空，不进行操作
        return;
    }

    Node* temp = head;
    Node* prev = nullptr;

    // 找到当前节点的前一个节点
    while (temp != nullptr && temp != currentPos) {  //寻找到currentPos和链表最后 之前
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        // 没有找到当前节点，不进行操作
        return;
    }

    if (prev == nullptr) {                           //更新前一个节点
        // 删除头节点，直接更新head
        head = currentPos->next;
    } else {
        // 更新前一个节点的 next 指针以跳过currentPos
        prev->next = currentPos->next;
    }

    Node* nodeToDelete = currentPos;
    currentPos = currentPos->next;                   // 更新当前节点currentPos

    delete nodeToDelete;                             // 释放内存
    --size;
} 

 */


template<typename T>
bool SingleLinkedList<T>::find(const T &_val)
//bool SingleLinkedList<T>::find(const T &_val) const //删除了const，因为这里修改了成员变量的状态
{
    Node *p = head;
    while (p != nullptr)
    {
        if (p->data == _val)
        {
            currentPos = p;  
            return true;
        }
        p = p->next;    
    }
    return false;
}

template<typename T>
int SingleLinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> _l) 
{
    for (auto i = _l.begin(); i != _l.end(); ++i)   //链表里面的迭代器，类似于数组的指针
    {
        Node* newNode = new Node(*i);               //在堆上为Node对象分配内存，并使用*i初始化它，返回的指针赋给newode
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        { 
            currentPos->next = newNode;             //完善当前节点的next指向新节点
            currentPos = newNode;                   //当前节点整体指向变成新节点
        }
        ++size;
    }
}

template <typename T>
void SingleLinkedList<T>::_emptyList()             //清空链表内容
{
    Node* p = head;
    while (p != nullptr)
    {
        Node* t = p;
        p = p->next; 
        delete t;
    }
}

template <typename T>
void SingleLinkedList<T>::printList() const
{
    Node* p = head;
    while (p != nullptr)
    {
        std::cout << p->data << "\t";
        p = p->next;
    }
    std::cout << std::endl;    
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList()     //析构函数可以在类内调用_emptyList，后者是private的，为什么不需要让另外几个成员变成空指针？？
{
    _emptyList();
}

template<typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T> &_l)  //拷贝构造函数可以在类内调用_copy，后者是private的
{
    _copy(_l);
}

template<typename T>
void SingleLinkedList<T>::emptyList()      //emptyist函数是public的，是外部用户用来清空的，emptyist可以在类内调用_emptyist
{
    _emptyList();
    head = nullptr;
    currentPos = nullptr;
    size = 0;
}

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(const SingleLinkedList<T> &_l)
{
    if (this == &_l)          //this指针就是这个链表的地址，如果该地址与&_l相同 ，防止自赋值操作
        return *this;         //返回这个链表
    emptyList();              //先清空
    _copy(_l);                //后拷贝
    return *this;             //返回这个链表
}

template <typename T>
void SingleLinkedList<T>::_copy(const SingleLinkedList<T> &_l)
{
    Node *p = _l.head;                      //指针依次指向_l链表的每个节点，下面再值拷贝每个节点
    while (p != nullptr)
    {
        Node* newNode = new Node(p->data);  //这里是拷贝了这个地方的数据，开辟新空间来放置
        if (head == nullptr)                //这里是当前链表的head指针
        {
            head = newNode;
            currentPos = head;              //拷贝第一个
        }
        else
        {
            currentPos->next = newNode;     //拷贝第二个时，把第二个节点传给第一个当前位置的->next里面，这时其实完成了第一次拷贝里面的currentPos
            currentPos = newNode;           //然后当前节点再整体挪向刚才这个新节点
        }
        ++size;
        p = p->next;
    }
}

