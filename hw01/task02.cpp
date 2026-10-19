#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

// Объединяем два отсортированных массива в новый отсортированный массив.
// i и j указывают на следующие элементы first и second.
// Меньший из них не больше остальных, поэтому его можно добавить в конец.
// Каждый элемент копируем один раз: O(n + m) времени, где n и m - длины массивов.
// Результат занимает O(n + m) памяти, остальные переменные - O(1).
std::vector<int> merge_sorted(const std::vector<int>& first, const std::vector<int>& second) {
	std::vector<int> result;
	result.reserve(first.size() + second.size());
	std::size_t i = 0;
	std::size_t j = 0;

	while (i < first.size() && j < second.size()) {
		if (first[i] <= second[j]) {
			result.push_back(first[i]);
			++i;
		} else {
			result.push_back(second[j]);
			++j;
		}
	}
	// Один массив закончился. Остаток другого уже отсортирован.
	while (i < first.size()) {
		result.push_back(first[i]);
		++i;
	}
	while (j < second.size()) {
		result.push_back(second[j]);
		++j;
	}
	return result;
}

int main() {
	assert((merge_sorted({1, 3, 5}, {2, 4, 6}) == std::vector<int>{1, 2, 3, 4, 5, 6}));
	assert(merge_sorted({}, {}).empty());
	assert((merge_sorted({}, {-3, 0, 7}) == std::vector<int>{-3, 0, 7}));
	assert((merge_sorted({1, 2}, {}) == std::vector<int>{1, 2}));
	assert((merge_sorted({1, 1, 3}, {1, 2, 3}) == std::vector<int>{1, 1, 1, 2, 3, 3}));
	assert((merge_sorted({-5, -2, 0}, {-4, 0, 8}) == std::vector<int>{-5, -4, -2, 0, 0, 8}));
	assert((merge_sorted({5}, {1, 2, 3}) == std::vector<int>{1, 2, 3, 5}));

	std::cout << "hw01/task02: OK\n";
}
