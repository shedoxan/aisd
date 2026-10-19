#include <cassert>
#include <initializer_list>
#include <iostream>

struct Node {
	int value;
	Node* next;
};

// ДЗ 2, задача 3. Удалить элемент из односвязного списка.
// Удаляем все вхождения val, как в removeElements на семинаре, и возвращаем голову.
// Список без циклов, его узлы должны быть выделены через new.
// dummy стоит перед головой: удаление первого узла не требует отдельного случая.
// previous указывает на последний сохраненный узел, current - на проверяемый.
// Удаляемый узел пропускаем в ссылке previous->next и освобождаем через delete.
// Один проход: время O(n), дополнительная память O(1).
Node* remove_value(Node* head, int val) {
	Node dummy{0, head}; // Локальный узел на стеке, new здесь не нужен.
	Node* previous = &dummy;
	Node* current = head;

	while (current != nullptr) {
		Node* next = current->next; // Сохраняем до delete: потом current читать нельзя.
		if (current->value == val) {
			previous->next = next;
			delete current;
			// previous остается на месте, чтобы удалить и соседнее совпадение.
		} else {
			previous = current;
		}
		current = next;
	}

	return dummy.next;
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
	assert(remove_value(nullptr, 1) == nullptr);

	{
		Node* head = make_list({5});
		head = remove_value(head, 5);
		assert(head == nullptr);
	}

	{
		Node* head = make_list({2, 2, 1, 3});
		Node* third = head->next->next;
		head = remove_value(head, 2);
		assert(head == third);
		assert(check_list(head, {1, 3}));
		delete_list(head);
	}

	{
		Node* head = make_list({1, 2, 2, 3, 2});
		Node* first = head;
		Node* fourth = head->next->next->next;
		head = remove_value(head, 2);
		assert(head == first && head->next == fourth);
		assert(fourth->next == nullptr);
		assert(check_list(head, {1, 3}));
		delete_list(head);
	}

	{
		Node* head = make_list({1, 2, 3});
		head = remove_value(head, 3);
		assert(check_list(head, {1, 2}));
		delete_list(head);
	}

	{
		Node* head = make_list({-2, 0, 4});
		Node* first = head;
		Node* second = head->next;
		Node* third = second->next;
		head = remove_value(head, 8);
		assert(head == first && head->next == second && second->next == third);
		assert(check_list(head, {-2, 0, 4}));
		delete_list(head);
	}

	{
		Node* head = make_list({4, 4, 4});
		head = remove_value(head, 4);
		assert(head == nullptr);
	}

	std::cout << "hw02/task03: OK\n";
}
