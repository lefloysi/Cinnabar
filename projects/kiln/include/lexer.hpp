#pragma once

#include "token.hpp"
#include "types.hpp"
#include "error.hpp"
#include "allocator.hpp"

#include <string>
#include <string_view>
#include <vector>
#include <expected>

namespace lf {



	struct Lexer {
		static std::vector<Token> lex(Lexer&& lexer);
		Lexer(std::string_view source);


	    uchar peek(u64 amount = 0) const;
	    uchar advance();
		bool skip_whitespace();

		Token lex_next();
		Token lex_identifier();
		Token lex_number();
		Token lex_operator();

	  private:
		static bool can_lex_identifier(uchar next);
		static bool can_lex_number(uchar next);
		static bool can_lex_operator(uchar next);

		std::string _source;
		ArenaAllocator _allocator;
		u64 _position = 0;
		std::unordered_map<std::string_view, identifier<std::string, u32>> _identifier_cache;
		std::vector<std::byte*> _allocated;
	};



} // namespace lf