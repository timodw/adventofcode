#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>


class tree_node {
    public:
        std::string name;
        std::unordered_set<tree_node*> children;
        int weight;
        tree_node* parent = nullptr;
        tree_node(std::string n, int w) {name = n; weight = w;};
        tree_node(std::string n) {name = n;};
};

void process_line(std::string);
void add_child(tree_node*, std::string);

std::unordered_map<std::string, tree_node*> nodes;
tree_node* root = nullptr;

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            process_line(line);
        }
        std::cout << "SOLUTION: " << root->name;
    }
    return 0;
}

void process_line(std::string line) {

    int start = 0;
    int end = line.find(" ");
    std::string name = line.substr(start, end);
    start = end + 2;
    end = line.find(")");
    int weight = atoi(line.substr(start, end - start).c_str());

    if (nodes.find(name) == nodes.end()) {
        tree_node* node = new tree_node(name, weight);
        nodes[name] = node;
    } else {
        nodes[name]->weight = weight;
    }
    tree_node* parent = nodes[name];
    if (root == nullptr) {
        root = parent;
    }
    start = line.find("->");
    if (start != std::string::npos) {
        std::string children = line.substr(start + 3);
        int start = 0;
        int end = children.find(", ");
        while (end != std::string::npos) {
            std::string name = children.substr(start, end - start);
            add_child(parent, name);
            start = end + 2;
            end = children.find(", ", start);
        }
        std::string name = children.substr(start);
        add_child(parent, name);
    }
    if (root->parent != nullptr) root = root->parent;
}

void add_child(tree_node* parent, std::string child_name) {
    if (nodes.find(child_name) != nodes.end()) {
        //child already in map
        nodes[child_name]->parent = parent; 
    } else {
        tree_node* new_node = new tree_node(child_name); 
        new_node->parent = parent;
        nodes[child_name] = new_node; 
    }
    parent->children.insert(nodes[child_name]);
    if (nodes[child_name] == root) root = parent;
}
