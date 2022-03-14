#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

void print_vector(const vector<int> &A);
void insertion_sort();
void merge_sort();
void merge_helper(vector<int> &A, int left, int right);
void merge(vector<int> &A, int left, int mid, int right);
void quick_sort();
void quick_helper(vector<int> &A, int left, int right);
int partition(vector<int> &A, int left, int right);
int long_partition(vector<int> &A, int left, int right);
void random_selection();
int random_selection_helper(vector<int> &A, int left, int right, int nth);

struct node{
	// make life easier by omitting value, i.e. force key = value
	int key;
	node *left;
	node *right;
};
class BST{
public:
	node *root;
public:
	BST():root(nullptr){};
	node *search(int k);
	void insert(int k);
	void remove(int k);
	void print();
};
void BST_test();
node *search_helper(node* root, int k);
void insert_helper(node *&root, int k);
void remove_helper(node *&root, int k);

int main(int argc, char const *argv[])
{
	// insertion_sort();
	// merge_sort();
	// quick_sort();
	// random_selection();
	// BST_test();

	return 0;
}

void print_vector(const vector<int> &A){
	// for(auto it = A.begin(); it < A.end(); it++){
	// 	cout << *it << " ";
	// }
	for(auto n : A){
		cout << n << " ";
	}
	cout << endl;
}
void insertion_sort(){
	vector<int> A = {42,20,17,13,28,14,23,15};
	for(auto i = 0; i < A.size(); i++){
		int j = i;
		while(j > 0 && A[j] < A[j - 1]){
			swap(A[j], A[j - 1]);
			j--;
		}
		print_vector(A);
	}
}
void merge_sort(){
	vector<int> A = {42,20,17,13,28,14,23,15};
	merge_helper(A, 0, A.size() - 1);
	print_vector(A);
}
void merge_helper(vector<int> &A, int left, int right){
	if(left >= right)
		return;
	auto mid = (left + right) / 2;
	merge_helper(A, left, mid);
	merge_helper(A, mid + 1, right);
	merge(A, left, mid, right);
}
void merge(vector<int> &A, int left, int mid, int right){
	auto i = left; auto j = mid + 1; auto k = 0;
	// auto C = new int[right - left + 1];
	vector<int> C{0, right - left + 1};
	while(i <= mid && j <= right){
		if(A[i] < A[j])
			C[k++] = A[i++];
		else
			C[k++] = A[j++];
	}
	if(i > mid){
		while(j <= right)
			C[k++] = A[j++];
	}
	else{
		while(i <= mid)
			C[k++] = A[i++];
	}
	swap_ranges(A.begin()+left, A.begin()+right + 1, C.begin());
	// for(auto l = 0; l < right - left + 1; l ++){
	// 	A[left + l] = C[l];
	// }
	// delete[] C;
}
void quick_sort(){
	srand(0);
	vector<int> A = {42,20,17,13,28,14,23,15};
	quick_helper(A, 0, A.size() - 1);
	print_vector(A);
}
void quick_helper(vector<int> &A, int left, int right){
	if (left >= right)
		return;
	// auto pivot = partition(A, left, right);
	auto pivot = long_partition(A, left, right);
	quick_helper(A, left, pivot - 1);
	quick_helper(A, pivot + 1, right);
}
int partition(vector<int> &A, int left, int right){
	int nth = rand()%(right - left + 1) + left;
	swap(A[right], A[nth]);
	auto i = left;
	for(auto j = left; j < right; j++){
		if(A[j] <  A[right]){
			swap(A[i], A[j]);
			i++;
		}
	}
	swap(A[i], A[right]);
	return i;
}
int long_partition(vector<int> &A, int left, int right){
	int nth = rand()%(right - left + 1) + left;
	swap(A[left], A[nth]);
	auto i = left + 1;
	auto j = right;
	while(i <= j){
		while(i <= right && A[i] < A[left])
			i++;
		while(j > left && A[j] >= A[left])
			j--;
		if (i == right + 1){
			swap(A[left], A[right]);
			return right;
		}
		if (j == left){
			return left;
		}
		if(i < j)
			swap(A[i], A[j]);
	}
	swap(A[left], A[min(i, j)]);
	return min(i, j);
}
void random_selection(){
	vector<int> A = {42,20,17,13,28,14,23,15};
	cout << random_selection_helper(A, 0, A.size() - 1, 6) << endl;
}
int random_selection_helper(vector<int> &A, int left, int right, int nth){
	if (left == right){
		return A[left];
	}
	auto mid = partition(A, 0, A.size() - 1);
	if (nth == mid - left)
		return A[mid];
	else if(nth > mid - left){
		if (mid == right)
			return A[right];
		return random_selection_helper(A, mid + 1, right, nth + left - mid - 1);
	}
	else
		return random_selection_helper(A, left, mid - 1, nth);
}
void BST_test(){
	BST t;
	vector<int> v = {4,2,6,3,7,1,5};
	for(auto i: v){
		t.insert(i);
	}
	t.print();
	t.remove(2); 
	t.insert(9);
	t.remove(5); 
	t.remove(1); 
	t.print();
}	
node *BST::search(int k){
	return search_helper(root, k);
}
node *search_helper(node* root, int k){
	if(root == nullptr)
		return nullptr;
	if(k == root->key)
		return root;
	return (k < root->key) ? search_helper(root->left, k) : search_helper(root->right, k);
}
void BST::insert(int k){
	insert_helper(root, k);
}
void insert_helper(node *&root, int k){
	if(root == nullptr){
		root = new node{k, nullptr, nullptr};
		return;
	}
	if(k < root->key)
		insert_helper(root->left, k);
	else if(k > root->key)
		insert_helper(root->right, k);
}
void BST::remove(int k){
	remove_helper(root, k);
}
void remove_helper(node *&root, int k){
	if(root == nullptr)
		return;
	if(k < root->key)
		remove_helper(root->left, k);
	else if(k > root->key)
		remove_helper(root->right, k);
	else{
		if(root->left == nullptr && root->right == nullptr){
			delete root; 
			root = nullptr;
		}
		else if(root->left == nullptr){
			auto victim = root;
			root = root->right;
			delete victim;
		}
		else if(root->right == nullptr){
			auto victim = root;
			root = root->left;
			delete victim;
		}
		else{
			auto it = &(root->left);
			while((*it)->right != nullptr)
				it = &((*it)->right);
			swap(root->key, (*it)->key);
			auto victim = *it;
			delete victim;
			*it = nullptr;
		}
	}
}
void BST::print(){
	cout << "starting printing\n";
	if(root == nullptr){
		cout << "empty\n";
		return;
	}
	queue<node*> q;
	q.push(root);
	while(!q.empty()){
		auto i = q.front(); 
		cout << i->key << " ";
		q.pop();
		if(i->left != nullptr)
			q.push(i->left);
		if(i->right != nullptr)
			q.push(i->right);
	}	
	cout << endl;
}


