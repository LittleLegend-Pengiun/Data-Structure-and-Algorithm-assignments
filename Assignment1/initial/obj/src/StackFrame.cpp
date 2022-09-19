#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;

StackFrame::StackFrame() {
    opStackMaxSize = OPERAND_STACK_MAX_SIZE;
    localVarArrSize = LOCAL_VARIABLE_ARRAY_SIZE;
    op_stack = new Stack<float>();
    lc_var_spc = new float*[localVarArrSize]{NULL};
    current_line = 0;
}

StackFrame::~StackFrame(){
    delete op_stack;
    for (int i = 0; i < localVarArrSize; i++) {
        float* t = lc_var_spc[i];
        lc_var_spc[i] = NULL;
        if (t) delete t;
    }
    delete[] lc_var_spc;
}

void StackFrame::run(string filename) {
    ifstream fin(filename);
    while (!fin.eof()) {
        current_line += 1;
        string line; getline(fin, line);
        this->operation(line);
    }
}

void StackFrame::operation(string command) {
    int position = (int)command.find(" ");
	string cmd = "", value = "";
	if (position > -1) {
		cmd = command.substr(0, position);
		value = command.substr(position + 1);
	}
	else if (command.find("\r") != string::npos) 
        cmd = command.substr(0, command.length()-1);
    else cmd = command;
	
    
    if (cmd == "iadd") { cmd_iadd(); }
    else if (cmd == "fadd") { cmd_fadd(); }
    else if (cmd == "isub") { cmd_isub(); }
    else if (cmd == "fsub") { cmd_fsub(); }
    else if (cmd == "imul") { cmd_imul(); }
    else if (cmd == "fmul") { cmd_fmul(); }
    else if (cmd == "idiv") { cmd_idiv(); }
    else if (cmd == "fdiv") { cmd_fdiv(); }
    else if (cmd == "irem") { cmd_irem(); }
    else if (cmd == "ineg") { cmd_ineg(); }
    else if (cmd == "fneg") { cmd_fneg(); }
    else if (cmd == "iand") { cmd_iand(); }
    else if (cmd == "ior") { cmd_ior(); }
    else if (cmd == "ieq") { cmd_ieq(); }
    else if (cmd == "feq") { cmd_feq(); }
    else if (cmd == "ineq") { cmd_ineq(); }
    else if (cmd == "fneq") { cmd_fneq(); }
    else if (cmd == "ineg") { cmd_ineg(); }
    else if (cmd == "fneg") { cmd_fneg(); }
    else if (cmd == "ilt") { cmd_ilt(); }
    else if (cmd == "flt") { cmd_flt(); }
    else if (cmd == "igt") { cmd_igt(); }
    else if (cmd == "fgt") { cmd_fgt(); }
    else if (cmd == "ibnot") { cmd_ibnot(); }
    else if (cmd == "iconst") { cmd_iconst(stoi(value)); }
    else if (cmd == "fconst") { cmd_fconst(stof(value)); }
    else if (cmd == "iload") { cmd_iload(stoi(value)); }
    else if (cmd == "istore") { cmd_istore(stoi(value)); }
    else if (cmd == "fload") { cmd_fload(stoi(value)); }
    else if (cmd == "fstore") { cmd_fstore(stoi(value)); }
    else if (cmd == "i2f") { cmd_i2f(); }
    else if (cmd == "f2i") { cmd_f2i(); }
    else if (cmd == "top") { cmd_top(); }
    else if (cmd == "val") { cmd_val(stoi(value)); }
    else {cout << "Other command: " << cmd << endl;} 
}

