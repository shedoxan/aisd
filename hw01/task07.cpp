#include <cassert>
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

// Переносим нули в конец, сохраняя порядок остальных чисел.
// i проверяет элементы слева направо, write - место для следующего ненулевого.
// До write уже стоят ненулевые числа, от write до i (не включая i) - нули.
// Если write < i, ставим найденное число на write, а ноль отправляем на его место.
// Если write == i, число уже на месте, обмен ничего не меняет.
// Ненулевые числа встречаем и записываем в одном порядке, поэтому он сохраняется.
// Один проход: O(n) времени и O(1) дополнительной памяти.
void move_zeroes_back(std::vector<int>& values) {
	std::size_t write = 0;
	for (std::size_t i = 0; i < values.size(); ++i) {
		if (values[i] != 0) {
			std::swap(values[write], values[i]);
			++write;
		}
	}
}

int main() {
	std::vector<int> values = {0, 3, 0, 5, 2, 0};
	move_zeroes_back(values);
	assert((values == std::vector<int>{3, 5, 2, 0, 0, 0}));

	values = {};
	move_zeroes_back(values);
	assert(values.empty());

	values = {0};
	move_zeroes_back(values);
	assert((values == std::vector<int>{0}));

	values = {0, 0, 0};
	move_zeroes_back(values);
	assert((values == std::vector<int>{0, 0, 0}));

	values = {-2, 4, -2};
	move_zeroes_back(values);
	assert((values == std::vector<int>{-2, 4, -2}));

	values = {0, -1, 0, -1, 2};
	move_zeroes_back(values);
	assert((values == std::vector<int>{-1, -1, 2, 0, 0}));

	values = {3, 5, 0, 0};
	move_zeroes_back(values);
	assert((values == std::vector<int>{3, 5, 0, 0}));

	std::cout << "hw01/task07: OK\n";
}
