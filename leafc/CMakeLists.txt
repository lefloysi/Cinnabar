

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

add_executable("leafc")

if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "leafc")
	target_compile_options("leafc" PRIVATE 
		/W3 # high warning level
		/MP # multithreaded build
		/WX # warnings as errors
	)
endif()


target_sources("leafc" PRIVATE 
	"src/main.cpp"
	"src/lexer.cpp" 
	"src/token.cpp"
	"src/error.cpp"
)

target_include_directories("leafc" PUBLIC "include")
target_link_libraries("leafc" PRIVATE CLI11::CLI11 ${llvm_libs})