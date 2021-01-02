find_package(GTest REQUIRED)

add_executable(test test.cpp)
target_link_libraries(test GTest::GTest libevaluate_core)