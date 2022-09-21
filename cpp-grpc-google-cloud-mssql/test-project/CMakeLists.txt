cmake_minimum_required(VERSION 3.24)

project(SQLServerNativeProgram C CXX)

add_executable(${PROJECT_NAME} Main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    /usr/lib/x86_64-linux-gnu/libodbc.so
    /usr/lib/x86_64-linux-gnu/libodbcinst.so
    /usr/lib/x86_64-linux-gnu/libodbccr.so
)
