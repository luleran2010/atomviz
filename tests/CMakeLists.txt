find_package(Catch2 CONFIG REQUIRED)

add_executable(test_parsers test_parsers.cpp)
target_link_libraries(test_parsers PRIVATE Catch2::Catch2WithMain Core)
target_compile_definitions(test_parsers PRIVATE
    RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data/"
)

include(CTest)
include(Catch)
catch_discover_tests(test_parsers)