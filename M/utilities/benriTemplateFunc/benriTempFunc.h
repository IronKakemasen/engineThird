#pragma once
#include < algorithm >
#include <vector>

template<typename T>
bool DoesContain(const std::vector<T>& container_, T value_) {
	return std::find(container_.cbegin(), container_.cend(), value_) != container_.cend();
}