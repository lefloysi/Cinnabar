#pragma once

#include "token.hpp"
#include "types.hpp"

#include <string>
#include <string_view>
namespace lf {
	class Lexer {
	  public:
		explicit Lexer(std::string_view source);

	  private:
		char _read();
		// amount 0 gets the very next char
		char _peek(u64 amount = 0);
		void skip_whitespace();

		u64 _line_no{};
		u64 _position{};
		std::string _source;

	};
} // namespace lf