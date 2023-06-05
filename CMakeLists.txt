cmake_minimum_required(VERSION 3.23)
project(a)
add_executable(a init_target.cpp)
target_link_libraries(a PUBLIC systemc)
target_link_directories(a PUBLIC 
                        "/usr/local/systemc-2.3.3/lib-linux64")
target_include_directories(a PUBLIC
                        "/usr/local/systemc-2.3.3/include"
                        "/usr/local/systemc-2.3.3/include/tlm_utils"
                        "/usr/local/systemc-2.3.3/include/tlm_core/tlm_2/tlm_2_interfaces")