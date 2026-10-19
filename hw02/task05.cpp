#include <cassert>
#include <cstddef>
#include <iostream>
#include <limits>
#include <vector>

// Ищем пару в отсортированном массиве. Один элемент дважды брать нельзя.
// Двигаем индексы с краёв к середине: каждый делает не больше n шагов.
// Время O(n), дополнительная память O(1).
bool has_pair_sum(const std::vector<int>& values, long long target) {
	if (values.size() < 2) return false;

	std::size_t left = 0;
	std::size_t right = values.size() - 1;
	while (left < right) {
		// Приводим до сложения, чтобы сумма двух int не переполнилась.
		long long sum = static_cast<long long>(values[left]) + values[right];
		if (sum == target) return true;

		if (sum < target) {
			// Даже с самым большим оставшимся числом сумма мала.
			// Значит, текущий левый элемент уже не подходит.
			++left;
		} else {
			// Даже с самым маленьким оставшимся числом сумма велика.
			--right;
		}
	}

	return false;
}

int main() {
	assert(has_pair_sum({1, 2, 4, 7, 11}, 9));
	assert(!has_pair_sum({1, 2, 4, 7, 11}, 20));
	assert(!has_pair_sum({}, 0));
	assert(!has_pair_sum({3}, 6));
	assert(has_pair_sum({3, 3}, 6));
	assert(has_pair_sum({-8, -3, 0, 2, 9}, -6));
	assert(has_pair_sum({0, 0}, 0));

	int max_value = std::numeric_limits<int>::max();
	int min_value = std::numeric_limits<int>::min();
	assert(has_pair_sum({max_value, max_value}, 2LL * max_value));
	assert(has_pair_sum({min_value, min_value}, 2LL * min_value));
	assert(!has_pair_sum({max_value, max_value}, -2));

	std::cout << "hw02/task05: OK\n";
	return 0;
}
