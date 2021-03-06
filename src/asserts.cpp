/*
	Copyright (C) 2003-2013 by David White <davewx7@gmail.com>
	
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdio.h>

#ifndef NO_EDITOR
#include "editor.hpp"
#endif

#include "asserts.hpp"
#include "code_editor_dialog.hpp"
#include "level.hpp"
#include "preferences.hpp"
#include "stats.hpp"
#include "variant.hpp"

#if defined(_WINDOWS)
#include "SDL_syswm.h"
#endif

void report_assert_msg(const std::string& m)
{
	if(level::current_ptr()) {
		std::cerr << "ATTEMPTING TO SEND CRASH REPORT...\n";
		std::map<variant,variant> obj;
		obj[variant("type")] = variant("crash");
		obj[variant("msg")] = variant(m);
#ifndef NO_EDITOR
		obj[variant("editor")] = variant(editor::last_edited_level().empty() == false);
#else
		obj[variant("editor")] = variant(false);
#endif

		if(preferences::edit_and_continue()) {
			edit_and_continue_assert(m);
		}

		stats::record(variant(&obj), level::current_ptr()->id());
		stats::flush_and_quit();
	}

#if defined(__native_client__)
	std::cerr << m;
#endif

#if defined(__ANDROID__)
	__android_log_print(ANDROID_LOG_INFO, "Frogatto", m.c_str());

#endif
	
#if defined(_WINDOWS)
	::MessageBoxA(NULL, m.c_str(), "Assertion failed", MB_OK|MB_ICONSTOP);
#endif
}

validation_failure_exception::validation_failure_exception(const std::string& m)
  : msg(m)
{
	std::cerr << "ASSERT FAIL: " << m << "\n";
}

fatal_assert_failure_exception::fatal_assert_failure_exception(const std::string& m)
  : msg(m)
{
	std::cerr << "ASSERT FAIL: " << m << "\n";
}

namespace {
	int throw_validation_failure = 0;
	int throw_fatal = 0;
}

bool throw_validation_failure_on_assert()
{
	return throw_validation_failure != 0 && !preferences::die_on_assert();
}

assert_recover_scope::assert_recover_scope()
{
	throw_validation_failure++;
}

assert_recover_scope::~assert_recover_scope()
{
	throw_validation_failure--;
}

void output_backtrace()
{
	std::cerr << get_call_stack() << "\n";
}

bool throw_fatal_error_on_assert()
{
	return throw_fatal != 0 && !preferences::die_on_assert();
}

fatal_assert_scope::fatal_assert_scope()
{
	throw_fatal++;
}

fatal_assert_scope::~fatal_assert_scope()
{
	throw_fatal--;
}
