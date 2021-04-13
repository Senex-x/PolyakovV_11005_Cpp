#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Node {
	int key;      // ����
	Node* parent;  // ��������� �� ������������ ����
	Node* child;  // ��������� �� ���� �� �������� �����
	Node* left;  // ��������� �� ����� ���� ���� �� ������
	Node* right;  // ��������� �� ������ ���� ���� �� ������
	int degree;  // ������� �������
	bool mark;// ��� �� ������ � �������� ��������� ����� ������� ���� �������)
};

struct FibonacciHeap {
	int size = 0; // ������� ���������� �����
	Node* min = NULL; // ��������� �� ������ ������ � ����������� ������ 

	void insert(int x) {
		Node* newNode = new Node();               //  ������� ����� ���� 
		newNode->key = x;          //   �������������� ���� ������ ����
		if (size == 0) {             //   ���� ���� ��� ���������, �� ������ ��� ����������� �����������
			min = newNode;
			min->left = newNode;
			min->right = newNode;
		}
		else {                     // ����� ��������� ������ ��������� � ������, ����� �� ���������� ���������
			Node* prevRight = min->right;
			min->right = newNode;
			newNode->left = min;
			newNode->right = prevRight;
			prevRight->left = newNode;
		}
		if (newNode->key < min->key) {
			min = newNode;
		}// ������ ��������� �� �������, ���� ����
				newNode->parent;
				size++;                  // �� �������� ��������� ���������� size 
			
		
	}

	int getMin() {
		return min->key;
	}

	void unionLists(Node* first, Node* second) {
		Node* L = first->left;             // ��������� ������ ��������� ������� ���������
		Node* R = second->right;
		second->right = first;
		first->left = second;
		L->right = R;
		R->left = L;
	}

	void merge(FibonacciHeap* that) {
		if (that->size == 0)            // ���� ������ ���� �����, ������ ���������
			return;
		if (size = 0) {                    // ���� ���� ���� �����, �� ����������� ����� ������ ����
			min = that->min;
			size = that->size;
		}
		else {
			unionLists(min, that->min); // ���������� ��� �������� ������
			size += that->size;
			if (min || (that->min and that->min < min)) { // ���� ������� ���� ���������, �� ���� �������� ���������
				min = that->min;
			}
		}
	}

	void consolidate() {
		Node* A[1024];
		A[min->degree] = min;               // ������� ������ � �������������� ��� min
		Node* current = min->right;
		while (A[current->degree] != current) {   // ���� �������� ������� ��������
			if (A[current->degree]) {     // ���� ������ ������, �� ������� � ��� ������� �������
				A[current->degree] = current;
				current = current->right;
			}
			else {                  // ����� �������� � �������� �� �������� ����� � ����, ������� ����� � ������ ������
				Node* conflict = A[current->degree];
				Node* addTo,* adding;

				if (conflict->key < current->key) {
					addTo = conflict;
					adding = current;
				}
				else {
					addTo = current;
					adding = conflict;
				}
				unionLists(addTo->child, adding);
				adding->parent = addTo;
				addTo->degree++;
				current = addTo;
			}
			if (min->key > current->key)      // ��������� �������, ���� �����
				min = current;
		}
	}

	int deleteMin() {
		Node* prevMin = min;
		unionLists(min, min->child);   // ������ ����� min ���������� � ��������
		Node* L = min->left;            // ��������� ������� min �� ������
		Node* R = min->right;
		L->right = R;
		R->left = L;
		if (prevMin->right == prevMin)  // �������� ���������� ������ � ����� ���������
			return min->key;

		min = min->right;              // ���� ��� ��������� ��������� min �� ������� ����, � ����� consolidate() ������������� min � �������� ����������
		consolidate();
		size--;
		return prevMin->key;
	}
};

int main() {
	FibonacciHeap* heap = new FibonacciHeap();
	int array[] = { 23, 54, 12, 54, 7, 3, 234, 6, 34, 90 };
	for (int i = 0; i < 10; i++) {
		heap->insert(array[i]);
	}
	heap->deleteMin();
	cout << heap->getMin();

	return 0;
}

