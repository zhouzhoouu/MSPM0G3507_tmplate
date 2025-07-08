
cmake_minimum_required(VERSION 3.13)

include("cmake/gcc-arm-none-eabi.cmake")

project(MSPM0G3507_Tmplate C)

# 设置交叉编译工具链
# 编译选项
set(CMAKE_C_FLAGS "-mcpu=cortex-m0plus -mthumb -g -O2 -ffunction-sections -fdata-sections")
set(CMAKE_EXE_LINKER_FLAGS "-T${CMAKE_SOURCE_DIR}/Startup/mspm0g3507.lds -Wl,--gc-sections -Wl,-Map=${PROJECT_NAME}.map")

file(GLOB_RECURSE USER_SOURCES "${CMAKE_SOURCE_DIR}/User/Src/*.c")

include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/ti/driverlib
        ${CMAKE_SOURCE_DIR}/Sysconfig
        ${CMAKE_SOURCE_DIR}/CMSIS/Core/Include
        ${CMAKE_SOURCE_DIR}/CMSIS/DSP/Include
        ${CMAKE_SOURCE_DIR}/CMSIS/DSP/PrivateInclude
        ${CMAKE_SOURCE_DIR}/User/Inc
)

# 源码
add_executable(${PROJECT_NAME}.elf
        Startup/startup_mspm0g350x_gcc.c
        Sysconfig/ti_msp_dl_config.c
        ${USER_SOURCES}
)

target_link_libraries(${PROJECT_NAME}.elf
        ${CMAKE_SOURCE_DIR}/Lib/driverlib.a

)


target_compile_definitions(${PROJECT_NAME}.elf PRIVATE
        __MSPM0G3507__
)

target_link_options(${PROJECT_NAME}.elf PRIVATE
        --specs=nosys.specs
)

