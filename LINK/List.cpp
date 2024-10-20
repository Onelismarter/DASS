#include "List.h"
#include <iostream>
#include  <cassert>
int main()
{
    std::cout << "测试默认构造函数： " << std::endl;
    List<int> lst;
    std::cout << "测试左值数据:尾部插入函数.push_back()和首部插入函数.push_front()： " << std::endl;    
    for (int i = 0; i < 6; ++i)
    {
        lst.push_back(i);
    }

    for (int i = 0; i < 6; ++i)
    {
        lst.push_front(-i);
    }    
    for (auto it : lst)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;

   std::cout << "测试右值数据:尾部插入函数.push_back()和首部插入函数.push_front()： " << std::endl;    
    int && ll1 = 6;
    lst.push_back(std::move(ll1));
    int && ll2 = -6;
    lst.push_front(std::move(ll2));   
    for (auto it : lst)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;

  
    std::cout << "测试首部删除函数.pop_front()、尾部删除函数.pop_back()、前置自增运算符++、*操作符重载、begin（）、end（）： " << std::endl;  
    lst.pop_front();
    lst.pop_back();
     for (auto it = lst.begin(); it !=  lst.end(); ++it)
    {
        std::cout << *it << " ";
    }   
    std::cout << std::endl; 

    std::cout << "测试前置自减、后置自减运算符--: "<< std::endl;     
    auto it = ++(++lst.begin());
    std::cout << *(--it) << std::endl;
    std::cout << *(it--) << std::endl;
    std::cout << *it << std::endl;

    std::cout << "左值数据：测试插入到指定位置.insert(): "<< std::endl;  
    lst.insert(++lst.begin(),100);
    for (auto it = lst.begin(); it !=  lst.end(); ++it)
    {
        std::cout << *it << " ";
    }   
    std::cout << std::endl;

    std::cout << "右值数据：测试插入到指定位置.insert(): "<< std::endl;  
    int && ll3 = 200;
    lst.insert(++lst.begin(),ll3);
    for (auto it = lst.begin(); it !=  lst.end(); ++it)
    {
        std::cout << *it << " ";
    }   
    std::cout << std::endl; 

    std::cout << "测试删除指定位置的数据.erase(): "<< std::endl;  
    lst.erase(++lst.begin());
    for (auto it = lst.begin(); it !=  lst.end(); ++it)
    {
        std::cout << *it << " ";
    }   
    std::cout << std::endl; 

    std::cout << "测试删除指定范围的数据.erase(): "<< std::endl; 
    lst.erase(lst.begin(),++(++lst.begin()));
    for (auto it = lst.begin(); it !=  lst.end(); ++it)
    {
        std::cout << *it << " ";
    }   
    std::cout << std::endl;     

    std::cout << "测试列表初始化构造函数、 后置自增运算符++： ";    
    List<int> lst2 = {6, 7, 8, 9, 10};
    for (auto it = lst2.begin(); it != lst2.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "测试拷贝构造函数： ";    
    List<int> lst3 = lst2;
    for (auto it = lst3.begin(); it != lst3.end(); ++it) 
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "测试移动构造函数： ";    
    List<int> lst4 = std::move(lst3);
    for (auto it = lst4.begin(); it != lst4.end(); ++it)
    {
        std::cout << *it << " ";
    }
    //  assert(lst3.begin() == lst3.end());
    //这里为什么没法比较，理论上不都是指向空指针了吗，用assert判断也不行
/*   if (lst3.begin() == lst3.end()) 
    {
       std::cerr << "Original copied list is now empty." << std::endl;
    } 
 */
    std::cout << std::endl; 

    std::cout << "测试赋值运算符号=：  ";    
    List<int> lst5;
    lst5 = lst4;
    for (auto it = lst5.begin(); it != lst5.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "非常量对象测试 .front()、.back()、begin()、end():  ";  //如果是常量对象的话则只有只读操作，无法进行修改
    std::cout << (lst5.front() += 5) << " " << (lst5.back() += 5) << std::endl;

    for (auto it = lst5.begin(); it != lst5.end(); ++it)
    {
       std::cout << (*it += 5) << " ";  // 可以修改
    }
    std::cout << std::endl;
    
    //
    std::cout << "测试.size()和清空.clear()、.empty()：  "; 
    std::cout << lst5.size() << std::endl;
    lst5.clear();
    if(lst5.empty())
    {
        std::cout << "Size after clear is " << lst5.size() << ", So the list is empty after the clear!" << std::endl;
    }
    else
    {
        std::cerr << "Failed clear!" << std::endl;
    }

    return 0;
}
