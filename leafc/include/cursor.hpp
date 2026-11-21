#pragma once


namespace lf {
	struct Cursor {
		u64 line_no = 1;
		u64 char_no = 1;
		u64 position = 0;
	};
}
