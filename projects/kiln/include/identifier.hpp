#pragma once

#include <concepts>

namespace lf {
	template<typename T, typename value_type> 
	struct identifier {

		constexpr identifier() = default;
		explicit constexpr identifier(value_type value) : _value(value) {}

		value_type value() const noexcept { return _value; }

	  private:
		value_type _value{};
	};
}
