#include <iostream>
#include <memory>
#include <set>

using namespace std;

class CNode {
public:
    shared_ptr<CNode> left;
    shared_ptr<CNode> right;
//    shared_ptr<CNode> parent;
    int value;

    CNode(int val) : value(val), left(nullptr), right(nullptr) {}

    void addValue(int val) {
        if (val < value) {
            if (left) {
                left->addValue(val);
            } else {
                left = make_shared<CNode>(val);
            }
        } else {
            if (right) {
                right->addValue(val);
            } else {
                right = make_shared<CNode>(val);
            }
        }
    }

    string printTree()
    {
        string result = "(";
        if (left) {
            result += left->printTree();
        } else {
            result += "null";
        }
        result += " <- val -> ";
        if (right) {
            result += right->printTree();
        } else {
            result += "null";
        }
        result += ")";
        return result;
    }

};

int main() {
    int lines, numbers;
    cin >> lines >> numbers;

    set<string> uniqueTrees;

    for(int i = 0; i < lines; i++)
    {
        shared_ptr<CNode> root = nullptr;
        for(int j = 0; j < numbers; j++)
        {
            int val;
            cin >> val;
            if (!root) {
                root = make_shared<CNode>(val);
            } else {
                root->addValue(val);
            }
        }

        uniqueTrees.insert(root->printTree());

    }

    cout << uniqueTrees.size() << endl;
    return 0;
}
