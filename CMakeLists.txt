cmake_minimum_required(VERSION 3.11)
project(first-engine)

aux_source_directory("${PROJECT_SOURCE_DIR}/FirstEngine" FE_SOURCES)
add_executable(${PROJECT_NAME} ${FE_SOURCES})
