#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;

StackFrame::StackFrame()
{
    opStackMaxSize = OPERAND_STACK_MAX_SIZE;
    localVarArrSize = LOCAL_VARIABLE_SPACE_SIZE;
    op_stack = new stack<float>();
    lc_var_spc = new AVLTree<Value_and_type>();
    current_line = 0;
}

StackFrame::~StackFrame()
{
    delete op_stack;
    op_stack = NULL;
    delete lc_var_spc;
    lc_var_spc = NULL;
}

void StackFrame::run(string filename)
{
    ifstream fin(filename);
    while (!fin.eof())
    {
        current_line += 1;
        string line;
        getline(fin, line);
        this->operation(line);
    }
}

void StackFrame::operation(string command)
{
    int position = (int)command.find(" ");
    string cmd = "", value = "";
    if (position > -1)
    {
        cmd = command.substr(0, position);
        value = command.substr(position + 1);
    }
    else if (command.find("\r") != string::npos)
        cmd = command.substr(0, command.length() - 1);
    else
        cmd = command;

    if (cmd == "iadd")
    {
        cmd_iadd();
    }
    else if (cmd == "fadd")
    {
        cmd_fadd();
    }
    else if (cmd == "isub")
    {
        cmd_isub();
    }
    else if (cmd == "fsub")
    {
        cmd_fsub();
    }
    else if (cmd == "imul")
    {
        cmd_imul();
    }
    else if (cmd == "fmul")
    {
        cmd_fmul();
    }
    else if (cmd == "idiv")
    {
        cmd_idiv();
    }
    else if (cmd == "fdiv")
    {
        cmd_fdiv();
    }
    else if (cmd == "irem")
    {
        cmd_irem();
    }
    else if (cmd == "ineg")
    {
        cmd_ineg();
    }
    else if (cmd == "fneg")
    {
        cmd_fneg();
    }
    else if (cmd == "iand")
    {
        cmd_iand();
    }
    else if (cmd == "ior")
    {
        cmd_ior();
    }
    else if (cmd == "ieq")
    {
        cmd_ieq();
    }
    else if (cmd == "feq")
    {
        cmd_feq();
    }
    else if (cmd == "ineq")
    {
        cmd_ineq();
    }
    else if (cmd == "fneq")
    {
        cmd_fneq();
    }
    else if (cmd == "ineg")
    {
        cmd_ineg();
    }
    else if (cmd == "fneg")
    {
        cmd_fneg();
    }
    else if (cmd == "ilt")
    {
        cmd_ilt();
    }
    else if (cmd == "flt")
    {
        cmd_flt();
    }
    else if (cmd == "igt")
    {
        cmd_igt();
    }
    else if (cmd == "fgt")
    {
        cmd_fgt();
    }
    else if (cmd == "ibnot")
    {
        cmd_ibnot();
    }
    else if (cmd == "iconst")
    {
        cmd_iconst(stoi(value));
    }
    else if (cmd == "fconst")
    {
        cmd_fconst(stof(value));
    }
    else if (cmd == "iload")
    {
        cmd_iload(value);
    }
    else if (cmd == "istore")
    {
        cmd_istore(value);
    }
    else if (cmd == "fload")
    {
        cmd_fload(value);
    }
    else if (cmd == "fstore")
    {
        cmd_fstore(value);
    }
    else if (cmd == "i2f")
    {
        cmd_i2f();
    }
    else if (cmd == "f2i")
    {
        cmd_f2i();
    }
    else if (cmd == "top")
    {
        cmd_top();
    }
    else if (cmd == "val")
    {
        cmd_val(value);
    }
    else if (cmd == "par") 
    {
        cmd_par(value);
    }
    else
    {
        cout << "Other command: " << cmd << endl;
    }
}

void StackFrame::cmd_iadd()
{
    float type1, type2, value1, value2;
    
    if (op_stack->size() < 4)
        {throw StackEmpty(current_line);}
    
    type1 = op_stack->top();
    op_stack->pop();
    value1 = op_stack->top();
    op_stack->pop();
    type2 = op_stack->top();
    op_stack->pop();
    value2 = op_stack->top();
    op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1)
        throw TypeMisMatch(current_line);
    int new_value = value1 + value2;
    op_stack->push(new_value);
    op_stack->push(0);
}
void StackFrame::cmd_fadd()
{
    float value1, value2;
    if (op_stack->size() < 4)
        {throw StackEmpty(current_line);}
    
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
        op_stack->pop();
        value2 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    // if (type1 == 0 || type2 == 0) throw TypeMisMatch(current_line);
    float new_value = value1 + value2;
    op_stack->push(new_value);
    op_stack->push(1);
}

