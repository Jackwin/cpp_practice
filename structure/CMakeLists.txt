cmake_minimum_required(VERSION 3.5)

project (struct_learn)

set(SOURCES
    src/main.cpp
    )

add_executable(struct_learn ${SOURCES})

target_include_directories(struct_learn
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)