void StackFrame::cmd_iadd() {
    float type1, type2, value1, value2;
    try {
        type1 = op_stack->pop();
        value1 = op_stack->pop();
        type2 = op_stack->pop();
        value2 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1) throw TypeMisMatch(current_line);
    int new_value = value1 + value2;
    op_stack->push(new_value);
    op_stack->push(0);
}
void StackFrame::cmd_fadd() {
    float value1, value2;
    try {
        value1 = op_stack->pop();
        value1 = op_stack->pop();
        value2 = op_stack->pop();
        value2 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    //if (type1 == 0 || type2 == 0) throw TypeMisMatch(current_line);
    float new_value = value1 + value2;
    op_stack->push(new_value);
    op_stack->push(1);
}

void StackFrame::cmd_isub() {
    float type1, type2, value1, value2;
    try {
        type1 = op_stack->pop();
        value1 = op_stack->pop();
        type2 = op_stack->pop();
        value2 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1) throw TypeMisMatch(current_line);
    int new_value = value2 - value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_fsub() {
    float value1, value2;
    try {
        value1 = op_stack->pop();
        value1 = op_stack->pop();
        value2 = op_stack->pop();
        value2 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    //if (type1 == 0 || type2 == 0) throw TypeMisMatch(current_line);
    float new_value = value2 - value1;
    op_stack->push(new_value);
    op_stack->push(1);
}

void StackFrame::cmd_imul() {
    float type1, type2, value1, value2;
    try {
        type1 = op_stack->pop();
        value1 = op_stack->pop();
        type2 = op_stack->pop();
        value2 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1) throw TypeMisMatch(current_line);
    int new_value = value1 * value2;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_fmul() {
    float value1, value2;
    try {
        value1 = op_stack->pop();
        value1 = op_stack->pop();
        value2 = op_stack->pop();
        value2 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    //if (type1 == 0 || type2 == 0) throw TypeMisMatch(current_line);
    float new_value = value1 * value2;
    op_stack->push(new_value);
    op_stack->push(1);
}

void StackFrame::cmd_idiv() {
    float type1, type2, value1, value2;
    try {
        type1 = op_stack->pop();
        value1 = op_stack->pop();
        type2 = op_stack->pop();
        value2 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1) throw TypeMisMatch(current_line);
    if (value1 == 0) throw DivideByZero(current_line);
    int new_value = (int)(value2 / value1);
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_fdiv() {
    float value1, value2;
    try {
        value1 = op_stack->pop();
        value1 = op_stack->pop();
        value2 = op_stack->pop();
        value2 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    //if (type1 == 0 || type2 == 0) throw TypeMisMatch(current_line);
    if (value1 == 0) throw DivideByZero(current_line);
    float new_value = value2 / value1;
    op_stack->push(new_value);
    op_stack->push(1);
}

void StackFrame::cmd_irem() {
    float type1, type2, value1, value2;
    try {
        type1 = op_stack->pop();
        value1 = op_stack->pop();
        type2 = op_stack->pop();
        value2 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1) throw TypeMisMatch(current_line);
    if (value1 == 0) throw DivideByZero(current_line);

    float new_value = (int)value2 - ((int)value2 / (int)value1) * (int)value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_ineg() {
    float type1, value1;
    try {
        type1 = op_stack->pop();
        value1 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1) throw TypeMisMatch(current_line);
    int new_value = -value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_fneg() {
    float value1;
    try {
        value1 = op_stack->pop();
        value1 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    //if (type1 == 0) throw TypeMisMatch(current_line);
    float new_value = -value1;
    op_stack->push(new_value);
    op_stack->push(1);
}

void StackFrame::cmd_iand() {
    float type1, type2, value1, value2;
    try {
        type1 = op_stack->pop();
        value1 = op_stack->pop();
        type2 = op_stack->pop();
        value2 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1) throw TypeMisMatch(current_line);
    int new_value = (int)value2 & (int)value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_ior() {
    float type1, type2, value1, value2;
    try {
        type1 = op_stack->pop();
        value1 = op_stack->pop();
        type2 = op_stack->pop();
        value2 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1) throw TypeMisMatch(current_line);
    int new_value = (int)value2 | (int)value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_ieq() {
    float type1, type2, value1, value2;
    try {
        type1 = op_stack->pop();
        value1 = op_stack->pop();
        type2 = op_stack->pop();
        value2 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1) throw TypeMisMatch(current_line);
    int new_value = (int)value2 == (int)value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_feq() {
    float value1, value2;
    try {
        value1 = op_stack->pop();
        value1 = op_stack->pop();
        value2 = op_stack->pop();
        value2 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    //if (type1 == 0 || type2 == 0) throw TypeMisMatch(current_line);
    int new_value = value2 == value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_ineq() {
    float type1, type2, value1, value2;
    try {
        type1 = op_stack->pop();
        value1 = op_stack->pop();
        type2 = op_stack->pop();
        value2 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1) throw TypeMisMatch(current_line);
    int new_value = (int)value2 != (int)value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_fneq() {
    float value1, value2;
    try {
        value1 = op_stack->pop();
        value1 = op_stack->pop();
        value2 = op_stack->pop();
        value2 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    //if (type1 == 0 || type2 == 0) throw TypeMisMatch(current_line);
    int new_value = value2 != value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_ilt() {
    float type1, type2, value1, value2;
    try {
        type1 = op_stack->pop();
        value1 = op_stack->pop();
        type2 = op_stack->pop();
        value2 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1) throw TypeMisMatch(current_line);
    int new_value = (int)value2 < (int)value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_flt() {
    float value1, value2;
    try {
        value1 = op_stack->pop();
        value1 = op_stack->pop();
        value2 = op_stack->pop();
        value2 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    //if (type1 == 0 || type2 == 0) throw TypeMisMatch(current_line);
    int new_value = value2 < value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_igt() {
    float type1, type2, value1, value2;
    try {
        type1 = op_stack->pop();
        value1 = op_stack->pop();
        type2 = op_stack->pop();
        value2 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    if (type1 == 1 || type2 == 1) throw TypeMisMatch(current_line);
    int new_value = (int)value2 > (int)value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_fgt() {
    float value1, value2;
    try {
        value1 = op_stack->pop();
        value1 = op_stack->pop();
        value2 = op_stack->pop();
        value2 = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    //cout << type1 << " " << type2 << " " << value1 << " " << value2 << endl;
    //if (type1 == 0 || type2 == 0) throw TypeMisMatch(current_line);
    int new_value = value2 > value1;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_ibnot() {
    float type, value;
    try {
        type = op_stack->pop();
        value = op_stack->pop();
    }
    catch (const std::out_of_range& e) {
        throw StackEmpty(current_line);
    }
    if (type == 1) throw TypeMisMatch(current_line);
    int new_value = (int)value == 0;
    op_stack->push(new_value);
    op_stack->push(0);
}

void StackFrame::cmd_iconst(float value) {
    if (op_stack->size() == opStackMaxSize) throw StackFull(current_line);
    op_stack->push(value);
    op_stack->push(0);
    //cout << "iconst called, last value: " << op_stack->back() << "\n";
}

void StackFrame::cmd_fconst(float value) {
    if (op_stack->size() == opStackMaxSize) throw StackFull(current_line);
    op_stack->push(value);
    op_stack->push(1);
}

void StackFrame::cmd_iload(int idx) {
    if (idx % 2 == 1) idx = idx - 1;;
    if (idx >= localVarArrSize || idx < 0) 
        throw ArrayOutOfRange(current_line);
    
    if (lc_var_spc[idx] == NULL) 
        throw UndefinedVariable(current_line);
    
    if (*lc_var_spc[idx] == 1) throw TypeMisMatch(current_line);

    cmd_iconst((int)*lc_var_spc[idx+1]);
}

void StackFrame::cmd_fload(int idx) {
    if (idx % 2 == 1) idx = idx - 1;
    if (idx >= localVarArrSize || idx < 0) 
        throw ArrayOutOfRange(current_line);
    
    if (lc_var_spc[idx] == NULL) 
        throw UndefinedVariable(current_line);
    
    if (*lc_var_spc[idx] == 0) throw TypeMisMatch(current_line);

    cmd_fconst((float)*lc_var_spc[idx+1]);
}

void StackFrame::cmd_istore(int idx) {
    int type, val;
    try {
        type = op_stack->pop();
        val = op_stack->pop();
    }
    catch (const out_of_range& e) {
        throw StackEmpty(current_line);
    }

    if  (type == 1) throw TypeMisMatch(current_line);
    
    if (idx >= localVarArrSize || idx < 0) 
        throw ArrayOutOfRange(current_line); 

    if (lc_var_spc[idx] == NULL) 
        lc_var_spc[idx] = new float(type);
    else *lc_var_spc[idx] = type;

    if (lc_var_spc[idx+1] == NULL)
        lc_var_spc[idx+1] = new float(val);
    else *lc_var_spc[idx+1] = val;
}

void StackFrame::cmd_fstore(int idx) {
    float type, val;
    try {
        type = op_stack->pop();
        val = op_stack->pop();
    }
    catch (const out_of_range& e) {
        throw StackEmpty(current_line);
    }

    if  (type == 0) throw TypeMisMatch(current_line);
    
    if (idx >= localVarArrSize || idx < 0) 
        throw ArrayOutOfRange(current_line);
    
    if (lc_var_spc[idx] == NULL) 
        lc_var_spc[idx] = new float(type);
    else *lc_var_spc[idx] = type;

    if (lc_var_spc[idx+1] == NULL)
        lc_var_spc[idx+1] = new float(val);
    else *lc_var_spc[idx+1] = val;
}
void StackFrame::cmd_i2f() {
    int type, value;
    try {
        type = op_stack->pop();
        value = op_stack->pop();
    }
    catch (const out_of_range& e) {
        throw StackEmpty(current_line);
    }

    if (type == 1) throw TypeMisMatch(current_line);

    cmd_fconst((float)value);
}

void StackFrame::cmd_f2i() {
    float type, value;
    try {
        type = op_stack->pop();
        value = op_stack->pop();
    }
    catch (const out_of_range& e) {
        throw StackEmpty(current_line);
    }

    if (type == 0) throw TypeMisMatch(current_line);
    
    cmd_iconst(static_cast<int>(value));
}

void StackFrame::cmd_top() {
    if (op_stack->empty()) throw StackEmpty(current_line);
    cout << op_stack->top() << "\n";
}

void StackFrame::cmd_val(int index) {
    if (lc_var_spc[index+1] == NULL) throw UndefinedVariable(current_line);
    cout << *lc_var_spc[index+1] << "\n";
}


/* ===================================================================
======================================================================
======================================================================
======================================================================
=================================================================== */
/* Initial of other data structures */

// Stack implementation
template<class T>
Stack<T>::Stack() {
    this->list = new DLinkedList<T>();
}

template<class T>
Stack<T>::~Stack() {
    this->clear();
    delete list;
}

template<class T>
void Stack<T>::push(const T &item) {
    list->add(0, item);
}


template<class T>
T Stack<T>::pop() {
    return list->removeAt(0);
}


template<class T>
T Stack<T>::top() {
    return list->get(1);   
}

template<class T>
bool Stack<T>::empty() {
    return list->empty();

}

template<class T>
int Stack<T>::size() {
    return list->size();
      
}

template<class T>
void Stack<T>::clear() {
    list->clear();
}

/* ================================================================ */
// Node
template<class T>
Node<T>::Node(): previous(NULL), next(NULL) {}

template<class T>
Node<T>::Node(const T& data): data(data), 
                        previous(NULL), 
                        next(NULL) 
                        {}

/* ================================================================ */
// DLinkedList
template<class T>
DLinkedList<T>::DLinkedList(): head(NULL),
                               tail(NULL)
                               {}

template<class T>
DLinkedList<T>::~DLinkedList() {
    this->clear();
}

template<class T>
void DLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    Node<T>* temp = new Node<T>(e);
    if (this->count == 0) {
        this->head = temp;
        this->tail = temp;
        this->count++;
        return;
    }
    (this->tail)->next = temp;
    temp->previous = this->tail;
    this->tail = temp;
    this->count++;
}

template <class T>
void DLinkedList<T>::add (int index, const T& e) {
    /* Insert an element into the list at given index. */ 
    Node<T>* temp = new Node<T>(e);
    Node<T>* travel = this->head;
    if (index < 0 || index > count) return;
    if (count == 0 || index == count) 
    {
        this->add(e);
        return;
    }
    if (index == 0) {
        temp->next = this->head;
        this->head->previous = temp;
        this->head = temp;
        this->count++;
        return;
    }
    while (index >=0){ 
        if (index == 1) {
            temp->next = travel->next;
            travel->next = temp;
            temp->previous = travel;
            temp->next->previous = temp;
            this->count = this->count + 1;
            return;
        }
        index--;
        travel = travel->next;
    }
}

template <class T>
int DLinkedList<T>::size() {
    /* Return the length (size) of list */ 
    return this->count;
}

template<class T>
T DLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    if (index < 0 || index >= this->count) return T();
    if (index == 0)  return this->head->data; 
    if (index == this->count - 1)  return this->tail->data; 

    Node<T>* walker = this->head;
    for (int i = 0; i < index; ++i)
        walker = walker->next;
    return walker->data;
}

template <class T>
void DLinkedList<T>::set(int index, const T& e) {
    /* Assign new value for element at given index in the list */
    if (index < 0 || index >= this->count) return;
    if (index == 0)  this->head->data = e;
    if (index == this->count - 1) this->tail->data = e;

    Node<T>* walker = this->head;
    for (int i = 0; i < index; i++)
        walker = walker->next;
    walker->data = e;
}

template<class T>
bool DLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    return this->count == 0;
}

template<class T>
int DLinkedList<T>::indexOf(const T& item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    if (this->head->data == item) return 0;
    if (this->tail->data == item) return this->count - 1;
    
    int index = 0;
    Node<T>* walker = this->head;
    
    while (walker) {
        if (walker->data == item) return index;
        walker = walker->next;
        index++;
    }
    return -1;
}

template<class T>
bool DLinkedList<T>::contains(const T& item) {
    /* Check if item appears in the list */
    if (this->head->data == item) return true;
    if (this->tail->data == item) return true;

    int index = 0;
    Node<T>* walker = this->head;

    while (walker) {
        if (walker->data == item) return true;
        walker = walker->next;
        ++index;
    }
    return false;
}

template <class T>
T DLinkedList<T>::removeAt(int index)
{
    if (index < 0 || index > count - 1) throw std::out_of_range("This is out of range!");
    this->count--;

    if (index == 0) {
        Node<T>* remove_node = this->head;       
        this->head = this->head->next;
        T return_value = remove_node->data;
        delete remove_node;
        if (this->head) this->head->previous = nullptr;
        if (!this->head) this->tail = nullptr;
        return return_value;
    }
    if (index == this->count) {
        Node<T>* remove_node = this->tail;
        this->tail = this->tail->previous;
        
        T return_value = remove_node->data;
        delete remove_node;
        
        if (this->tail) this->tail->next = nullptr;
        return return_value;
    }
    
    Node<T>* remove_node = head;
        
    while (index--) {
        remove_node = remove_node->next;
    }
    T return_value = remove_node->data;

    remove_node->previous->next = remove_node->next;
    remove_node->next->previous = remove_node->previous;
    
    delete remove_node;
    return return_value;
}

template <class T>
bool DLinkedList<T>::removeItem(const T& item)
{
    /* Remove the first apperance of item in list and return true, otherwise return false */
    if (!this->head) return false;
    int i = 0;
    for (Node<T>* current = this->head; current != nullptr; ++i, current = current->next) {
        if (current->data == item) {
            this->removeAt(i);
            return true;
        }
    }
    return false;
}

template<class T>
void DLinkedList<T>::clear() {
    /* Remove all elements in list */
    while (this->head) {
        Node<T>* remove_node = this->head;
        this->head = this->head->next;
        delete remove_node;
    }
    this->count = 0;
    this->head = nullptr;
    this->tail = nullptr;
}