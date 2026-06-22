#include <bitset>
#include <iomanip>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

class CNode;
using namespace std;

class CNode {
public:
    int size = 0;
    char result = '-';

    pair<int, int> position;
    vector<CNode*> children;
    CNode* parent = nullptr;


    CNode()= default;
};

string returnLine(string line, int start) {
    int hex = 0;
    for (int i = start; i < start + 8; ++i) {
        // int pos = 7 - (i % 8);
        int pos = i % 8;

        if (line[i] == 'B')
            hex |= (1 << pos);

    }
    // return bitset<8>(hex).to_string();

    stringstream ss;
    ss << "0x"
       << std::hex
       << std::nouppercase
       << std::setfill('0')
       << std::setw(2)
       << hex;

    return ss.str();
}


class CProblem {
public:
    int pixels;
    string code;
    vector<string> image;
    CNode* root = nullptr;


    CProblem(int pixels, string code): pixels(pixels), code(code)
    {
        for (int i = 0; i < pixels; ++i)
            image.emplace_back(pixels, ' ');
    }

    void fillImage(CNode* node) {
        for (int i = 0; i < node->size; ++i) {
            for (int j = 0; j < node->size; ++j) {
                image[node->position.first + i][node->position.second + j] = node->result;
            }
        }
    }

    ~CProblem() {
        freeTree(root);
    }

    void freeTree(CNode* ptr) {
        if (ptr != nullptr) {
            for (auto child : ptr->children) {
                freeTree(child);
            }
            delete ptr;
        }
    }

    void buildTree() {

        root = new CNode();
        root->size = pixels;
        root->position = make_pair(0, 0);
        root->result = code[0];

        fillImage(root);

        CNode* current = root;
        for (int i = 1; i < code.size(); ++i) {
            while (current->children.size() == 4) {
                current = current->parent;
                if (current == nullptr)
                    return;
            }

            CNode* child = new CNode();
            child->size = current->size/2;
            child->position = current->position;

            // count coordinates
            if (current->children.size() == 1 || current->children.size() == 3)
                child->position.second = child->position.second + child->size;
            if (current->children.size() == 2 || current->children.size() == 3)
                child->position.first = child->position.first + child->size;

            // fill table
            if (code[i] == 'W' || code[i] == 'B') {
                child->result = code[i];
                current->children.emplace_back(child);
                child->parent = current;

                fillImage(child);
            }
            // further recursion
            else {

                child->result = 'Q';
                current->children.emplace_back(child);
                child->parent = current;
                current = child;
            }
        }

        return;
    }


    void printImage() {
        for (int i = 0; i < pixels; ++i) {
            for (int j = 0; j < pixels; ++j) {
                cout << image[i][j];
            }
            cout << endl;
        }
    }

    void printResult() {
        cout << "#define quadtree_width " << pixels << endl;
        cout << "#define quadtree_height " << pixels << endl;
        cout << "static char quadtree_bits[] = {" << endl;

        for (const auto& line: image) {
            for (int i = 0; i < pixels/8; i++) {
                cout << returnLine(line, i * 8) << ",";
            }
            cout << endl;
        }

        cout << "};" << endl;
    }

};



CProblem readInput() {
    int pixels;
    cin >> pixels;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string text;
    getline(cin, text);

    CProblem problem(pixels, text);
    return problem;
}


int main() {
    CProblem problem = readInput();
    problem.buildTree();
    // problem.printImage();
    problem.printResult();
    // cout << returnLine("WBBBBWWB", 0);
    return 0;
}