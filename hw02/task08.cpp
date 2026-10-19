#include <cassert>
#include <initializer_list>
#include <iostream>

struct Node {
	int value;
	Node* next;
};

// ДЗ 2, задача 8. Слияние двух отсортированных списков.
// Списки отсортированы по неубыванию, не имеют циклов и общих узлов.
// Переставляем существующие узлы, возвращаем голову общего списка.
// first и second указывают на еще не добавленные части списков.
// Меньший из этих двух узлов добавляем к результату: остальные не могут быть меньше.
// Когда один список закончится, остаток другого уже отсортирован.
// Время O(n + m), дополнительная память O(1).
Node* merge_lists(Node* first, Node* second) {
	Node dummy{0, nullptr}; // Узел перед результатом, создан на стеке без new.
	Node* tail = &dummy; // Последний узел результата, пока это dummy.

	while (first != nullptr && second != nullptr) {
		if (first->value <= second->value) {
			tail->next = first;
			first = first->next;
		} else {
			tail->next = second;
			second = second->next;
		}
		tail = tail->next;
	}

	// Прицепляем остаток целиком, новые узлы в куче не создаются.
	tail->next = (first != nullptr) ? first : second;
	return dummy.next; // dummy не входит в результат, возвращаем первый реальный узел.
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
	assert(merge_lists(nullptr, nullptr) == nullptr);

	{
		Node* first = make_list({1, 3});
		Node* head = merge_lists(first, nullptr);
		assert(head == first);
		assert(check_list(head, {1, 3}));
		delete_list(head);
	}

	{
		Node* second = make_list({2, 4});
		Node* head = merge_lists(nullptr, second);
		assert(head == second);
		assert(check_list(head, {2, 4}));
		delete_list(head);
	}

	{
		Node* first = make_list({3, 6, 8});
		Node* second = make_list({4, 7, 9, 11});
		Node* head = merge_lists(first, second);
		assert(head == first && head->next == second);
		assert(check_list(head, {3, 4, 6, 7, 8, 9, 11}));
		delete_list(head);
	}

	{
		Node* first = make_list({3, 4});
		Node* second = make_list({1, 2});
		Node* second_tail = second->next;
		Node* head = merge_lists(first, second);
		assert(head == second && second_tail->next == first);
		assert(check_list(head, {1, 2, 3, 4}));
		delete_list(head);
	}

	{
		Node* first = make_list({-3, 0, 2, 2});
		Node* second = make_list({-3, 2, 5});
		Node* head = merge_lists(first, second);
		assert(head == first && head->next == second);
		assert(check_list(head, {-3, -3, 0, 2, 2, 2, 5}));
		delete_list(head);
	}

	{
		Node* first = make_list({7});
		Node* second = make_list({7});
		Node* head = merge_lists(first, second);
		assert(head == first && head->next == second);
		assert(check_list(head, {7, 7}));
		delete_list(head);
	}

	std::cout << "hw02/task08: OK\n";
}
