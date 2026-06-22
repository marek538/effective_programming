#include <iostream>
#include <memory>

using namespace std;

class CNode{
public:
    bool isValue = false;
    int value = 0;
    string function = "";

    shared_ptr<CNode> left = nullptr;
    shared_ptr<CNode> right = nullptr;
    shared_ptr<CNode> parent = nullptr;
    shared_ptr<CNode> thisPtr = nullptr;

    bool insertNode(shared_ptr<CNode> node) {
        if(left == nullptr){
            left = node;
            node->parent = thisPtr;
            return true;
        }
        else if(right == nullptr){
            right = node;
            node->parent = thisPtr;
            return true;
        }
        return false;
    }


    string print(string &res)
    {
        if(left != nullptr && left -> isValue ) {
            res += to_string(left->value);
            res += " ";
        }
        else if(left != nullptr)
            left->print(res);

        if(right != nullptr && right -> isValue ) {
            res += to_string(right->value);
            res += " ";
        }
        else if(right != nullptr)
            right->print(res);

        if(!isValue)
            res += function;
        else
            res += to_string(value);
        res += " ";

        return res;

    }
};

int main() {
    while(true){
        // JEDEN PROBLEM


        string text;
        getline(cin, text);

        if(text == "0") break;

        shared_ptr<CNode> head = nullptr;

        for (char c : text){
            if (c == ' ')
                continue;
            auto current = make_shared<CNode>();
            current->thisPtr = current;
            if(c >= '0' && c <= '9')
            {
                current->isValue = true;
                current->value = c - '0';
            }
            else if(c == '+' || c == '-' || c == '*' || c == '/')
                current->function = c;


            // insert
            if(head == nullptr) {
                head = current;
            }
            else
            {
                while(!head->insertNode(current))
                {
                    head = head->parent;
                }
                if(!current->isValue)
                    head = current;
            }
        }

        while(head->parent != nullptr)
            head = head->parent;


        string res = "";
        head->print(res);
        cout << res << endl;
    }


    return 0;
}
