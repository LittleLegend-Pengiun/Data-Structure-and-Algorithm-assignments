#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__

#include <string>
#include <stack>

using namespace std;
/*
StackFrame declaration
*/
enum Balance_value {
    LH = -1,
    EH = 0,
    RH = 1,
};

class Value_and_type {
public:
    float value;
    bool type;
    Value_and_type(float value, bool type) : value(value), type(type) {}
    Value_and_type(const Value_and_type* &obj) : value(obj->value), type(obj->type) {}
};

template <class T>
class AVLTree {
    class Node;
    Node *root;
    int count;
    T* delete_data;
    Node* parent_of_searched_node;
private: 
    class Node {
    public:
        string key;
        Node* left;
        Node* right;
        T* data;
        Balance_value balance;
        Node(string key, T* data) {
            this->key = key;
            this->left = NULL;
            this->right = NULL;
            this->data = data;
            this->balance = EH;
        }
        ~Node() {
            delete this->data;
            this->data = NULL;
        }
    };
protected:
    int getHeightRec(Node *node);
    int compare_string1_to_string2 (const string&, const string&);
    Node* rotate_left (Node* &node);
    Node* rotate_right (Node* &node);

    Node* left_balance (Node* &node, bool&);
    Node* right_balance (Node* &node, bool&);
    Node* insert (Node* &node, string key, T* data, bool& taller);

    T* search (Node*, string key);
    Node* clear(Node* root);
public:
    AVLTree();
    ~AVLTree();
    void insert(string key, T* data);
    int get_height();
    int size();
    T* search (string key);
    bool empty();
    void clear();
    string get_parent_node();
};

class StackFrame {
    int opStackMaxSize; // max size of operand stack
    int localVarArrSize; // size of local variable array
    stack<float>* op_stack;
    AVLTree<Value_and_type>* lc_var_spc;
    int current_line;
    // Methods
    void operation(std::string command); // run the command

    // List of command functions
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
    void cmd_iconst(float value);
    void cmd_fconst(float value);
    void cmd_iload(string var);
    void cmd_fload(string var);
    void cmd_istore(string var);
    void cmd_fstore(string var);
    void cmd_i2f();
    void cmd_f2i();
    void cmd_top();
    void cmd_val(string var);
    void cmd_par(string var);
public:
    /*
    Constructor of StackFrame
    */
    StackFrame(); // constructor
    ~StackFrame(); // destructor
    /*
    Run the method written in the testcase
    @param filename name of the file
    */
    void run(std::string filename);
};

#endif // !__STACK_FRAME_H__