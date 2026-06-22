#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class CNode
{
public:
    int value;
    shared_ptr<CNode> parent = nullptr;
    vector<shared_ptr<CNode>> children;
    bool isLeaf = true;
};


vector<int> parseString(string text)
{
    vector<int> parsed;
    for(char c : text)
    {
        int val;
        if (c >= '0' && c <= '9') val = c - '0';
        else val = c - 'A' + 10;

        for(int shift = 3; shift >= 0; shift--) {
            if (((val >> shift) & 1) > 0)
                parsed.push_back(1);
            else
                parsed.push_back(0);
        }
    }
    return parsed;
}

void removePadding(vector<int>& parsed)
{
    uint i = 0;
    while(i < parsed.size() && parsed[i] == 0)
        i++;

    // remove first 1
    i++;
    parsed.erase(parsed.begin(), parsed.begin() + i);
}

shared_ptr<CNode> parseTreeRec(const vector<int> &parsed, int &pos) {
    if (pos >= (int)parsed.size()) return nullptr;

    shared_ptr<CNode> node = make_shared<CNode>();
    int bit = parsed[pos];

    if (bit == 1) {
        node->isLeaf = true;
        pos++;
        node->value = parsed[pos];
        pos++;
    } else {
        node->isLeaf = false;
        node->value = -1;
        node->children.resize(4);
        pos++;
        for (int i = 0; i < 4; i++)
            node->children[i] = parseTreeRec(parsed, pos);
    }
    return node;
}



shared_ptr<CNode> buildTree(string text){
    vector<int> parsed = parseString(text);
    removePadding(parsed);

    int i = 0;
    return parseTreeRec(parsed, i);
}

void test()
{
    // TODO
    int i = 0;
    vector<int> parsed = parseString({1,1});
    auto tmp = parseTreeRec(parsed, i);

    parsed = {0,1,1,1,1,1,1,1,0};
    i = 0;
    auto tmp2 = parseTreeRec(parsed, i);

    parsed = {0,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0};
    i = 0;
    auto tmp3 = parseTreeRec(parsed, i);
}

int main() {

    test();

    bool second = false;
    vector<shared_ptr<CNode>> nodes;

    while(true)
    {
        string text;
        getline(cin, text);

        if (text == "0" && second)
            break;
        else if(text == "0")
            second = true;

        shared_ptr<CNode> node;
        node = buildTree(text);
        nodes.push_back(node);

        if(nodes.size() == 2)
        {
            // TODO - compare trees
            nodes.clear();
        }

    }

    return 0;
}
