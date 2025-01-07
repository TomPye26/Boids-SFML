cmake_minimum_required(VERSION 3.10)

# Project name
project(SFMLProject)

set(CMAKE_CXX_STANDARD 17)

# Add the SFML directory
set(SFML_DIR "C:/Program Files/SFML/lib/cmake/SFML")

# Find the SFML package
find_package(SFML 2.6.2 REQUIRED graphics window system)

add_executable(SFMLApp src/main.cpp src/BoidObject.cpp src/Flock.cpp)

# Link SFML libraries
target_link_libraries(SFMLApp sfml-graphics sfml-window sfml-system)

# Copy bin files to build dir (a bit hacky)
add_custom_command(TARGET SFMLApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "C:/Program Files/SFML/bin"  
        $<TARGET_FILE_DIR:SFMLApp>           
)