void StackFrame::cmd_isub()
{
    float type1, type2, value1, value2;
    if (op_stack->size() < 4)
        {throw StackEmpty(current_line);}
    
        type1 = op_stack->top();
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
        type2 = op_stack->top();
        op_stack->pop();
        value2 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1)
        throw TypeMisMatch(current_line);
    int new_value = value2 - value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_fsub()
{
    float value1, value2;
    if (op_stack->size() < 4)
        {throw StackEmpty(current_line);}
   
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
        op_stack->pop();
        value2 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    // if (type1 == 0 || type2 == 0) throw TypeMisMatch(current_line);
    float new_value = value2 - value1;
    op_stack->push(new_value);
    op_stack->push(1);
}

void StackFrame::cmd_imul()
{
    float type1, type2, value1, value2;
    if (op_stack->size() < 4)
        {throw StackEmpty(current_line);}
    
        type1 = op_stack->top();
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
        type2 = op_stack->top();
        op_stack->pop();
        value2 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1)
        throw TypeMisMatch(current_line);
    int new_value = value1 * value2;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_fmul()
{
    float value1, value2;
    if (op_stack->size() < 4)
        {throw StackEmpty(current_line);}
    
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
        op_stack->pop();
        value2 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    // if (type1 == 0 || type2 == 0) throw TypeMisMatch(current_line);
    float new_value = value1 * value2;
    op_stack->push(new_value);
    op_stack->push(1);
}

void StackFrame::cmd_idiv()
{
    float type1, type2, value1, value2;
    if (op_stack->size() < 4) 
        {throw StackEmpty(current_line);}
    
        type1 = op_stack->top();
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
        type2 = op_stack->top();
        op_stack->pop();
        value2 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1)
        throw TypeMisMatch(current_line);
    if (value1 == 0)
        throw DivideByZero(current_line);
    int new_value = (int)(value2 / value1);
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_fdiv()
{
    float value1, value2;
    if (op_stack->size() < 4)
        {throw StackEmpty(current_line);}
    
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
        op_stack->pop();
        value2 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    // if (type1 == 0 || type2 == 0) throw TypeMisMatch(current_line);
    if (value1 == 0)
        throw DivideByZero(current_line);
    float new_value = value2 / value1;
    op_stack->push(new_value);
    op_stack->push(1);
}

void StackFrame::cmd_irem()
{
    float type1, type2, value1, value2;
    if (op_stack->size() < 4)
        {throw StackEmpty(current_line);}
    
        type1 = op_stack->top();
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
        type2 = op_stack->top();
        op_stack->pop();
        value2 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1)
        throw TypeMisMatch(current_line);
    if (value1 == 0)
        throw DivideByZero(current_line);

    float new_value = (int)value2 - ((int)value2 / (int)value1) * (int)value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_ineg()
{
    float type1, value1;
    if (op_stack->size() < 2)
        {throw StackEmpty(current_line);}
    
        type1 = op_stack->top();
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1)
        throw TypeMisMatch(current_line);
    int new_value = -value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_fneg()
{
    float value1;
    if (op_stack->size() < 2)
        {throw StackEmpty(current_line);}
    
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    // if (type1 == 0) throw TypeMisMatch(current_line);
    float new_value = -value1;
    op_stack->push(new_value);
    op_stack->push(1);
}

