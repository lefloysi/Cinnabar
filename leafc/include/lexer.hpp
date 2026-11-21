#pragma once

#include "token.hpp"
#include "types.hpp"
#include "error.hpp"
#include "cursor.hpp"

#include <string>
#include <string_view>
#include <vector>
#include <expected>

namespace lf {


	struct Lexer {
		
		static std::expected<std::vector<Token>, std::vector<error>> lex(Lexer&& lexer);
		Lexer(const char* source);
		Lexer(std::string_view source);

		std::string_view source;
		Cursor cursor;

	    unsigned char peek(u64 amount = 0) const;
	    unsigned char advance();
		bool skip_whitespace();

		std::expected<Token, error> lex_next();
		Token lex_identifier();
		Token lex_number();
		Token lex_operator();

		private:
		static bool can_lex_identifier(unsigned char next);
		static bool can_lex_number(unsigned char next);
		static bool can_lex_operator(unsigned char next);

		template<typename Predicate>
		inline std::string_view max_munch(Predicate condition) {
			Cursor start = cursor;
			u64 length = 0;
			while (condition(advance())) {
				++length;
			}
			return std::string_view(source.data() + start.position, length);
		}

	};



} // namespace lf