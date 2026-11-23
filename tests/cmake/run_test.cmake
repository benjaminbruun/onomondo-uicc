# Copyright (c) 2026 Onomondo ApS. All rights reserved.
# SPDX-License-Identifier: GPL-3.0-only

# Test runner, used by ss_add_test() in tests/CMakeLists.txt. Run in script
# mode:
#
#   cmake -DTEST_NAME=<name> -DTEST_EXE=<path> -DWORK_DIR=<dir>
#         [-DFILES_SRC=<dir>] [-DREFERENCE=<file>] -P run_test.cmake
#
# 1. Recreates WORK_DIR, so nothing is left over from an earlier run.
# 2. If FILES_SRC is given, copies it into WORK_DIR. The test then finds a
#    pristine profile at ./files and never writes to the source tree.
# 3. Runs TEST_EXE in WORK_DIR. A non-zero exit (failed assert, crash,
#    sanitizer report) fails the test.
# 4. If REFERENCE is given, the test's stdout must match it.

foreach(var TEST_NAME TEST_EXE WORK_DIR)
	if(NOT ${var})
		message(FATAL_ERROR "run_test.cmake: ${var} must be set")
	endif()
endforeach()

set(out_file "${WORK_DIR}/${TEST_NAME}.out")
set(err_file "${WORK_DIR}/${TEST_NAME}.err")

function(print_file label path)
	file(READ "${path}" content)
	message("----- ${label} (${path})\n${content}-----")
endfunction()

file(REMOVE_RECURSE "${WORK_DIR}")
file(MAKE_DIRECTORY "${WORK_DIR}")
if(FILES_SRC)
	file(COPY "${FILES_SRC}" DESTINATION "${WORK_DIR}")
endif()

execute_process(
	COMMAND "${TEST_EXE}"
	WORKING_DIRECTORY "${WORK_DIR}"
	RESULT_VARIABLE exit_code
	OUTPUT_FILE "${out_file}"
	ERROR_FILE "${err_file}"
)

if(NOT exit_code EQUAL 0)
	print_file("stdout" "${out_file}")
	print_file("stderr" "${err_file}")
	message(FATAL_ERROR "${TEST_NAME}: exited with '${exit_code}'")
endif()

if(REFERENCE)
	execute_process(
		COMMAND "${CMAKE_COMMAND}" -E compare_files --ignore-eol "${out_file}" "${REFERENCE}"
		RESULT_VARIABLE differs
		OUTPUT_QUIET ERROR_QUIET
	)
	if(differs)
		find_program(DIFF_TOOL diff)
		if(DIFF_TOOL)
			execute_process(COMMAND "${DIFF_TOOL}" -u --strip-trailing-cr "${REFERENCE}" "${out_file}")
		else()
			print_file("expected" "${REFERENCE}")
			print_file("actual" "${out_file}")
		endif()
		message(FATAL_ERROR "${TEST_NAME}: stdout does not match ${REFERENCE}")
	endif()
endif()
