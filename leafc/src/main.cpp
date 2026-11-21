
#include "types.hpp"
#include "lexer.hpp"

#include <CLI\CLI.hpp>

#include <iostream>
#include <string_view> 
#include <vector>
#include <print>

const char* code = R"(
var Foo : i32 = 5;

)";


i32 main(i32 argc, char* argv[]) {

    auto result = lf::Lexer::lex(code);
	auto tokens = *result;
    for (auto token : tokens) {
		std::println("{}", token);
    }
    return 0;
}