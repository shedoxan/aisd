#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>

// Проверяем, можно ли получить b, вставив символы в a.
// Например, "abc" подходит к "axbxc", но не к "acb".
// Время O(n + m), дополнительная память O(1).
// u32string нужна для сравнения букв, в том числе русских, а не байтов UTF-8.
bool is_subsequence(const std::u32string& a, const std::u32string& b) {
	std::size_t i = 0; // Какой символ a сейчас ищем.
	std::size_t j = 0; // Какой символ b сейчас смотрим.

	while (i < a.size() && j < b.size()) {
		if (a[i] == b[j]) {
			// Нашли нужный символ. Теперь ищем следующий символ a.
			++i;
		}
		// В b идём дальше и при совпадении, и при несовпадении.
		++j;
	}

	// Если i дошёл до конца a, нашли все её символы в нужном порядке.
	return i == a.size();
}

int main() {
	assert(is_subsequence(U"abc", U"ahbgdc"));
	assert(!is_subsequence(U"axc", U"ahbgdc"));
	assert(is_subsequence(U"", U""));
	assert(is_subsequence(U"", U"abc"));
	assert(!is_subsequence(U"abc", U""));
	assert(is_subsequence(U"abc", U"abc"));
	assert(!is_subsequence(U"aa", U"a"));
	assert(is_subsequence(U"кот", U"кто-то"));
	assert(!is_subsequence(U"кот", U"ток"));

	std::cout << "hw02/task04: OK\n";
	return 0;
}
