#pragma once

#include "types.hpp"
#include "token.hpp"

namespace lf {
	namespace node {
		struct 
	}


	struct Parser {

		static void parse(Parser&& parser);

		Parser(std::span<const Tokens> tokens);

		const Token& peek(size_t amount);
		void consume(size_t amount);

		std::span<const Tokens> tokens;
		size_t index;
	}
}
