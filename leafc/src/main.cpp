
#include "types.hpp"

#include <CLI\CLI.hpp>

#include <iostream>
#include <string_view> 
#include <vector>



const char* code = R"(
var Foo : i32 = 5;

)";


i32 main(i32 argc, char* argv[]) {

    CLI::App app{};

    CLI11_PARSE(app, argc, argv);
    return 0;
}