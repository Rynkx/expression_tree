#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>

#include "expression_tree.hpp"

TEST_CASE ("wacky example of tree to expression"){
    node* root = new node('*',
                               new node('+',
                                             new node('3'),
                                             new node('4')),
                               new node('*', 
                                             new node('-',
                                                          new node('5'),
                                                          new node('2')),
                                             new node('+', 
                                                          new node('3'),
                                                          new node('2'))));
    std::string result = get_expression(root);
    CHECK(result == "(3+4)*(5-2)*(3+2)");
}

TEST_CASE ("tree from expr, no parentheses"){
    std::string expr = "(5+4*3-2-1)*(3+5*(3-2*6))*(8-3*5)";
    node* expr_tree = get_tree(expr);
    std::string result = get_expression(expr_tree);
    CHECK (result == expr);
}