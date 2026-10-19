#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>

// Сравниваем первую букву с последней, вторую с предпоследней и так далее.
// Регистр, пробелы и знаки учитываем. Пустая строка тоже палиндром.
// Время O(n), дополнительная память O(1).
// u32string нужна, чтобы русские буквы сравнивались целиком.
bool is_palindrome(const std::u32string& text) {
	if (text.size() < 2) return true;

	std::size_t left = 0;
	std::size_t right = text.size() - 1;

	while (left < right) {
		// Одного несовпадения достаточно, чтобы вернуть false.
		if (text[left] != text[right]) return false;
		// Проверенную пару больше не трогаем, идём внутрь строки.
		++left;
		--right;
	}

	return true;
}

int main() {
	assert(is_palindrome(U""));
	assert(is_palindrome(U"a"));
	assert(is_palindrome(U"abba"));
	assert(is_palindrome(U"level"));
	assert(!is_palindrome(U"abc"));
	assert(!is_palindrome(U"Level"));
	assert(is_palindrome(U"a b a"));
	assert(!is_palindrome(U"ab a"));
	assert(is_palindrome(U"топот"));
	assert(!is_palindrome(U"кот"));

	std::cout << "hw02/task06: OK\n";
	return 0;
}
