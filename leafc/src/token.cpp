#include "token.hpp"




namespace lf {
	Token Token::end_of_file(const Cursor& cursor) {
		Token token;
		token._type = Type::eof;
		token._literal = "";
		token._cursor = cursor;
		return token;
	}
	Token Token::identifier(const Cursor& cursor, std::string_view text) {
		Token token;
		token._type = Type::identifier;
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

}