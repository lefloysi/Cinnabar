
find_package("CLI11" CONFIG REQUIRED)
find_package("LLVM" CONFIG REQUIRED)



add_executable("leafc")


if (MSVC)
	target_compile_options("leafc" PRIVATE 
		/W3 
		/MP # multithreaded build
		/WX # warnings as errors
		/ZI 
	)
endif()
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "leafc")


target_sources("leafc" PRIVATE 
"src/main.cpp"
"src/lexer.cpp" 
"src/token.cpp"
)

target_include_directories("leafc" PUBLIC "include")
target_link_libraries("leafc" PRIVATE CLI11::CLI11 LLVM::LLVM)