#pragma once

#include <string>
#include <iostream>
struct node {
    char data;
    node* left;
    node* right;

    node(const char& _data, node * _left = nullptr, node * _right = nullptr)
        : data(_data), left(_left), right(_right) {}
    
    bool is_leaf() const {
        return left == nullptr && right == nullptr;
    }
    
    ~node(){
        delete left;
        delete right;
    }
};

int prio (const char& x){
     switch (x) {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        default: return 3;
    }
}

std::string parenthesize (const std::string& expr){
    return "("+ expr + ')';
}

std::string get_expression(node *const& expr_tree){
    if(expr_tree->is_leaf()) 
        return std::string(1, expr_tree->data);
    
    return (prio(expr_tree->left->data) < prio(expr_tree->data) 
                ? parenthesize(get_expression(expr_tree->left))
                : get_expression(expr_tree->left))
           + 
           expr_tree->data
           +
           (prio(expr_tree->right->data) < prio(expr_tree->data)
                ? parenthesize(get_expression(expr_tree->right))
                : get_expression(expr_tree->right));
}

node* get_tree(const std::string& expr){
    auto begin = expr.begin();
    auto end = expr.end();

    char num = *(begin++);
    node* right_node = nullptr;

    if(num == '('){
        std::clog << "first " << begin - expr.begin();
        auto index = expr.find(')', begin - expr.begin());
        right_node = get_tree(expr.substr(begin - expr.begin() , index - (begin - expr.begin())));
        begin = expr.begin() + index + 1; 
    } else {
        right_node = new node(num);
    }
    
    // If a single number.
    if(begin == end)
        return right_node;
    
    char op = *(begin++);
    
    node* root = new node(op, right_node);
    node* empty_right = root;

    int last_prio = prio(op);
    
    while(true){
        num = *(begin++);
        if(num == '('){
            std::clog << "deep " << begin - expr.begin();
            auto index = expr.find(')', begin-expr.begin());
            right_node = get_tree(expr.substr(begin - expr.begin() , index - (begin - expr.begin())));
            begin = expr.begin() + index + 1; 
        } else {
            right_node = new node(num);
        }
        if(begin == end){
            empty_right->right = right_node;
            return root;
        }

        op = *(begin++);
        
        if (prio(op) > last_prio) {
            empty_right->right = new node(op, right_node);
            empty_right = empty_right->right; 
        } else {
            root = new node(op, root);
            empty_right->right = right_node;
            empty_right = root;
        }
        
        last_prio = prio(op);
    }
    return root;
}