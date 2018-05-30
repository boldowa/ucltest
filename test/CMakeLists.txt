#-------------------------------------------------
# UCLTEST test
#-------------------------------------------------

set(CPPUTEST_LIB CppUTest)

# Compile flags
set(UCLTEST_TEST_FLAGS "-Wall")

if(EXTENSIONS)
	list(APPEND CPPUTEST_LIB CppUTestExt)
endif(EXTENSIONS)

file(GLOB_RECURSE TESTSOURCES
	"."  "*.cpp"
)

add_executable(ucltest_test ${TESTSOURCES})
target_link_libraries(ucltest_test ucltest ${CPPUTEST_LIB})
target_include_directories(ucltest_test PRIVATE
	"../include"
	"../ext/cpputest/include"
)

if(NOT MSVC)
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		if(UCLTEST_EXECUTE_TEST)
			add_flags(UCLTEST_TEST_FLAGS "-include CppUTest/MemoryLeakDetectorNewMacros.h")
			add_flags(UCLTEST_TEST_FLAGS "-include CppUTest/MemoryLeakDetectorMallocMacros.h")
		endif()
	endif()
endif(NOT MSVC)
set_target_properties(ucltest_test PROPERTIES COMPILE_FLAGS ${UCLTEST_TEST_FLAGS})


