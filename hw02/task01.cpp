#include <cassert>
#include <initializer_list>
#include <iostream>

struct Node {
	int value;
	Node* next;
};

// ДЗ 2, задача 1. Развернуть односвязный список.
// Принимает голову списка без циклов, возвращает новую голову.
// previous указывает на начало уже развернутой части, current - на текущий узел.
// Сначала сохраняем следующий узел, затем направляем ссылку current назад.
// После этого previous и current сдвигаются: развернутая часть растет на один узел.
// Каждый узел посещается один раз: время O(n), дополнительная память O(1).
Node* reverse_list(Node* head) {
	Node* previous = nullptr;
	Node* current = head;

	while (current != nullptr) {
		Node* next = current->next; // Иначе после разворота ссылки потеряем остаток списка.
		current->next = previous;
		previous = current;
		current = next;
	}

	return previous;
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
	assert(reverse_list(nullptr) == nullptr);

	{
		Node* head = make_list({5});
		Node* first = head;
		head = reverse_list(head);
		assert(head == first);
		assert(check_list(head, {5}));
		delete_list(head);
	}

	{
		Node* head = make_list({1, 2});
		Node* first = head;
		Node* second = head->next;
		head = reverse_list(head);
		assert(head == second && head->next == first);
		assert(check_list(head, {2, 1}));
		delete_list(head);
	}

	{
		Node* head = make_list({1, 2, 3, 4, 5});
		Node* first = head;
		Node* last = head->next->next->next->next;
		head = reverse_list(head);
		assert(head == last && first->next == nullptr);
		assert(check_list(head, {5, 4, 3, 2, 1}));
		head = reverse_list(head);
		assert(head == first);
		assert(check_list(head, {1, 2, 3, 4, 5}));
		delete_list(head);
	}

	{
		Node* head = make_list({-3, 0, -3, 7});
		head = reverse_list(head);
		assert(check_list(head, {7, -3, 0, -3}));
		delete_list(head);
	}

	std::cout << "hw02/task01: OK\n";
}
