#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

// Убираем повторы в отсортированном массиве и возвращаем новую длину.
// Например, из [1, 1, 2] получаем начало [1, 2] и длину 2.
// Сам размер vector не меняем: хвост после новой длины больше не используем.
// Время O(n), дополнительная память O(1).
std::size_t remove_duplicates(std::vector<int>& values) {
	if (values.empty()) return 0;

	std::size_t slow = 1; // Первый элемент уже оставили, следующий пишем сюда.
	for (std::size_t fast = 1; fast < values.size(); ++fast) {
		// В отсортированном массиве повторы соседние. Сравниваем с последним
		// оставленным числом, а не с предыдущим индексом исходного массива.
		if (values[fast] != values[slow - 1]) {
			// slow не правее fast, поэтому непрочитанные числа не затираются.
			values[slow] = values[fast];
			++slow;
		}
	}

	return slow;
}

void check_result(std::vector<int> values, const std::vector<int>& expected) {
	std::size_t length = remove_duplicates(values);
	assert(length == expected.size());
	for (std::size_t i = 0; i < length; ++i) {
		assert(values[i] == expected[i]);
	}
}

int main() {
	check_result({1, 1, 2, 2, 3}, {1, 2, 3});
	check_result({}, {});
	check_result({7}, {7});
	check_result({4, 4, 4, 4}, {4});
	check_result({-3, -1, 0, 2}, {-3, -1, 0, 2});
	check_result({-2, -2, 0, 0, 0, 3, 3}, {-2, 0, 3});

	std::cout << "hw02/task07: OK\n";
	return 0;
}
