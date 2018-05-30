#--- Builds CppUTest
option(EXTENSIONS "Uses CppUTestExt" OFF)
option(TESTS "Tests CppUTest library" OFF)

add_subdirectory(libucl)

if(UCLTEST_EXECUTE_TEST)
	add_subdirectory(cpputest)
endif(UCLTEST_EXECUTE_TEST)

