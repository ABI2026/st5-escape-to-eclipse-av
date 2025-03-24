#pragma once

#ifndef ENV

#include <unordered_map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <functional>
#include <memory>

template <typename T>
using s_ptr = std::shared_ptr<T>;

#define ENV

#endif //ENV