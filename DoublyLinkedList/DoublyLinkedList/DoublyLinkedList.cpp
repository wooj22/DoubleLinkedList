#include <iostream>
using namespace std;

/* ���߿��Ḯ��Ʈ ���� */
// ����, �˻�, ����, ��� ����
// iterator ����

/* Node */
template<typename T>
struct Node {
	T data;							// ��� ������
	Node<T>* next = nullptr;		// ���� ��� �ּ�
	Node<T>* prev = nullptr;		// ���� ��� �ּ�
};

/* DoubleLinkedList */
template<typename T>
struct DoubleLinkedList {
	/// head, tail
	Node<T> head;
	Node<T> tail;

	/// Iterator
	struct Iterator
	{
		Node<T>* curNode = nullptr;
		Iterator(Node<T>* p) { curNode = p; }

		Iterator& operator++() 
		{
			curNode = curNode->next;
			return *this;
		}
		T& operator*() { return curNode->data; }
		bool operator==(const Iterator& ref) { return  curNode == ref.curNode; }
		bool operator!=(const Iterator& ref) { return  curNode != ref.curNode; }
		void operator=(Node<T>* p) { curNode = p;	}
	};

	Iterator begin() { return Iterator(head.next); }
	Iterator end() { return Iterator(&tail); }


	/// �߰� ���� : prev��� �ڿ� ��带 �����ϰ� ����
	Node<T>* insert(Node<T>* prevNode, const T& data)
	{
		// 1. ��� ����
		Node<T>* newNode = new Node<T>();
		newNode->data = data;

		// 2. ����Ʈ�� ����
		// 1) ����Ʈ�� ������� ���
		if (head.next == nullptr) {	
			newNode->prev = &head;
			newNode->next = &tail;

			head.next = newNode;
			tail.prev = newNode;
		}
		// 2) ����Ʈ�� ������� ���� ���
		else {	
			// new node�� prev, next set
			newNode->prev = prevNode;
			newNode->next = prevNode->next;

			// next node�� prev set
			if (prevNode->next != &tail) prevNode->next->prev = newNode;
			else tail.prev = newNode;

			// prev node�� next set
			prevNode->next = newNode;
		}

		// 3. ��� ����
		return newNode;
	}

	/// �� �ڿ� ����
	void push_back(const T& data) 
	{
		// 1. ��� ����
		Node<T>* newNode = new Node<T>();
		newNode->data = data;

		// 2. ����
		// 1) ����Ʈ�� ������� ���
		if (head.next == nullptr) { 
			newNode->prev = &head;
			newNode->next = &tail;

			head.next = newNode;
			tail.prev = newNode;
		}
		// 2) ����Ʈ�� ������� ���� ���
		else {  
			// new node�� prev, next set
			newNode->prev = tail.prev;
			newNode->next = &tail;

			// prev node�� next set
			tail.prev->next = newNode;

			// next node�� prev set
			tail.prev = newNode;
		}
	}

	/// �˻� : ó�� �߰��� ��� ����
	Node<T>* find(const T& data) 
	{
		for (Node<T>* findNode = head.next; findNode != &tail; findNode = findNode->next)
			if (findNode->data == data) return findNode;

		return nullptr;
	}

	/// ��� ���� : ��带 ����� ���� ��� ����
	Node<T>* erase(Node<T>* removeNode) 
	{
		removeNode->prev->next = removeNode->next;
		removeNode->next->prev = removeNode->prev;

		Node<T>* returnNode = removeNode->next;
		delete removeNode;
		return returnNode;
	}

	/// ���� : ��ü��带 ��ȸ�ϸ鼭 ���� �����͸� �ش� ����ּҸ� erase�� �����.
	void remove(const T& data) 
	{
		Node<T>* findNode = head.next;
		while (findNode != &tail)
		{
			if (findNode->data == data)
				findNode = erase(findNode);  // �����ϰ� ���� ����
			else
				findNode = findNode->next;   // ���� ����
		}
	}
};

int main() {
	DoubleLinkedList<int> MyList;
	MyList.push_back(10);
	MyList.push_back(30);
	MyList.push_back(40);    // �߰� �׽�Ʈ

	Node<int>* pFind = MyList.find(30);
	MyList.erase(pFind);     // ���� �׽�Ʈ

	// ��ü ����� ���
	DoubleLinkedList<int>::Iterator iter = MyList.begin();
	for (; iter != MyList.end(); ++iter)
	{
		std::cout << *iter << std::endl;
	}
}