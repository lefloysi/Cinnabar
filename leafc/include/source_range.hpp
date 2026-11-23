#pragma once

#include <string_view>
#include <span>
namespace lf {
	struct source_range {

		std::string_view sub(std::string_view text) {
			return std::string_view(text.at(position), length);
		}
		template<typename T>
		std::span<T> sub(std::span<T> range) {
			return std::span<T>(text.at(position), length);
		})

		size_t position;
		size_t length;
	};
}
