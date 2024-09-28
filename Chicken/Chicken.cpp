#include <iostream>
#include <cstring>

class Chicken {
private:
    int age = 24;
    char* name = nullptr; // 使用动态分配的C风格字符串

public:
    // 默认构造函数
    Chicken() = default;

    // 带年龄的构造函数
    Chicken(int _age) : age(_age) {}; //好像带不带；都行

    // 带年龄和名字的构造函数  ：允许在创建Chicken对象的时候同时指定年龄和名字
    Chicken(int _age, const char* _name) : age(_age) {
        int len = std::strlen(_name) + 1;
        name = new char[len];
        for (int i = 0; i < len; ++i) {
            name[i] = _name[i];
        }
    }

    // 拷贝构造函数 ： 通过已有的Chicken对象创建一个新的Chicken对象，实现深度复制 Chicken chick2=chick1 （创建的时候深度复制）
    Chicken(const Chicken& other) : age(other.age) {
        if (other.name) {
            int len = std::strlen(other.name) + 1;
            name = new char[len];
            for (int i = 0; i < len; ++i) {
                name[i] = other.name[i];
            }
        }
    }

    // 拷贝赋值运算符  ：允许将一个Chicken对象赋值给另一个Chicken对象，实现深度复制 （任意时候深度复制）：支持链式赋值操作 ：a=b=c
    Chicken& operator=(const Chicken& other) {    //other对象的值在该函数内部不能被修改
        if (this != &other) {                     //自赋值检查，如果是自己直接返回
            age = other.age;
            char* newName = nullptr;              //这里不直接用name，而是new了一个新的是因为无法确保name此时是空的，因为是任意时候深度复制，但上面的拷贝构造那里 name此时确保是空的
            if (other.name) {
                int len = std::strlen(other.name) + 1;
                newName = new char[len];
                for (int i = 0; i < len; ++i) {
                    newName[i] = other.name[i];
                }
            }
            delete[] name;                        //删除干净
            name = newName;                       //newName管理的内存传给name
        }
        return *this;                             //this 指向当前对象，*this是当前对象本身， 开头那里Chicken & 说明是以引用的方式返回当前对象，，可以支持链式赋值操作
    }

    // 析构函数
    ~Chicken() {
        if (name != nullptr)
            delete[] name;
    }

    // 设置年龄
    void setAge(int _age) {                       //_age是值传递参数，在方法内部不会被修改，不需要声明const
        age = _age;
    }

    // 设置名字
    void setName(const char* _name) {            //const 关键字确保方法内部不会修改 _name 指向的字符串内容，而且字符串字面量在 C++ 中是常量，必须用 const char* 来接收
        if (name != nullptr) {
            delete[] name;
        }
        int len = std::strlen(_name) + 1;
        name = new char[len];
        for (int i = 0; i < len; ++i) {
            name[i] = _name[i];
        }
    }

    // 获取名字
    const char* getName() const {                //末尾的const来修饰成员函数，表示这个方法不会修改对象的任何成员变量，提供对象状态的只读访问：是访问器而不是修改器！！！提高代码的可读性
        return name;                             //以const char* 的形式被返回，表示不应该修改返回的name
    }

    // 获取年龄
    const int& getAge() const {
        return age;                              //这里返回引用，但对于基本数据类型，也可以返回其值
    }
};

int main() {
//这个 Lambda 函数用于输出 Chicken 对象的状态，调用 getName 和 getAge 方法来获取 Chicken 对象的名字和年龄。由于它接受 const Chicken&，所以要求 getName 和 getAge 方法是 const 的。
    auto print = [](const Chicken &c) {
        std::cout << "Hi, everyone! My name is " << c.getName()
                  << ", I am " << c.getAge() << " years old." << std::endl;
    };

    Chicken c(24, "Kunkun");
    print(c);

    Chicken d;
    d = c;
    print(d); // 测试【赋值运算符】是否正确，能正确输出给 20 分

    Chicken a = c;
    print(a); // 测试【赋值构造函数】是否正确，能正确输出给 20 分

    c.setName("Xukun Cai");
    print(c);
    print(a);
    print(d); // 测试是否为【深度复制】，本行与上两行能正确输出给 20 分

    Chicken b;
    b = d = c;
    print(b);
    print(d); // 测试【连续赋值】功能，本行与上一行能正确输出给 20 分

    return 0;
}
