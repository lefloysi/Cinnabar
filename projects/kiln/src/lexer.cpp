#include "lexer.hpp"

#include <print>
#include <expected>
#include <array>
#include <unordered_map>

namespace lf {
	std::vector<Token> Lexer::lex(Lexer&& lexer) {
		std::vector<Token> result;
		while (lexer._position < lexer._source.size()) {
			result.emplace_back(lexer.lex_next());
		}
		return result;
	}

	Lexer::Lexer(std::string_view source) : _source(std::string(source)) {}
	
	unsigned char Lexer::advance() {
		unsigned char result = peek();
		_position++;
		return result;
	}
	unsigned char Lexer::peek(u64 amount) const {
		if (_position + amount >= _source.size()) {
			return '\0';
		}
		return _source[_position + amount];
	}
	bool Lexer::skip_whitespace() {
		u64 start = _position;
		while (std::isspace(peek())) {
			advance();
		}
		return start != _position;
	}

	Token Lexer::lex_next() {
		skip_whitespace();
		uchar next = peek();
		// first, is this end of file?
		if (next == '\0') {
			return Token::end_of_file(_position);
		}

		// if its a char or _ lex an identifier
		if (can_lex_identifier(next)) {
			return lex_identifier();
		}
		// then if its a number
		else if (can_lex_number(next)) {
			return lex_number();
		}
		// this is complicated. really we wanna check if the sequence is inside the prefix tree.
		// if its not in the prefix tree we want to cause an error. TODO : Add prefix tree 
		else if (can_lex_operator(next)) {
			return lex_operator();
		}
		
		return Token::illegal(_position, {});
	}

	Token Lexer::lex_identifier() {
		advance();
		return Token::identifier(_position, {});
	}
	Token Lexer::lex_number() {
		auto is_allowed = [](unsigned char key) { return std::isdigit(key) || key == '.'; };
		advance();
		return Token::number_literal(_position, {});
	}


	Token Lexer::lex_operator() {
		u64 length = 1;
		Token::Type result = Token::Type::none;
		advance();
		return Token::punctuator(_position, Token::Type::punc_arrow_left);

	}
	bool Lexer::can_lex_identifier(unsigned char next) {
		return std::isalpha(next) || next == '_';
	}
	bool Lexer::can_lex_number(unsigned char next) {
		return std::isdigit(next);
	}
	bool Lexer::can_lex_operator(unsigned char next) {
		std::array<bool, 256> can_start; 
		can_start.fill(false);
		for (const auto& op : Token::operator_lookup) {
			if (op.first.size() == 0) {
				throw "invalid operator";
			}
			can_start[static_cast<unsigned char>(op.first[0])] = true;
		}
		return can_start[next];
	}

} // namespace lf
