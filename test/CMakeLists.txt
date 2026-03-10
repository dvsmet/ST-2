add_executable(${PROJECT_NAME}.test
  AllTests.cpp
  tests.cpp)

find_package(Threads REQUIRED)
find_package(GTest QUIET)
if (NOT GTest_FOUND)
  include(FetchContent)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  )
  FetchContent_MakeAvailable(googletest)
endif()
target_link_libraries(${PROJECT_NAME}.test
  ${PROJECT_NAME} GTest::gtest Threads::Threads)
target_compile_definitions(${PROJECT_NAME}.test 
  PRIVATE TEST_DIR="${CMAKE_CURRENT_LIST_DIR}/test")

install(TARGETS ${PROJECT_NAME}.test
        DESTINATION "${tool_dest}")