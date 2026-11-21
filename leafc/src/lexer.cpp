#include "lexer.hpp"

#include <print>
#include <expected>
#include <array>
#include <unordered_map>

namespace lf {
	std::expected<std::vector<Token>, std::vector<error>> Lexer::lex(Lexer&& lexer) {
		std::vector<Token> result;
		while (lexer.cursor.position < lexer.source.size()) {
			auto token_result = lexer.lex_next();
			if (!token_result) {
				std::println("{}: ya messed up", token_result.error());
				result.emplace_back(Token::illegal());
			} else {
				result.emplace_back(std::move(*token_result));
			}

		}
		return result;
	}

	Lexer::Lexer(const char* source) : source(source) {}
	Lexer::Lexer(std::string_view source) : source(source) {}
	
	unsigned char Lexer::advance() {
		unsigned char result = peek();
		if (result == '\n') {
			cursor.line_no++;
			cursor.char_no = 0;
		} else {
			cursor.char_no++;
		}
		cursor.position++;
		return result;
	}
	unsigned char Lexer::peek(u64 amount) const {
		if (cursor.position + amount >= source.size()) {
			return '\0';
		}
		return source[cursor.position + amount];
	}
	bool Lexer::skip_whitespace() {
		u64 start = cursor.position;
		while (std::isspace(peek())) {
			advance();
		}
		return start != cursor.position;
	}

	std::expected<Token, error> Lexer::lex_next() {
		skip_whitespace();
		unsigned char next = peek();
		// first, is this end of file?
		if (next == '\0') {
			return Token::end_of_file(cursor);
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
		// if its not in the prefix tree we want to cause an error.
		else if (can_lex_operator(next)) {
			return lex_operator();
		}
		advance();
		return std::unexpected(error::format("bad charackter: '{}'", next));
	}

	Token Lexer::lex_identifier() {
		auto is_allowed = [](unsigned char key) { return std::isalnum(key) || key == '_'; };
		const Cursor cursor = this->cursor;
		return Token::identifier(cursor, max_munch(is_allowed));
	}
	Token Lexer::lex_number() {
		auto is_allowed = [](unsigned char key) { return std::isdigit(key) || key == '.'; };
		const Cursor cursor = this->cursor;
		return Token::number_literal(cursor, max_munch(is_allowed));
	}
	Token Lexer::lex_operator() {
		u64 length = 1;
		const Cursor cursor = this->cursor;
		Token::Type result = Token::Type::none;
		while (true) {
			std::string_view view = source.substr(cursor.position, length);
			if (auto it = Token::operator_lookup.find(view); it == Token::operator_lookup.end()) {
				break;
			}
			else {
				result = it->second;
			}
			advance();
			length++;
		}
		return Token::symbol(cursor, result, source.substr(cursor.position, length - 1));
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
