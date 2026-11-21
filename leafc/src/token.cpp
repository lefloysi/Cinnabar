#include "token.hpp"




namespace lf {
	const std::unordered_map<std::string_view, Token::Type> Token::operator_lookup = {
		{ ".", Token::Type::op_decimal },
		{ "+", Token::Type::op_plus },
		{ "-", Token::Type::op_minus },
		{ "*", Token::Type::op_asterik },
		{ "/", Token::Type::op_slash },
		{ "->", Token::Type::op_arrow_right },
		{ "<-", Token::Type::op_arrow_left },
		{ "<<", Token::Type::op_bitshift_left },
		{ "%", Token::Type::op_modulus },
		{ "=", Token::Type::op_equal },
		{ "==", Token::Type::op_equal_equal },
		{ ">=", Token::Type::op_greater_equal },
		{ "<=", Token::Type::op_lesser_equal },
		{ "<", Token::Type::op_lesser_than },
		{ ">", Token::Type::op_greater_than },
		{ ";", Token::Type::op_semicolon },
		{ ":", Token::Type::op_colon },
		{ ":=", Token::Type::op_colonequal },
		{ "(", Token::Type::op_lparan },
		{ ")", Token::Type::op_rparan },
		{ "[", Token::Type::op_lbracket },
		{ "]", Token::Type::op_rbracket },
		{ "{", Token::Type::op_lbrace },
		{ "}", Token::Type::op_rbrace },
		{ "=", Token::Type::op_equal },
		{ ":", Token::Type::op_colon },
	};
	const std::unordered_map<std::string_view, Token::Type> Token::keyword_lookup = {
		{ "return", Token::Type::kw_return },
		{ "fn", Token::Type::kw_fn },
		{ "var", Token::Type::kw_var },
		{ "const", Token::Type::kw_const },
		{ "class", Token::Type::kw_class },
		{ "union", Token::Type::kw_union },
		{ "enum", Token::Type::kw_enum },
		{ "extern", Token::Type::kw_extern },
		{ "export", Token::Type::kw_export },

		{ "void", Token::Type::type_void },
		{ "bool", Token::Type::type_bool },
		{ "ch08", Token::Type::type_ch08 },
		{ "ch16", Token::Type::type_ch16 },
		{ "ch32", Token::Type::type_ch32 },
		{ "i08", Token::Type::type_i08 },
		{ "i16", Token::Type::type_i16 },
		{ "i32", Token::Type::type_i32 },
		{ "i64", Token::Type::type_i64 },
		{ "u08", Token::Type::type_u08 },
		{ "u16", Token::Type::type_u16 },
		{ "u32", Token::Type::type_u32 },
		{ "u64", Token::Type::type_u64 },
		{ "f32", Token::Type::type_f32 },
		{ "f64", Token::Type::type_f64 },

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

	Token Token::illegal(const Cursor& cursor, std::string_view text) {
		Token token;
		token._type = Type::illegal;
		token._literal = text;
		token._cursor = cursor;
		return token;
	}

}