#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include "z3++.h"
using std::string;
using std::vector;
using std::map;
using std::stack;
using namespace z3;

#include "multree.h"
#include "cfg.h"
#include "minisee.h"


// 下面两个print函数或许能帮你debug
// 输出程序流图root对应的代码
void print_cfg(cfg_node* root);
// 输出表达式树root存储的表达式
void print_exp(exp_node* root);

extern stack<see_state> state_queue;


// 把字符串表示的数字转成int类型带符号整数
// s可能是10进制无符号整数、10进制带符号整数或16进制整数
int mystoi(string s) {
    // your code here

    // to set the base to read from the string
    int base = 10;
    if (s.length() >= 3 && s[0] == '0' && s[1] == 'x') base = 16;

    return std::stoll(s, nullptr, base);
}


// root是一棵表达式树
// 如果root为NULL，就返回NULL
// 否则，就生成一棵新的树，这棵树表示的表达式和root表示的完全一致
// 但是这棵树的所有节点都是new出来的，不可以复用root中的任何节点
exp_node* copy_exp_tree(exp_node* root) {
    // your code here
    if (!root) return nullptr;

    // create a root for the new expression tree
    exp_node* new_root = new exp_node(
        root->type,
        root->val,
        copy_exp_tree(root->child[0]),
        copy_exp_tree(root->child[1])
    );

    return new_root;
}


// 这个函数用于处理if语句
// state是if语句对应的符号执行节点
// path_const是state里面的path constraint
// condition表示if条件表达式
// branch是true时返回if条件为真对应的新的path constraint
// branch是false时返回if条件为假对应的新的path constraint
exp_node* update_path_const(see_state* state, exp_node* path_const, bool branch, exp_node* condition) {
    
    // old_const是和state里面的path constraint一样的表达式
    exp_node* old_const = copy_exp_tree(path_const);
    // cur_const是当前if条件对应的表达式
    exp_node* cur_const = update_exp_tree(state, condition);

    // exp是新的path constraint
    exp_node* exp = NULL;
    if(old_const) {
        // 如果当前state里面的path constraint不是true
        exp = new exp_node(exp_op, "&&", old_const);
        if(branch) {
            exp->child[1] = cur_const;
        }
        else {
            exp->child[1] = new exp_node(exp_op, "!", cur_const);
        }
    }
    else {
        if(branch) {
            exp = cur_const;
        }
        else {
            exp = new exp_node(exp_op, "!", cur_const);
        }
    }

    return exp;
}


// 处理if语句
// state中的cfg第一条语句就是一个if语句
void analyze_if(see_state* state) {
    // your code here, you may need to use update_path_const
    const cfg_node* cur_cfg = state->cfg;
    assert(cur_cfg->type == cfg_if);

    // get path constraints for both the true and false conditions
    exp_node* true_if = update_path_const(state, state->path_const, true, cur_cfg->exp_tree);
    exp_node* false_if = update_path_const(state, state->path_const, false, cur_cfg->exp_tree);

    // create next nodes
    see_state* true_node = new see_state(cur_cfg->next[0], true_if);
    see_state* false_node = new see_state(cur_cfg->next[1], false_if);
    true_node->sym_store = state->sym_store;
    false_node->sym_store = state->sym_store;

    // push the nodes into the stack
    state_queue.push(*true_node);
    state_queue.push(*false_node);

    return;
}
