#pragma once

#include "types.hpp"

#include <string_view>
namespace lf {
	class Token {
	  public:
		enum class Type {
			none,
			identifier,
			eof,
			illegal,

			keyword_return,	   // return
			keyword_fn,		   // fn
			keyword_var,	   // var
			keyword_const,	   // const
			keyword_class,	   // class
			keyword_union,	   // union
			keyword_enum,	   // enum

			key_decimal,	   // .
			key_plus,		   // +
			key_minus,		   // -
			key_asterik,	   // *
			key_slash,		   // /
			key_arrow_right,   // ->
			key_arrow_left,	   // <-
			key_bitshift_left, // <<
			key_modulus,	   // %
			key_equal_equal,   // ==
			key_greater_equal, // >=
			key_lesser_equal,  // <=
			key_lesser_than,   // <
			key_greater_than,  // >
			key_semicolon,	   // ;
			key_colon,		   // :
			key_lparan,		   // (
			key_rparan,		   // )
			key_lbracket,	   // [
			key_rbracket,	   // ]
			key_lbrace,		   // {
			key_rbrace,		   // }

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

		};

	  private:
		Type type;
		std::string_view literal;

		u64 line_pos{};
		u64 char_pos{};
	};
} // namespace lf
