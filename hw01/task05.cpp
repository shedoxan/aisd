#include <cassert>
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

// Сортируем нули, единицы и двойки с помощью трёх индексов.
// left - место для следующего нуля, current - проверяемый элемент.
// От right до конца уже стоят двойки, right в эту часть входит.
// До left стоят нули, от left до current (не включая current) - единицы.
// Непроверенная часть [current, right) с каждым шагом уменьшается на один элемент.
// Поэтому время O(n), дополнительная память O(1).
void sort_zero_one_two(std::vector<int>& values) {
	std::size_t left = 0;
	std::size_t current = 0;
	std::size_t right = values.size();

	while (current < right) {
		if (values[current] == 0) {
			std::swap(values[left], values[current]);
			++left;
			++current;
		} else if (values[current] == 1) {
			++current;
		} else {
			--right;
			std::swap(values[current], values[right]);
			// С правого края пришёл непроверенный элемент, current пока не двигаем.
		}
	}
}

int main() {
	std::vector<int> values = {2, 0, 2, 1, 1, 0};
	sort_zero_one_two(values);
	assert((values == std::vector<int>{0, 0, 1, 1, 2, 2}));

	values = {};
	sort_zero_one_two(values);
	assert(values.empty());

	values = {2};
	sort_zero_one_two(values);
	assert((values == std::vector<int>{2}));

	values = {1, 1, 1};
	sort_zero_one_two(values);
	assert((values == std::vector<int>{1, 1, 1}));

	values = {0, 0, 1, 2, 2};
	sort_zero_one_two(values);
	assert((values == std::vector<int>{0, 0, 1, 2, 2}));

	values = {2, 2, 1, 1, 0, 0};
	sort_zero_one_two(values);
	assert((values == std::vector<int>{0, 0, 1, 1, 2, 2}));

	values = {2, 0, 2, 0};
	sort_zero_one_two(values);
	assert((values == std::vector<int>{0, 0, 2, 2}));

	std::cout << "hw01/task05: OK\n";
}
