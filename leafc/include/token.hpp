#pragma once

#include "types.hpp"
#include "cursor.hpp"

#include <format>
#include <string_view>
#include <unordered_map>

namespace lf {
	class Token {
	  public:
		enum class Type {
			none,
			identifier,
			eof,
			illegal,

			kw_return,		  // return
			kw_fn,			  // fn
			kw_var,			  // var
			kw_const,		  // const
			kw_class,		  // class
			kw_union,		  // union
			kw_enum,		  // enum
			kw_extern,		  // extern
			kw_export,		  // export

			op_decimal,		  // .
			op_plus,		  // +
			op_minus,		  // -
			op_asterik,		  // *
			op_slash,		  // /
			op_arrow_right,	  // ->
			op_arrow_left,	  // <-
			op_bitshift_left, // <<
			op_modulus,		  // %
			op_equal,		  // =
			op_equal_equal,	  // ==
			op_greater_equal, // >=
			op_lesser_equal,  // <=
			op_lesser_than,	  // <
			op_greater_than,  // >
			op_semicolon,	  // ;
			op_colon,		  // :
			op_colonequal,    // :=
			op_lparan,		  // (
			op_rparan,		  // )
			op_lbracket,	  // [
			op_rbracket,	  // ]
			op_lbrace,		  // {
			op_rbrace,		  // }
			
			type_void,		   // void
			type_bool,		   // bool
			type_ch08,		   // ch08
			type_ch16,		   // ch16
			type_ch32,		   // ch32
			type_i08,		   // i08
			type_i16,		   // i16
			type_i32,		   // i32
			type_i64,		   // i64
			type_u08,		   // u08
			type_u16,		   // u16
			type_u32,		   // u32
			type_u64,		   // u64
			type_f32,		   // f32
			type_f64,		   // f64
			
			literal_number,	   // 123.123
			literal_string,	   // "SomeString"
 		};

		static Token end_of_file(const Cursor& cursor);
		static Token identifier(const Cursor& cursor, std::string_view text);
		static Token number_literal(const Cursor& cursor, std::string_view text);
		static Token string_literal(const Cursor& cursor, std::string_view text);
		static Token symbol(const Cursor& cursor, Type type, std::string_view text);
		static Token illegal();
		Token() = default;
		inline Type type() const noexcept { return _type; }
		inline std::string_view literal() const noexcept { return _literal; }
		static const std::unordered_map<std::string_view, Type> operator_lookup;
		static const std::unordered_map<std::string_view, Type> keyword_lookup;

	  private:
		Type _type = Type::none;
		std::string_view _literal = "";
		Cursor _cursor;
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
		return std::format_to(ctx.out(), "{}({}) ", obj.type(), obj.literal());
	}
};

