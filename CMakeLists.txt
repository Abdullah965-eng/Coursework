
cmake_minimum_required(VERSION 3.20)
project(power_quality_analyser C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(code)

add_executable(power_quality_analyser
        code/main.c
        code/waveform.c
        code/io.c
)

# Link math library (required for sqrt in waveform.c)
target_link_libraries(power_quality_analyser m)

# Enable warnings
target_compile_options(power_quality_analyser PRIVATE -Wall -Wextra -pedantic)
