#include <cassert>
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

// Переносим чётные числа в начало, сохраняя их порядок.
// i идёт по массиву, write - место для следующего чётного числа.
// Чётные встречаем слева направо и добавляем в начало в той же очередности.
// Если write < i, обмен вытесняет нечётное число, не затрагивая собранные чётные.
// Порядок нечётных может измениться, как и в примере условия.
// Один проход: O(n) времени и O(1) дополнительной памяти.
void move_even_front(std::vector<int>& values) {
	std::size_t write = 0;
	for (std::size_t i = 0; i < values.size(); ++i) {
		if (values[i] % 2 == 0) {
			std::swap(values[write], values[i]);
			++write;
		}
	}
}

int main() {
	std::vector<int> values = {3, 2, 4, 1, 11, 8, 9};
	move_even_front(values);
	assert((values == std::vector<int>{2, 4, 8, 1, 11, 3, 9}));

	values = {};
	move_even_front(values);
	assert(values.empty());

	values = {7};
	move_even_front(values);
	assert((values == std::vector<int>{7}));

	values = {2, 4, 0, -6};
	move_even_front(values);
	assert((values == std::vector<int>{2, 4, 0, -6}));

	values = {3, -1, 5};
	move_even_front(values);
	assert((values == std::vector<int>{3, -1, 5}));

	values = {-3, -2, 0, -4, 7};
	move_even_front(values);
	assert((values == std::vector<int>{-2, 0, -4, -3, 7}));

	values = {1, 2, 3, 2, 5, 4};
	move_even_front(values);
	assert((values == std::vector<int>{2, 2, 4, 1, 5, 3}));

	std::cout << "hw01/task06: OK\n";
}
