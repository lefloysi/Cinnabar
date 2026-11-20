#pragma once


namespace lf {
	struct Cursor {
		u64 line_no{};
		u64 char_no{};
		u64 position{};
	};
}
