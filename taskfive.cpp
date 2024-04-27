#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <unordered_map>
#include <memory>
using namespace std;

struct TreeNode {
    string value;
    shared_ptr<TreeNode> left;
    shared_ptr<TreeNode> right;
    TreeNode(string val) : value(val), left(nullptr), right(nullptr) {}
};

bool isOperator(const string& c) {
    return c == "+" || c == "-" || c == "*" || c == "/";
}

int evaluateExpression(shared_ptr<TreeNode> node, const unordered_map<string, int>& variables) {
    if (node == nullptr) return 0;
    if (isOperator(node->value)) {
        int left = evaluateExpression(node->left, variables);
        int right = evaluateExpression(node->right, variables);
        if (node->value == "+") return left + right;
        if (node->value == "-") return left - right;
        if (node->value == "*") return left * right;
        if (node->value == "/") return left / right;  // Assume right is not zero
    } else if (isdigit(node->value[0]) || node->value[0] == '-') {
        return stoi(node->value);
    } else {
        // It's a variable
        return variables.at(node->value);
    }
    return 0;  // Should never reach here
}

shared_ptr<TreeNode> constructTree(const string& expr) {
    stack<shared_ptr<TreeNode>> nodes;
    string token;
    for (char c : expr) {
        if (isspace(c)) continue;
        if (c == '(') {
            // No action needed, just a marker
        } else if (c == ')') {
            // Pop two operands and one operator, and link them
            auto right = nodes.top(); nodes.pop();
            auto op = nodes.top(); nodes.pop();
            auto left = nodes.top(); nodes.pop();
            op->left = left;
            op->right = right;
            nodes.push(op);
        } else if (isdigit(c) || c == '-' || isalpha(c)) {
            token = c;
            if (c == '-' || isalpha(c)) {  // Support negative numbers or variable names like x1
                while (!nodes.empty() && isalpha(nodes.top()->value[0])) {
                    token += nodes.top()->value;
                    nodes.pop();
                }
            }
            nodes.push(make_shared<TreeNode>(token));
        } else if (isOperator(string(1, c))) {
            nodes.push(make_shared<TreeNode>(string(1, c)));
        }
    }
    return nodes.top();
}

void printTree(const shared_ptr<TreeNode>& node, int space = 0) {
    if (node == nullptr) return;
    space += 10;
    printTree(node->right, space);
    cout << endl;
    for (int i = 10; i < space; i++) cout << " ";
    cout << node->value << "\n";
    printTree(node->left, space);
}

int main() {
    string expression;
    cout << "Enter a fully parenthesized expression: ";
    getline(cin, expression);
    auto root = constructTree(expression);

    unordered_map<string, int> variables = {
        {"x1", 0}, {"x2", 0}, {"x3", 0}  // Pre-initialized variables
        // Add more if needed
    };

    printTree(root);
    cout << "Value at root: " << evaluateExpression(root, variables) << endl;

    // Interactive variable update
    char choice = 'y';
    string varName;
    int varValue;
    while (choice == 'y') {
        cout << "Enter a variable name to update (e.g., x1): ";
        cin >> varName;
        cout << "Enter new value for " << varName << ": ";
        cin >> varValue;
        variables[varName] = varValue;
        cout << "Updated value at root: " << evaluateExpression(root, variables) << endl;
        cout << "Do you want to update another variable? (y/n): ";
        cin >> choice;
    }

    return 0;
}
