#pragma once

namespace util {

template <typename First, typename... T>
bool is_all_of(First&& first, T&&... t) {
  return ((first == t) && ...);
}

}  // namespace util