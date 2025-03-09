cmake_minimum_required (VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("TOPO132")

file(GLOB SRC "*.hpp" "*.cpp")
file(COPY ${SRC} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable (TOPO132 ${SRC})


include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(dependencies)

enable_testing()
add_executable (tests tests.cc)

target_link_libraries(tests PUBLIC GTest::gtest_main)
target_link_libraries(tests PUBLIC OpenSSL::SSL)
target_link_libraries(tests PUBLIC OpenSSL::Crypto)

target_link_libraries(${PROJECT_NAME} PUBLIC OpenSSL::SSL)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenSSL::Crypto)

include(GoogleTest)
gtest_discover_tests(tests)