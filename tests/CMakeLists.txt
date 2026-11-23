# Copyright (c) 2024 Onomondo ApS. All rights reserved.
# SPDX-License-Identifier: GPL-3.0-only

# Enable testing for current directory and below.
enable_testing()

set(SS_TEST_RUNNER ${CMAKE_CURRENT_LIST_DIR}/cmake/run_test.cmake)

# ss_add_test(<name> [LIBS <lib>...] [FILES] [NO_REFERENCE] [RUN_IF <condition>])
#
# Builds <name>.c into the executable <name> and registers it as the CTest test
# <name>. Each run gets a fresh, private working directory, <name>.run in the
# binary directory.
#
# A test fails when it exits non-zero (failed assert(), crash, sanitizer
# report). In addition its stdout must match <name>.ok, unless NO_REFERENCE is
# given for a test that checks everything itself with assert().
#
#   LIBS          Libraries to link.
#   FILES         Copy the repository's files/ profile into the working
#                 directory before every run. Required for tests that go
#                 through the storage layer; they must never run against (and
#                 write to) the profile in the source tree.
#   NO_REFERENCE  The test has no <name>.ok; only the exit code counts.
#   RUN_IF        Register the test only if <condition> holds, e.g.
#                 RUN_IF NOT CONFIG_EXTERNAL_KEY_LOAD. It is built either way.
function(ss_add_test name)
	cmake_parse_arguments(ARG "FILES;NO_REFERENCE" "" "LIBS;RUN_IF" ${ARGN})
	if(ARG_UNPARSED_ARGUMENTS)
		message(FATAL_ERROR "ss_add_test(${name}): unknown arguments: ${ARG_UNPARSED_ARGUMENTS}")
	endif()

	add_executable(${name} ${name}.c)
	target_include_directories(${name} PRIVATE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/include)
	if(ARG_LIBS)
		target_link_libraries(${name} PRIVATE ${ARG_LIBS})
	endif()
	# Tests rely on assert(); keep it alive in every build type.
	target_compile_options(${name} PRIVATE -UNDEBUG)

	set(reference ${CMAKE_CURRENT_SOURCE_DIR}/${name}.ok)
	if(ARG_NO_REFERENCE)
		if(EXISTS ${reference})
			message(FATAL_ERROR "ss_add_test(${name}): NO_REFERENCE given, but ${reference} exists")
		endif()
		set(reference "")
	elseif(NOT EXISTS ${reference})
		message(FATAL_ERROR "ss_add_test(${name}): ${reference} not found. "
			"Add it, or pass NO_REFERENCE if the test only uses assert().")
	endif()

	if(DEFINED ARG_RUN_IF)
		if(NOT (${ARG_RUN_IF}))
			return()
		endif()
	endif()

	set(files_src "")
	if(ARG_FILES)
		set(files_src ${PROJECT_SOURCE_DIR}/files)
	endif()

	add_test(NAME ${name}
		COMMAND ${CMAKE_COMMAND}
			-DTEST_NAME=${name}
			-DTEST_EXE=$<TARGET_FILE:${name}>
			-DWORK_DIR=${CMAKE_CURRENT_BINARY_DIR}/${name}.run
			-DFILES_SRC=${files_src}
			-DREFERENCE=${reference}
			-P ${SS_TEST_RUNNER})
endfunction()

add_subdirectory(access)
add_subdirectory(aes)
add_subdirectory(apdu)
add_subdirectory(app_transact)
add_subdirectory(btlv)
add_subdirectory(ctlv)
add_subdirectory(des)
add_subdirectory(envelope)
add_subdirectory(fcp)
add_subdirectory(list)
add_subdirectory(ota)
add_subdirectory(sms)
add_subdirectory(storage)
add_subdirectory(tlv8)
add_subdirectory(utils)
add_subdirectory(pin)
add_subdirectory(suspend)
add_subdirectory(init)
