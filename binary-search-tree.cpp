#include <iostream>
#include <stack>
#include <vector>
struct Node{
	int key;
	Node *left;
	Node *right;
	Node *parent;
	Node(int data){
		this->key = data;
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;
	}
};

Node* iterativeSearch(Node* root, int val){
	Node* pos = root;
	while(pos != nullptr and pos->key != val){
		if(val < pos->key)
			pos = pos->left;
		else
			pos = pos->right;
	}
	return pos;
}

Node* recursiveSearch(Node *root, int val){
	if(root == nullptr or root->key == val)
		return root;
	if(val < root->key)
		return recursiveSearch(root->left, val);
	else
		return recursiveSearch(root->right, val);
}


Node* minimumIterative(Node *root){
	Node *leaf = root;
	while(leaf->left != nullptr)
		leaf = leaf->left;
	return leaf;
}

Node* maximumIterative(Node *root){
	Node *leaf = root;
	while(leaf->right != nullptr)
		leaf = leaf->right;
	return leaf;
}

void printRecursive(Node *root){
	if(root != nullptr){
		printRecursive(root->left);
		std::cout << root->key << "    ";
		printRecursive(root->right);
	}
}

Node* minimumRecursive(Node *root){
	if(root->left == nullptr)
		return root;
	return minimumRecursive(root->left);
}

Node* maximumRecursive(Node *root){
	if(root->right == nullptr)
		return root;
	return maximumRecursive(root->right);
}


void printIterative(Node *root){
	std::stack<Node*> values;
	values.push(root);
	while(!values.empty()){
		Node* upper = values.top();
		values.pop();
		if(upper != nullptr){
			std::cout << upper->key << "    ";
			values.push(upper->left);
			values.push(upper->right);
		}
	}
}

Node* successor(Node *x){
	if(x->right != nullptr)
		return minimumIterative(x->right);
	Node *par = x->parent;
	//Find lowest ancestor of x whose left child is also an ancestor of x.
	while(par != nullptr and  x == par->right){
		x = par;
		par = par->parent;
	}
	return par;
}

Node *prdecessor(Node *x){
	if(x->left != nullptr)
		return maximumIterative(x);
	Node *par = x->parent;
	//find highest ancestor of x whose right child is also an ancestor of x.
	while(par != nullptr and par->left == x){
		x = par;
		par = par->parent;
	}
	return par;
}

void insertNode(Node *root, int data){
	Node* parent = nullptr;
	Node* pos = root;
	Node* newNode = new Node(data);
	while(pos != nullptr){
		parent = pos;
		if(data < pos->key)
			pos = pos->left;
		else
			pos = pos->right;
	}
	newNode->parent = parent;
	if(parent == nullptr)
		root = newNode;
	if(data < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;
}

void transplant(Node *root, Node *initial, Node *final){
	if(initial->parent == nullptr)
		root = final;
	else{
		if(initial->parent->left == initial)
			initial->parent->left = final;
		else
			initial->parent->right = final;
	}
	if(final != nullptr)
		final->parent = initial->parent;
}

void deleteNode(Node *root, int val){
	Node *toDelete = recursiveSearch(root, val);
	if(toDelete == nullptr)
		return;
	if(toDelete->left == nullptr)
		transplant(root, toDelete, toDelete->right);
	else if(toDelete->right == nullptr)
		transplant(root, toDelete, toDelete->left);
	else{
		Node* succ = successor(toDelete);
		if(succ->parent != toDelete){
			transplant(root, succ, succ->parent);
			succ->right = toDelete->right;
			succ->right->parent = succ;
		}
		transplant(root, toDelete, succ);
		succ->left = toDelete->left;
		succ->left->parent = succ;
	}
}

int main(){
	//Testing Code Goes here.
	int n;
	std::cout << "Enter number of values to arrange in BST: ";
	std::cin >> n;
	std::vector<int> arr(n);
	std::cout << "Enter the values to be arranged: ";
	for(int i{0}; i < n; i++)
		std::cin >> arr[i];
	if(n == 0)
		return 0;
	Node* root = new Node(arr[0]);
	for(int i{1}; i < n; i++)
		insertNode(root, arr[i]);
	int x;
	std::cout << "Enter Node to be deleted: ";
	std::cin >> x;
	deleteNode(root, x);
	printRecursive(root);
	std::cout << '\n';
	return 0;
}