void StackFrame::cmd_iand()
{
    float type1, type2, value1, value2;
    if (op_stack->size() < 4)
        {throw StackEmpty(current_line);}
    
        type1 = op_stack->top();
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
        type2 = op_stack->top();
        op_stack->pop();
        value2 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1)
        throw TypeMisMatch(current_line);
    int new_value = (int)value2 & (int)value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_ior()
{
    float type1, type2, value1, value2;
    if (op_stack->size() < 4)
        {throw StackEmpty(current_line);}
    
        type1 = op_stack->top();
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
        type2 = op_stack->top();
        op_stack->pop();
        value2 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1)
        throw TypeMisMatch(current_line);
    int new_value = (int)value2 | (int)value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_ieq()
{
    float type1, type2, value1, value2;
    if (op_stack->size() < 4)
        {throw StackEmpty(current_line);}
    
        type1 = op_stack->top();
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
        type2 = op_stack->top();
        op_stack->pop();
        value2 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1)
        throw TypeMisMatch(current_line);
    int new_value = (int)value2 == (int)value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_feq()
{
    float value1, value2;
    if (op_stack->size() < 4)
        {throw StackEmpty(current_line);}
    
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
        
        op_stack->pop();
        value2 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    // if (type1 == 0 || type2 == 0) throw TypeMisMatch(current_line);
    int new_value = value2 == value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_ineq()
{
    float type1, type2, value1, value2;
    if (op_stack->size() < 4)
        {throw StackEmpty(current_line);}
    
        type1 = op_stack->top();
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
        type2 = op_stack->top();
        op_stack->pop();
        value2 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1)
        throw TypeMisMatch(current_line);
    int new_value = (int)value2 != (int)value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_fneq()
{
    float value1, value2;
    if (op_stack->size() < 4)
        {throw StackEmpty(current_line);}
    
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
        op_stack->pop();
        value2 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    // if (type1 == 0 || type2 == 0) throw TypeMisMatch(current_line);
    int new_value = value2 != value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_ilt()
{
    float type1, type2, value1, value2;
    if (op_stack->size() < 4)
        {throw StackEmpty(current_line);}
    
        type1 = op_stack->top();
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
        type2 = op_stack->top();
        op_stack->pop();
        value2 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1)
        throw TypeMisMatch(current_line);
    int new_value = (int)value2 < (int)value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_flt()
{
    float value1, value2;
    if (op_stack->size() < 4)
        {throw StackEmpty(current_line);}
    
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
        op_stack->pop();
        value2 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    // if (type1 == 0 || type2 == 0) throw TypeMisMatch(current_line);
    int new_value = value2 < value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_igt()
{
    float type1, type2, value1, value2;
    if (op_stack->size() < 4)
        {throw StackEmpty(current_line);}
    
        type1 = op_stack->top();
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
        type2 = op_stack->top();
        op_stack->pop();
        value2 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1)
        throw TypeMisMatch(current_line);
    int new_value = (int)value2 > (int)value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_fgt()
{
    float value1, value2;
    if (op_stack->size() < 4)
        {throw StackEmpty(current_line);}
    
        op_stack->pop();
        value1 = op_stack->top();
        op_stack->pop();
        
        op_stack->pop();
        value2 = op_stack->top();
        op_stack->pop();
    
    // cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    // if (type1 == 0 || type2 == 0) throw TypeMisMatch(current_line);
    int new_value = value2 > value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_ibnot()
{
    float type, value;
    if (op_stack->size() < 2)
        {throw StackEmpty(current_line);}
    
        type = op_stack->top();
        op_stack->pop();
        value = op_stack->top();
        op_stack->pop();
    
    if (type == 1)
        throw TypeMisMatch(current_line);
    int new_value = (int)value == 0;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_iconst(float value)
{
    if ((int)op_stack->size() == opStackMaxSize)
        throw StackFull(current_line);
    op_stack->push(value);
    op_stack->push(0);
}

void StackFrame::cmd_fconst(float value)
{
    if ((int)op_stack->size() == opStackMaxSize)
        throw StackFull(current_line);
    op_stack->push(value);
    op_stack->push(1);
}

void StackFrame::cmd_iload(string idx)
{
    Value_and_type* variable = lc_var_spc->search(idx);
    if (variable == nullptr)
        throw UndefinedVariable(current_line);
    
    float value = variable->value;
    float type = variable->type;
    
    if (type == 1)
        throw TypeMisMatch(current_line);
    
    cmd_iconst(value);
}

void StackFrame::cmd_fload(string idx)
{
    Value_and_type* variable = lc_var_spc->search(idx);
    if (variable == nullptr)
        throw UndefinedVariable(current_line);
    
    float value = variable->value;
    float type = variable->type;
    
    if (type == 0)
        throw TypeMisMatch(current_line);
    
    cmd_fconst(value);
}

void StackFrame::cmd_istore(string idx)
{
    int type, val;
    if (op_stack->size() < 2)
        {throw StackEmpty(current_line);}
    
        type = op_stack->top();
        op_stack->pop();
        val = op_stack->top();
        op_stack->pop();
    

    if (type == 1)
        throw TypeMisMatch(current_line);

    if (lc_var_spc->size() == this->localVarArrSize)
        throw LocalSpaceFull(current_line);
    
    Value_and_type* push_val = new Value_and_type(val, (bool)type);
    lc_var_spc->insert(idx, push_val);
}

void StackFrame::cmd_fstore(string idx)
{
    float type, val;
    try
    {
        type = op_stack->top();
        op_stack->pop();
        val = op_stack->top();
        op_stack->pop();
    }
    catch (const out_of_range &e)
    {
        {throw StackEmpty(current_line);}
    }

    if (type == 0)
        throw TypeMisMatch(current_line);

    if (lc_var_spc->size() == LOCAL_VARIABLE_SPACE_SIZE)
        throw LocalSpaceFull(current_line);
    
    Value_and_type* push_val = new Value_and_type(val, (bool)type);
    lc_var_spc->insert(idx, push_val);
}
void StackFrame::cmd_i2f()
{
    int type, value;
    try
    {
        type = op_stack->top();
        op_stack->pop();
        value = op_stack->top();
        op_stack->pop();
    }
    catch (const out_of_range &e)
    {
        {throw StackEmpty(current_line);}
    }

    if (type == 1)
        throw TypeMisMatch(current_line);

    cmd_fconst((float)value);
}

void StackFrame::cmd_f2i()
{
    float type, value;
    if (op_stack->size() < 2)
        {throw StackEmpty(current_line);}
    
        type = op_stack->top();
        op_stack->pop();
        value = op_stack->top();
        op_stack->pop();
    

    if (type == 0)
        throw TypeMisMatch(current_line);

    cmd_iconst(static_cast<int>(value));
}

void StackFrame::cmd_top()
{
    if (op_stack->empty())
        {throw StackEmpty(current_line);}
    float type = op_stack->top();
    op_stack->pop();
    cout << op_stack->top() << "\n";
    op_stack->push(type);
}

void StackFrame::cmd_val(string var)
{
    Value_and_type* variable = lc_var_spc->search(var);
    if (variable == nullptr)
        throw UndefinedVariable(current_line);
    
    float value = variable->value;
    
    cout << value << "\n";
}

void StackFrame::cmd_par(string var) 
{
    Value_and_type* variable = lc_var_spc->search(var);
    if (variable == nullptr)
        throw UndefinedVariable(current_line);
    
    cout << lc_var_spc->get_parent_node() << "\n";
}





//-------------------------------------------------------------------
// AVL Declaration ==================================================
// ==================================================================

template <class T>
int AVLTree<T>::compare_string1_to_string2(const string &string1, const string &string2) // <: 1; >: -1; ==: 0
{
    int len1 = string1.length();
    int len2 = string2.length();
    int i = 0;
    while (string1[i] != '\0' && string2[i] != '\0')
    {
        if (string1[i] > string2[i])
            return -1;
        if (string1[i] < string2[i])
            return 1;
        i++;
    }
    if (len1 < len2)
        return 1;
    if (len1 == len2)
        return 0;
    return -1;
}

template <class T>
AVLTree<T>::AVLTree()
{
    this->root = NULL;
    this->count = 0;
    this->delete_data = NULL;
    this->parent_of_searched_node = NULL;
}

template <class T>
AVLTree<T>::~AVLTree()
{
    this->clear();
    this->root = NULL;
    if (delete_data != NULL) {
        delete this->delete_data;
        this->delete_data = NULL;
    }  
    this->count = 0;
}

template <class T>
int AVLTree<T>::get_height()
{
    return this->getHeightRec(this->root);
}

template <class T>
int AVLTree<T>::size()
{
    return this->count;
}

template <class T>
int AVLTree<T>::getHeightRec(Node *node)
{
    if (node == NULL)
        return 0;
    int lh = this->getHeightRec(node->left);
    int rh = this->getHeightRec(node->right);
    return (lh > rh ? lh : rh) + 1;
}

template <class T>
typename AVLTree<T>::Node *AVLTree<T>::rotate_left(Node *&node)
{
    // Không cần check vì chỉ gọi xoay khi lệch, khi lệch thì độ cao >= 3
    Node *right_sub_tree = node->right;
    node->right = right_sub_tree->left;
    right_sub_tree->left = node;
    return right_sub_tree;
}

template <class T>
typename AVLTree<T>::Node *AVLTree<T>::rotate_right(Node *&node)
{
    // Không cần check vì chỉ gọi xoay khi lệch, khi lệch thì độ cao >= 3
    Node *left_sub_tree = node->left;
    node->left = left_sub_tree->right;
    left_sub_tree->right = node;
    return left_sub_tree;
}

template <class T>
typename AVLTree<T>::Node *AVLTree<T>::left_balance(
    Node *&node,
    bool &taller)
{
    Node *left_tree = node->left;
    // Cây con trái lệch trái: L-L
    if (left_tree->balance == LH)
    {
        node->balance = EH;
        left_tree->balance = EH;
        node = rotate_right(node);
        taller = false;
    }
    // Cây con trái lệch phải: R-L
    else
    {
        Node *right_tree = left_tree->right;
        // Cây bên phải của cây con trái lệch trái:
        if (right_tree->balance == LH)
        {
            node->balance = RH;
            left_tree->balance = EH;
        }
        // Cây bên phải của cây con trái cân bằng:
        else if (right_tree->balance == EH)
        {
            left_tree->balance = EH;
            node->balance = EH;
        }
        // Cây bên phải của cây con trái lệch phải:
        else
        {
            node->balance = EH;
            left_tree->balance = LH;
        }
        right_tree->balance = EH;
        node->left = rotate_left(left_tree);
        node = rotate_right(node);
        taller = false;
    }
    return node;
}

template <class T>
typename AVLTree<T>::Node *AVLTree<T>::right_balance(
    Node *&node,
    bool &taller)
{
    Node *right_tree = node->right;
    // Cây con phải lệch phải: R-R
    if (right_tree->balance == RH)
    {
        node->balance = EH;
        right_tree->balance = EH;
        node = rotate_left(node);
        taller = false; // Sau khi tái cân bằng cây không cao lên
    }
    // Cây con phải lệch trái: L-R
    else
    {
        Node *left_tree = right_tree->left;
        // Cây bên trái của cây con phải lệch phải:
        if (left_tree->balance == RH)
        {
            node->balance = LH;
            right_tree->balance = EH;
        }
        // Cây bên trái của cây con phải cân bằng:
        else if (left_tree->balance == EH)
        {
            right_tree->balance = EH;
            node->balance = EH;
        }
        // Cây bên trái của cây con trái lệch phải:
        else
        {
            node->balance = EH;
            right_tree->balance = RH;
        }
        left_tree->balance = EH;
        node->right = rotate_right(right_tree);
        node = rotate_left(node);
        taller = false;
    }
    return node;
}

template <class T>
typename AVLTree<T>::Node *AVLTree<T>::insert(
    Node *&node,
    string key,
    T *data,
    bool &taller)
{
    if (node == nullptr)
    {
        Node *new_node = new Node(key, data);
        node = new_node;
        taller = true;
        return node;
    }
    else
    {
        
        int tf = this->compare_string1_to_string2(key, node->key);
        if (tf == 1)
        { // Insert vào bên trái
            node->left = insert(node->left, key, data, taller);
            // Nếu cây con bên trái cao lên:
            if (taller)
            {
                // Cây lệch trái thì mất cân bằng -> tái cân bằng:
                if (node->balance == LH)
                    node = left_balance(node, taller);
                // Cây cân bằng thì lệch trái + cây cao lên
                else if (node->balance == EH)
                    node->balance = LH;
                // Cây lệch phải thì cân bằng + cây không cao lên
                else
                {
                    node->balance = EH;
                    taller = false;
                }
            }
        }
        else
        {
            node->right = insert(node->right, key, data, taller);
            // Nếu cây con bên phải cao lên
            if (taller)
            {
                // Cây lệch phải thì mất cân bằng -> tái cân bằng:
                if (node->balance == RH)
                    node = right_balance(node, taller);
                // Cây cân bằng thì lệch phải + cây cao lên
                else if (node->balance == EH)
                    node->balance = RH;
                // Cây lệch trái thì cân bằng + cây không cao lên
                else
                {
                    node->balance = EH;
                    taller = false;
                }
            }
        }
        return node;
    }
}

template <class T>
void AVLTree<T>::insert(string key, T *data)
{
    // TODO
    bool taller = false;
    insert(this->root, key, data, taller);
    count++;
}


template <class T>
T* AVLTree<T>::search(Node* root, string key) {
    if (root == nullptr) return nullptr;
    if (compare_string1_to_string2(key, root->key) == 1)
    {
        this->parent_of_searched_node = root;
        return search(root->left, key);
    } 
    else if (compare_string1_to_string2(key, root->key) == -1) 
    {
        this->parent_of_searched_node = root;
        return search(root->right, key);
    }
    else return root->data;
}

template <class T>
T* AVLTree<T>::search(string key) {
    this->parent_of_searched_node = NULL;
    return search(this->root, key);
}

template <class T>
string AVLTree<T>::get_parent_node() {
    if (this->parent_of_searched_node == NULL) return "null";
    return this->parent_of_searched_node->key;
}

template <class T>
bool AVLTree<T>::empty() {
    return root->count == 0;
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::clear(Node* root) {
    if (root == NULL) return NULL;
    if (root->left != NULL) {
        root->left = clear(root->left);
    }
    if (root->right != NULL) {
        root->right = clear(root->right);
    }
    delete root;
    this->count--;
    return NULL;
}

template <class T>
void AVLTree<T>::clear() {
    clear(this->root);
}