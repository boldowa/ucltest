#-------------------------------------------------
# ucltest CMake
#-------------------------------------------------
cmake_minimum_required(VERSION 3.10)

if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "No build type selected, default to Debug")
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING 
                "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()
option(UCLTEST_EXECUTE_TEST "Execute test suite" ON)
option(UCLTEST_COVERAGE "Check code coverage" ON)
set(UCLTEST_COVERAGE_EXECUTE FALSE)

project(ucltest)
include(cmake/macs.cmake)

add_subdirectory(ext)
add_subdirectory(src)

if(UCLTEST_EXECUTE_TEST)
	find_program(GCOV gcov)
	if(NOT GCOV)
		message(FATAL_ERROR "-- gcov not found...")
	endif()
	message("-- gcov found: ${GCOV}")

	add_subdirectory(test)
	add_test(NAME ucltest COMMAND ucltest_test)
	add_custom_target(check ALL
		COMMAND echo "-- Executes ucltest_test ..."
		COMMAND test/ucltest_test -c
		)
	add_dependencies(check ucltest_test)
	add_dependencies(ucltest_exe check)
	if(UCLTEST_COVERAGE_EXECUTE)
		add_custom_target(coverage ALL
			COMMAND rm -rf gcov
			COMMAND mkdir gcov
			COMMAND find src/CMakeFiles/ucltest.dir/ -type f -name "*.gcno" -print0 | xargs -0 env LANG=C gcov
			COMMAND mv *.gcov gcov
			)
		add_dependencies(coverage check)
		add_dependencies(ucltest_exe coverage)
	endif(UCLTEST_COVERAGE_EXECUTE)
endif(UCLTEST_EXECUTE_TEST)



