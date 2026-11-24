#pragma once

#include "types.hpp"
#include "identifier.hpp"

#include <format>
#include <string_view>
#include <unordered_map>



namespace lf {
	class Token {
	  public:
		using Symbol = identifier<std::string, u32>;
		enum class Type {
			none,
			identifier,
			eof,
			illegal,

			keyw_return,		// return
			keyw_fn,			// fn
			keyw_var,			// var
			keyw_const,			// const
			keyw_class,			// class
			keyw_union,			// union
			keyw_enum,			// enum
			keyw_extern,		// extern
			keyw_export,		// export

			punc_decimal,		// .
			punc_plus,			// +
			punc_minus,			// -
			punc_asterik,		// *
			punc_slash,			// /
			punc_arrow_right,	// ->
			punc_arrow_left,	// <-
			punc_bitshift_left, // <<
			punc_modulus,		// %
			punc_equal,			// =
			punc_equal_equal,	// ==
			punc_greater_equal, // >=
			punc_lesser_equal,	// <=
			punc_lesser_than,	// <
			punc_greater_than,	// >
			punc_semicolon,		// ;
			punc_colon,			// :
			punc_colonequal,	// :=
			punc_lparan,		// (
			punc_rparan,		// )
			punc_lbracket,		// [
			punc_rbracket,		// ]
			punc_lbrace,		// {
			punc_rbrace,		// }

			type_void,			// void
			type_bool,			// bool
			type_ch08,			// ch08
			type_ch16,			// ch16
			type_ch32,			// ch32
			type_i08,			// i08
			type_i16,			// i16
			type_i32,			// i32
			type_i64,			// i64
			type_u08,			// u08
			type_u16,			// u16
			type_u32,			// u32
			type_u64,			// u64
			type_f32,			// f32
			type_f64,			// f64

			literal_number,		// 123.123
			literal_string,		// "SomeString"
		};

		static Token end_of_file(u64 position);
		static Token keyword(u64 position, Type type);
		static Token identifier(u64 position, Symbol symbol);
		static Token number_literal(u64 position, Symbol symbol);
		static Token string_literal(u64 position, Symbol symbol);
		static Token punctuator(u64 position, Type type);
		static Token illegal(u64 position, Symbol symbol);

		inline Type type() const noexcept { return _type; }
		inline Symbol symbol() const noexcept { return _symbol; }

		static const std::unordered_map<std::string_view, Type> operator_lookup;
		static const std::unordered_map<std::string_view, Type> keyword_lookup;

	  private:
		u64 _position = 0;
		Type _type = Type::none;
		Symbol _symbol;
	};


} // namespace lf

template<>
struct std::formatter<lf::Token::Type> {
	constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

	auto format(const lf::Token::Type& obj, auto& ctx) const {
		static constexpr std::string_view token_strings[] = {
			"NONE",
			"IDENTIFIER",
			"EOF",
			"ILLEGAL",

			"RETURN",         // return
			"FN",			  // fn
			"VAR",			  // var
			"CONST",		  // const
			"CLASS",		  // class
			"UNION",		  // union
			"ENUM",			  // enum
			"EXTERN",		  // extern
			"EXPORT",		  // export

			"DOT",			  // .
			"PLUS",			  // +
			"MINUS",		  // -
			"ASTERIK",		  // *
			"SLASH",		  // /
			"ARROW_RIGHT",	  // ->
			"ARROW_LEFT",	  // <-
			"BITSHIFT_LEFT",  // <<
			"MODULUS",		  // %
			"EQUALS",		  // =
			"EQUALS_EQUALS",  // ==
			"GREATER_EQUALS", // >=
			"LESSER_EQUALS",  // <=
			"LESSER",		  // <
			"GREATER",		  // >
			"SEMICOLON",	  // ;
			"COLON",		  // :
			"COLON_EQUALS",	  // :=
			"LPARANTHESE",	  // (
			"RPARANTHESE",	  // )
			"LBRACKET",		  // [
			"RBRACKET",		  // ]
			"LBRACE",		  // {
			"RBRACE",		  // }

			"VOID",			  // void
			"BOOL",			  // bool
			"CH08",			  // ch08
			"CH16",			  // ch16
			"CH32",			  // ch32
			"I08",			  // i08
			"I16",			  // i16
			"I32",			  // i32
			"I64",			  // i64
			"U08",			  // u08
			"U16",			  // u16
			"U32",			  // u32
			"U64",			  // u64
			"F32",			  // f32
			"F64",			  // f64

			"NUM_LITERAL",	  // 123.123
			"STR_LITERAL",	  // "SomeString"
		};

		return std::format_to(ctx.out(), "{}", token_strings[static_cast<size_t>(obj)]);
	}
};

template<>
struct std::formatter<lf::Token> {
	constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

	auto format(const lf::Token& obj, auto& ctx) const {
		return std::format_to(ctx.out(), "{}({}) ", obj.type(), "obj.symbol()");
	}
};

