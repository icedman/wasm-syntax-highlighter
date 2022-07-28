// Copyright 2015 The Emscripten Authors.  All rights reserved.
// Emscripten is available under two separate licenses, the MIT license and the
// University of Illinois/NCSA Open Source License.  Both these licenses can be
// found in the LICENSE file.

#include <string>

#include <textmate.h>
#include <grammars.h>
#include <themes.h>

#define SKIP_PARSE_THRESHOLD 500

#define EXPORT                                                                 \
  extern "C" __attribute__((visibility("default"))) __attribute__((used))

EXPORT void initialize()
{
	Textmate::load_theme_data(THEME_MONOKAI);
	Textmate::load_language_data(GRAMMAR_CPP);
}

std::string string_buffer;
std::vector<textstyle_t> text_styles;

EXPORT int highlight(const char *code, bool start)
{
	text_styles = Textmate::run_highlighter((char*)code, Textmate::language_info(0), Textmate::theme(),
			NULL,
			start ? NULL : Textmate::previous_block_data()
			);
	return text_styles.size();
}

EXPORT int highlight_buffer(bool start)
{
	printf("%s\n", string_buffer.c_str());
	return highlight(string_buffer.c_str(), start);
}

EXPORT int get_style_span(int index)
{
	if (index > text_styles.size() - 1) {
		return 0;
	}

	int res = 0;

	textstyle_t s = text_styles[index];

	// start
	res |= (s.start);
	// length
	res |= (s.length << 16);

	// printf("%d-%d rgb(%d, %d, %d) %d\n", s.start, s.length, s.r, s.g, s.b, res);
	return res;
}

EXPORT int get_style_color(int index)
{
	if (index > text_styles.size() - 1) {
		return 0;
	}

	int res = 0;

	textstyle_t s = text_styles[index];

	if (s.r > 255) s.r = 255;
	if (s.g > 255) s.g = 255;
	if (s.b > 255) s.b = 255;

	// rgb
	res |= (s.r);
	res |= (s.g << 8);
	res |= (s.b << 16);

	// printf("%d-%d rgb(%d, %d, %d)\n", s.start, s.length, s.r, s.g, s.b);
	return res;
}


EXPORT void begin_string()
{
	string_buffer = "";
}

EXPORT void push_character(int c)
{
	string_buffer += static_cast<char>(c);
	// printf(">%s %d\n", string_buffer.c_str(), c);
}