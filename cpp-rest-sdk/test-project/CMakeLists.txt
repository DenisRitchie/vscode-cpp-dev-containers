cmake_minimum_required(VERSION 3.24)

project(CppRestSdk C CXX)

set(Boost_NO_WARN_NEW_VERSIONS ON)
find_package(Boost 1.80.0 REQUIRED COMPONENTS thread context coroutine filesystem iostreams chrono atomic random system date_time regex)
find_package(cpprestsdk REQUIRED)

add_executable(${PROJECT_NAME} Main.cpp Headers.hpp CasaLens.hpp CasaLens.cpp DataFetcher.cpp)

target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_20
        cxx_template_template_parameters
        cxx_attributes
        cxx_auto_type
        cxx_constexpr
        cxx_decltype_incomplete_return_types
        cxx_decltype
        cxx_default_function_template_args
        cxx_defaulted_functions
        cxx_inheriting_constructors
        cxx_final
        cxx_lambdas
        cxx_noexcept
        cxx_nullptr
        cxx_override
        cxx_range_for
        cxx_raw_string_literals
        cxx_strong_enums
        cxx_contextual_conversions
        cxx_decltype_auto
        cxx_digit_separators
        cxx_generic_lambdas
        cxx_lambda_init_captures
        cxx_relaxed_constexpr
        cxx_return_type_deduction
        cxx_variable_templates
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        cpprestsdk::cpprest
        Boost::headers
        Boost::thread
        Boost::context
        Boost::coroutine
        Boost::filesystem
        Boost::iostreams
        Boost::chrono
        Boost::atomic
        Boost::random
        Boost::system
        Boost::date_time
        Boost::regex
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall -Wextra -pedantic -Werror -fstrict-enums -fconcepts -fcoroutines -fpermissive
)

add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
add_dependencies(${PROJECT_NAME} copy_assets)
