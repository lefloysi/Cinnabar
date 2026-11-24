cmake_minimum_required(VERSION 3.30)


project("kiln")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


find_package("CLI11" CONFIG REQUIRED)


find_package("LLVM" CONFIG REQUIRED)
include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})
llvm_map_components_to_libnames(llvm_libs 
	Analysis
	Core
	ExecutionEngine 
	InstCombine
	Object
	OrcJIT
	RuntimeDyld
	ScalarOpts
	Support
	native
)

add_executable("kiln")

if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "leafc")
	target_compile_options("kiln" PRIVATE 
		/W3 # high warning level
		/MP # multithreaded build
		/WX # warnings as errors
	)
endif()


target_sources("kiln" PRIVATE 
	"src/arena.cpp"
	"src/error.cpp"
	"src/lexer.cpp" 
	"src/main.cpp"
	"src/parser.cpp"
	"src/string_interner.cpp"
	"src/token.cpp"
)

target_include_directories("kiln" PUBLIC "include")
target_link_libraries("kiln" PRIVATE CLI11::CLI11 ${llvm_libs})