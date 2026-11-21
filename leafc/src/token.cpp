#include "token.hpp"




namespace lf {
	const std::unordered_map<std::string_view, Token::Type> Token::operator_lookup = {
		{ "=", Token::Type::op_equal },
		{ ":", Token::Type::op_colon },
	};
	const std::unordered_map<std::string_view, Token::Type> Token::keyword_lookup = {
		{ "var", Token::Type::kw_var },
		{ "i32", Token::Type::type_i32 },
	};

	Token Token::end_of_file(const Cursor& cursor) {
		Token token;
		token._type = Type::eof;
		token._literal = "";
		token._cursor = cursor;
		return token;
	}
	Token Token::identifier(const Cursor& cursor, std::string_view text) {
		Token token;
		;
		if (const auto& it = Token::keyword_lookup.find(text); it == Token::keyword_lookup.end()) {
			token._type = Type::identifier;
		}
		else {
			token._type = it->second;
		}
		token._literal = text;
		token._cursor = cursor;
		return token;
	}
	Token Token::number_literal(const Cursor& cursor, std::string_view text) {
		Token token;
		token._type = Type::literal_number;
		token._literal = text;
		token._cursor = cursor;
		return token;
	}
	Token Token::symbol(const Cursor& cursor, Type type, std::string_view text) {
		Token token;
		token._type = type;
		token._literal = text;
		token._cursor = cursor;
		return token;
	}

	Token Token::illegal() {
		Token token;
		token._type = Type::illegal;
		return token;
	}

}