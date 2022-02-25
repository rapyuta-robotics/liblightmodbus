cmake_minimum_required(VERSION 3.3)
project(lightmodbus)

add_library(
    lightmodbus
    "${PROJECT_SOURCE_DIR}/src/core.c"
    "${PROJECT_SOURCE_DIR}/src/master.c"
    "${PROJECT_SOURCE_DIR}/src/slave.c"
    "${PROJECT_SOURCE_DIR}/src/master/mcoils.c"
    "${PROJECT_SOURCE_DIR}/src/master/mdiscreteinputs.c"
    "${PROJECT_SOURCE_DIR}/src/master/minputregisters.c"
    "${PROJECT_SOURCE_DIR}/src/master/mregisters.c"
    "${PROJECT_SOURCE_DIR}/src/slave/scoils.c"
    "${PROJECT_SOURCE_DIR}/src/slave/sdiscreteinputs.c"
    "${PROJECT_SOURCE_DIR}/src/slave/sinputregisters.c"
    "${PROJECT_SOURCE_DIR}/src/slave/sregisters.c"
)

target_compile_definitions(lightmodbus PUBLIC LIGHTMODBUS_MASTER_REGISTERS=1)

target_include_directories(lightmodbus PUBLIC include)
