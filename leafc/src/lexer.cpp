#include "lexer.hpp"

#include <print>
#include <expected>
#include <unordered_map>

namespace lf {
	std::expected<std::vector<Token>, std::vector<error>> Lexer::lex(Lexer&& lexer) {
		std::vector<Token> result;
		while (lexer.cursor.position < lexer.source.size()) {
			auto token_result = lexer.lex_next();
			if (!token_result) {
				std::println("{}: ya messed up", token_result.error());
				Token token = result.emplace_back();
				token._type = Token::Type::illegal;
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
		if (std::isalpha(next) || next == '_') {
			return lex_identifier();
		}
		// then if its a digit
		else if (std::isdigit(next)) {
			return lex_number();
		}
		// this is complicated. really we wanna check if the sequence is inside the prefix tree.
		// if its not in the prefix tree we want to cause an error.
		else {
			return lex_operator();
		}
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
		std::string_view view = std::string_view(source.data() + cursor.position, length);
		if (auto it = Token::operator_lookup.find(view); it == Token::operator_lookup.end()) {
			advance();
			break;
		}
		else {
			result = it->second;
		}
		advance();
		length++;
	}
	return Token::symbol(cursor, result, std::string_view(source.data() + cursor.position, length - 1));
}

} // namespace lf
