#pragma once

#include "types.hpp"

#include <expected>
#include <string>
#include <filesystem>
#include <string_view>

namespace lf {
	class error {
	  public:
		template<typename... Args>
		static error format(std::format_string<Args...> fmt, Args&&... args);

		error(std::string_view message);
		std::string_view message() const;
	  private:
		std::string _message;
	};
	template<typename... Args>
	error error::format(std::format_string<Args...> fmt, Args&&... args) {
		return error(std::format(fmt, std::forward<Args>(args)...));
	}

	struct error_location {
		std::filesystem::path path;
		u64 position;
	};

	struct bad_character_error {
		explicit operator error() {
		
			return error("foo");
		}
	};
}

template<>
struct std::formatter<lf::error> {
	constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

	auto format(const lf::error& obj, auto& ctx) const {
		return std::format_to(ctx.out(), "{}", obj.message());
	}
};


template<>
struct std::formatter<lf::error_location> {
	constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

	auto format(const lf::error_location& obj, auto& ctx) const {
		return std::format_to(ctx.out(), "{}({})", obj.path, obj.position);
	}
};
