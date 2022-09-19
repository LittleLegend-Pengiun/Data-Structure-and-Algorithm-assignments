#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__

#include <string>
#include <stack>

template <class T>
class Node
{
    T data;
    Node* previous;
    Node* next;
    template <class U> friend class DLinkedList;
public:
    Node();
    Node(const T &data);
};

template <class T>
class DLinkedList {
protected:
    Node<T>* head;
    Node<T>* tail;
    int count;
public:
    DLinkedList();
    ~DLinkedList();
    void    add(const T &e);
    void    add(int index,const T &e);
    int     size();
    bool    empty();
    T       get(int index);
    void    set(int index,const T &e);
    int     indexOf(const T &item);
    bool    contains(const T &item);
    T       removeAt(int index);
    bool    removeItem(const T &item);
    void    clear();
};

template<class T>
class Stack {
    DLinkedList<T>* list;
public:
    Stack();
    ~Stack();
    void push(const T &item);
    T pop();
    T top();
    bool empty();
    int size();
    void clear();
};

class StackFrame {
    // Attributes
    int opStackMaxSize; // max size of operand stack
    int localVarArrSize; // size of local variable array
    Stack<float>* op_stack;
    float** lc_var_spc;
    int current_line;
    // Methods
    void operation(std::string command); // run the command

    // List of command functions
    void cmd_iconst(float value);
    void cmd_istore(int value);
    void cmd_iadd();
    void cmd_fadd();
    void cmd_isub();
    void cmd_fsub();
    void cmd_imul();
    void cmd_fmul();
    void cmd_idiv();
    void cmd_fdiv();
    void cmd_irem();
    void cmd_ineg();
    void cmd_fneg();
    void cmd_iand();
    void cmd_ior();
    void cmd_ieq();
    void cmd_feq();
    void cmd_ineq();
    void cmd_fneq();
    void cmd_ilt();
    void cmd_flt();
    void cmd_igt();
    void cmd_fgt();
    void cmd_ibnot();
    void cmd_fconst(float value);
    void cmd_iload(int value);
    void cmd_fload(int value);
    void cmd_fstore(int value);
    void cmd_i2f();
    void cmd_f2i();
    void cmd_top();
    void cmd_val(int index);



public:
    StackFrame(); // Constructor
    ~StackFrame(); // Destructor
    void run(std::string filename); // Run the file
};

#endif // !__STACK_FRAME_H__