#include <iostream>
#include <vector>
#include <algorithm>

template<class T>
class Node {
private:

public:
	T data;
	Node* left;
	Node* right;
	
	Node(int _data) {
		data=_data;
		left=nullptr;
		right=nullptr;
	}

	Node* insert(Node* node, T _data);

};

template<class T>
Node<T>* Node<T>::insert(Node<T>* node, T _data) {
	if(node==nullptr) {
		node = new Node<int>(_data);
	}
	else if(node->data < _data) {
		node->right = insert(node->right, _data);
	}
	else {
		node->left = insert(node->left, _data);
	}
	return node;
}

void postorder(Node<int>* node){
    if(node->left != nullptr){
        postorder(node->left);
    }
    if(node->right != nullptr){
        postorder(node->right);
    }
    std::cout << node->data << '\n';
}


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	Node<int> *root=nullptr;
	int num(0);
	while(std::cin >> num){
        if(num == std::cin.eof())    break;

        root = root->insert(root, num);
    }
	postorder(root);

	return 0;
}