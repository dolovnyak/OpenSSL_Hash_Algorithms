cmake_minimum_required(VERSION 3.21)
project(ft_ssl C)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME}
        main.c
        data_preprocessing.c
        sha256_algorithm.c
        md5_algorithm.c
        utilities.c
        )

# replaced executable file to root dir
set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )