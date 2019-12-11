cmake_minimum_required(VERSION 3.0)

project(kursach VERSION 1.0 LANGUAGES C CXX)

execute_process (
    COMMAND bash -c "lsb_release -si"
    OUTPUT_VARIABLE host_distr
)

if (${host_distr} STREQUAL "Ubuntu\n")
    set(math_gl_lib_name mgl)
else()
    set(math_gl_lib_name mgl2)
endif()

set(release_flags
    "-O3 -mtune=native -march=native -g -Wall -ftemplate-depth=10000 -std=c++17"
)

set(compile_flags "-fsanitize=address -fsanitize=leak -fsanitize=undefined \
-fdiagnostics-color=always -fdiagnostics-generate-patch \
-g -Wall -ftemplate-depth=10000 -std=c++17"
)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${release_flags}")

message("CMAKE_CXX_FLAGS" ${CMAKE_CXX_FLAGS})

set(method_source_files
    methods/implicit_forward_flow.cpp
    methods/explicit_forward_flow.cpp
    methods/implicit_backward_flow.cpp
    methods/explicit_backward_flow.cpp
    methods/cheharda.cpp
    methods/method_utils.cpp
    methods/fake_method_copy.cpp
    methods/common_implicit.cpp
    methods/predictor_corrector.cpp
)

set(plots_source_files
    plots/calc_min_max_and_draw_plots.cpp;
    plots/plots.cpp;
    plots/visualization.cpp
)

add_executable(plots_main.cpp.elf
    plots/plots_main.cpp 
    ${plots_source_files}
    ${method_source_files}
)
set_target_properties(plots_main.cpp.elf
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY plots
)

#target_sources(plots_main.cpp.elf)

target_link_libraries(plots_main.cpp.elf
    ${math_gl_lib_name}
    pthread
)


add_custom_target(pictures ALL DEPENDS plots_main.cpp.elf
    COMMAND make -f ${CMAKE_CURRENT_SOURCE_DIR}/Makefile.part pictures
)

add_custom_target(video 
    COMMAND make -f ${CMAKE_CURRENT_SOURCE_DIR}/Makefile.part video
)

