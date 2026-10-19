#include <cassert>
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

// Разворачиваем участок [left, right): left входит в него, right не входит.
// Меняем крайние элементы и двигаемся к середине.
void reverse_range(std::vector<int>& values, std::size_t left, std::size_t right) {
	while (left < right) {
		--right;
		if (left >= right) {
			break;
		}
		std::swap(values[left], values[right]);
		++left;
	}
}

// Сдвигаем массив вправо на k, как в примере условия.
// После общего разворота последние k элементов окажутся в начале,
// но в обратном порядке. Развороты двух частей восстановят их порядок.
// Три разворота дают O(n) времени. Дополнительная память O(1).
void rotate_right(std::vector<int>& values, std::size_t k) {
	if (values.empty()) {
		return;
	}
	k %= values.size(); // Полные обороты не меняют массив.
	if (k == 0) {
		return;
	}

	// Например, для [1, 2, 3, 4, 5] и k = 2 получаем:
	reverse_range(values, 0, values.size()); // [5, 4, 3, 2, 1]
	reverse_range(values, 0, k);             // [4, 5, 3, 2, 1]
	reverse_range(values, k, values.size()); // [4, 5, 1, 2, 3]
}

int main() {
	std::vector<int> values = {1, 2, 3, 4, 5, 6, 7};
	rotate_right(values, 3);
	assert((values == std::vector<int>{5, 6, 7, 1, 2, 3, 4}));

	values = {};
	rotate_right(values, 5);
	assert(values.empty());

	values = {8};
	rotate_right(values, 4);
	assert((values == std::vector<int>{8}));

	values = {1, 2, 3};
	rotate_right(values, 0);
	assert((values == std::vector<int>{1, 2, 3}));
	rotate_right(values, 3);
	assert((values == std::vector<int>{1, 2, 3}));
	rotate_right(values, 4);
	assert((values == std::vector<int>{3, 1, 2}));

	values = {-2, 0, -2, 5};
	rotate_right(values, 2);
	assert((values == std::vector<int>{-2, 5, -2, 0}));

	std::cout << "hw01/task01: OK\n";
}
