#include <cassert>
#include <initializer_list>
#include <iostream>

struct Node {
	int value;
	Node* next;
};

// ДЗ 2, задача 2. Найти середину списка.
// Список без циклов. Для четной длины возвращаем вторую середину,
// для пустого списка - nullptr. Сам список не меняется.
// slow и fast начинают с головы. fast делает два шага, slow - один.
// Когда fast достигнет конца, slow пройдет половину списка и окажется в середине.
// Время O(n), дополнительная память O(1).
Node* find_middle(Node* head) {
	Node* slow = head;
	Node* fast = head;

	// Для шага на два узла нужны и fast, и его следующий узел.
	while (fast != nullptr && fast->next != nullptr) {
		slow = slow->next;
		fast = fast->next->next;
	}

	return slow;
}

Node* make_list(std::initializer_list<int> values) {
	Node* head = nullptr;
	Node* tail = nullptr;

	for (int value : values) {
		Node* node = new Node{value, nullptr};
		if (head == nullptr) {
			head = node;
		} else {
			tail->next = node;
		}
		tail = node;
	}

	return head;
}

bool check_list(Node* head, std::initializer_list<int> values) {
	for (int value : values) {
		if (head == nullptr || head->value != value) {
			return false;
		}
		head = head->next;
	}

	return head == nullptr;
}

void delete_list(Node* head) {
	while (head != nullptr) {
		Node* next = head->next;
		delete head;
		head = next;
	}
}

int main() {
	assert(find_middle(nullptr) == nullptr);

	{
		Node* head = make_list({9});
		assert(find_middle(head) == head);
		assert(check_list(head, {9}));
		delete_list(head);
	}

	{
		Node* head = make_list({1, 2});
		Node* second = head->next;
		assert(find_middle(head) == second);
		assert(head->next == second && second->next == nullptr);
		assert(check_list(head, {1, 2}));
		delete_list(head);
	}

	{
		Node* head = make_list({1, 2, 3, 4, 5});
		Node* second = head->next;
		Node* third = second->next;
		Node* fourth = third->next;
		Node* fifth = fourth->next;
		assert(find_middle(head) == third);
		assert(head->next == second && second->next == third);
		assert(third->next == fourth && fourth->next == fifth);
		assert(check_list(head, {1, 2, 3, 4, 5}));
		delete_list(head);
	}

	{
		Node* head = make_list({1, 2, 3, 4, 5, 6});
		assert(find_middle(head) == head->next->next->next);
		assert(check_list(head, {1, 2, 3, 4, 5, 6}));
		delete_list(head);
	}

	{
		Node* head = make_list({7, 7, 7});
		assert(find_middle(head) == head->next);
		assert(check_list(head, {7, 7, 7}));
		delete_list(head);
	}

	std::cout << "hw02/task02: OK\n";
}
