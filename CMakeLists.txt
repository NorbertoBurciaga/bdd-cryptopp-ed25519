cmake_minimum_required(VERSION 3.13)

project(bdd-cryptopp-ed25519)

# find boost
find_package(Boost 1.69 REQUIRED COMPONENTS
    filesystem
    program_options
    regex
)

# find google test 
enable_testing()
find_package(GTest REQUIRED)

# Output directory settings
set(output_dir ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${output_dir})

#Subdirectories
add_subdirectory(tests/features)
