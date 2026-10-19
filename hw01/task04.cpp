#include <cassert>
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

// Сортируем массив из нулей и единиц, собирая нули в начале.
// i проверяет очередной элемент, write - место для следующего нуля.
// До write уже стоят нули, от write до i (не включая i) - единицы.
// Найденный ноль меняем с первой единицей. Если write == i, он уже на месте.
// Один проход: O(n) времени и O(1) дополнительной памяти.
void sort_zero_one(std::vector<int>& values) {
	std::size_t write = 0;
	for (std::size_t i = 0; i < values.size(); ++i) {
		if (values[i] == 0) {
			std::swap(values[write], values[i]);
			++write;
		}
	}
}

int main() {
	std::vector<int> values = {1, 0, 1, 0, 0, 1};
	sort_zero_one(values);
	assert((values == std::vector<int>{0, 0, 0, 1, 1, 1}));

	values = {};
	sort_zero_one(values);
	assert(values.empty());

	values = {1};
	sort_zero_one(values);
	assert((values == std::vector<int>{1}));

	values = {0, 0, 0};
	sort_zero_one(values);
	assert((values == std::vector<int>{0, 0, 0}));

	values = {1, 1, 1};
	sort_zero_one(values);
	assert((values == std::vector<int>{1, 1, 1}));

	values = {0, 0, 1, 1};
	sort_zero_one(values);
	assert((values == std::vector<int>{0, 0, 1, 1}));

	values = {1, 0};
	sort_zero_one(values);
	assert((values == std::vector<int>{0, 1}));

	std::cout << "hw01/task04: OK\n";
}
