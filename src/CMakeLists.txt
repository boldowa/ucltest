#-------------------------------------------------
# ucltest main source
#-------------------------------------------------

# Compile All sources
file(GLOB_RECURSE PRJCSOURCES
	"."  "*.c"
)
file(GLOB_RECURSE PRJCPPSOURCES
	"."  "*.cpp"
)
# exclude main.c
list(FILTER PRJCSOURCES EXCLUDE REGEX ".*main.c$")
list(FILTER PRJCPPSOURCES EXCLUDE REGEX ".*main.cpp$")

add_library(ucltest ${PRJCSOURCES} ${PRJCPPSOURCES})
target_include_directories(ucltest PRIVATE
	"../include"
	"../ext/cpputest/include"
	"../ext/libucl/include"
)

set(UCLTEST_FLAGS "-Wall")
if(NOT MSVC)
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		if(UCLTEST_EXECUTE_TEST)
			add_flags(UCLTEST_FLAGS "-include CppUTest/MemoryLeakDetectorNewMacros.h")
			add_flags(UCLTEST_FLAGS "-include CppUTest/MemoryLeakDetectorMallocMacros.h")
		endif()

		if(UCLTEST_COVERAGE)
			add_flags(UCLTEST_FLAGS "--coverage")
			target_link_libraries(ucltest gcov)
			set(UCLTEST_COVERAGE_EXECUTE TRUE PARENT_SCOPE)
		endif()
	endif()
endif(NOT MSVC)
set_target_properties(ucltest PROPERTIES COMPILE_FLAGS ${UCLTEST_FLAGS})
target_link_libraries(ucltest ucl)

add_executable(ucltest_exe main.c)
target_link_libraries(ucltest_exe ucltest)
set_target_properties(ucltest_exe PROPERTIES OUTPUT_NAME ucltest)

