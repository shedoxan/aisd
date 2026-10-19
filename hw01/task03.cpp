#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

// Сливаем два отсортированных массива в first. Это разные массивы.
// В first есть first_count исходных элементов и готовые места для всего second.
// first_count задаём явно, потому что нули могут быть и среди исходных данных.
// Пишем с конца, каждый раз выбирая больший из оставшихся элементов.
// Тогда место записи правее непрочитанной части first и мы её не затираем.
// Время O(n + m), где n = first_count, m = second.size().
// Дополнительная память O(1), новые массивы не создаём.
void merge_into_first(std::vector<int>& first, std::size_t first_count,
	const std::vector<int>& second) {
	assert(first_count <= first.size() && second.size() == first.size() - first_count);
	// i и j - числа ещё не перенесённых элементов. Их последние индексы: i - 1 и j - 1.
	// write - число ещё не заполненных мест результата, следующее место: write - 1.
	std::size_t i = first_count;
	std::size_t j = second.size();
	std::size_t write = first.size();

	// Когда second закончится, остаток first уже будет на своих местах.
	while (j > 0) {
		--write;
		if (i > 0 && first[i - 1] > second[j - 1]) {
			--i;
			first[write] = first[i];
		} else {
			--j;
			first[write] = second[j];
		}
	}
}

int main() {
	std::vector<int> first = {1, 3, 5, 0, 0, 0};
	merge_into_first(first, 3, {2, 4, 6});
	assert((first == std::vector<int>{1, 2, 3, 4, 5, 6}));

	first = {};
	merge_into_first(first, 0, {});
	assert(first.empty());

	first = {0, 0, 0};
	merge_into_first(first, 0, {-2, 0, 4});
	assert((first == std::vector<int>{-2, 0, 4}));

	first = {-1, 0, 2};
	merge_into_first(first, 3, {});
	assert((first == std::vector<int>{-1, 0, 2}));

	first = {-3, 0, 0, 0, 0, 0};
	merge_into_first(first, 3, {-2, 0, 1});
	assert((first == std::vector<int>{-3, -2, 0, 0, 0, 1}));

	first = {4, 5, 0, 0, 0};
	merge_into_first(first, 2, {1, 2, 3});
	assert((first == std::vector<int>{1, 2, 3, 4, 5}));

	first = {1, 1, 0, 0};
	merge_into_first(first, 2, {1, 1});
	assert((first == std::vector<int>{1, 1, 1, 1}));

	std::cout << "hw01/task03: OK\n";
}
