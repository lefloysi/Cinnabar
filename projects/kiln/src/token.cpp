#include "token.hpp"




namespace lf {
	const std::unordered_map<std::string_view, Token::Type> Token::operator_lookup = {
		{ ".",  Token::Type::punc_decimal },
		{ "+",  Token::Type::punc_plus },
		{ "-",  Token::Type::punc_minus },
		{ "*",  Token::Type::punc_asterik },
		{ "/",  Token::Type::punc_slash },
		{ "->", Token::Type::punc_arrow_right },
		{ "<-", Token::Type::punc_arrow_left },
		{ "<<", Token::Type::punc_bitshift_left },
		{ "%",  Token::Type::punc_modulus },
		{ "=",  Token::Type::punc_equal },
		{ "==", Token::Type::punc_equal_equal },
		{ ">=", Token::Type::punc_greater_equal },
		{ "<=", Token::Type::punc_lesser_equal },
		{ "<",  Token::Type::punc_lesser_than },
		{ ">",  Token::Type::punc_greater_than },
		{ ";",  Token::Type::punc_semicolon },
		{ ":",  Token::Type::punc_colon },
		{ ":=", Token::Type::punc_colonequal },
		{ "(",  Token::Type::punc_lparan },
		{ ")",  Token::Type::punc_rparan },
		{ "[",  Token::Type::punc_lbracket },
		{ "]",  Token::Type::punc_rbracket },
		{ "{",  Token::Type::punc_lbrace },
		{ "}",  Token::Type::punc_rbrace },
	};
	const std::unordered_map<std::string_view, Token::Type> Token::keyword_lookup = {
		{ "return", Token::Type::keyw_return },
		{ "fn",		Token::Type::keyw_fn },
		{ "var",	Token::Type::keyw_var },
		{ "const",	Token::Type::keyw_const },
		{ "class",	Token::Type::keyw_class },
		{ "union",	Token::Type::keyw_union },
		{ "enum",	Token::Type::keyw_enum },
		{ "extern", Token::Type::keyw_extern },
		{ "export", Token::Type::keyw_export },

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

	Token Token::end_of_file(u64 position) {
		Token token;
		token._position = position;
		token._type = Type::eof;
		return token;
	}
	Token Token::keyword(u64 position, Type type) {
		Token token;
		token._position = position;
		token._type = type;
		return token;
	}
	Token Token::identifier(u64 position, Symbol symbol) {
		Token token;
		token._position = position;
		token._type = Type::identifier;
		token._symbol = symbol;
		return token;
	}
	Token Token::number_literal(u64 position, Symbol symbol) {
		Token token;
		token._position = position;
		token._type = Type::literal_number;
		token._symbol = symbol;
		return token;
	}
	Token Token::punctuator(u64 position, Type type) {
		Token token;
		token._position = position;
		token._type = type;
		return token;
	}

	Token Token::illegal(u64 position, Symbol symbol) {
		Token token;
		token._position = position;
		token._type = Type::illegal;
		token._symbol = symbol;
		return token;
	}

}