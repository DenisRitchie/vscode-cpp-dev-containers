cmake_minimum_required(VERSION 3.28)

project(CppWebToolKit C CXX)

add_executable(${PROJECT_NAME} Main.cpp)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        /usr/local/include
)

target_link_directories(${PROJECT_NAME}
    PRIVATE
        /usr/local/lib
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        wthttp wt
)

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

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall -Wextra -pedantic -Werror -fstrict-enums -fconcepts -fcoroutines -fpermissive
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/editSide-template.xml DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
