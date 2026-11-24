
#include "error.hpp"


namespace lf {
	error::error(std::string_view message) : _message(std::string(message)) {}
	std::string_view error::message() const { return std::string_view(_message); }

}
