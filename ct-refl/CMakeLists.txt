cmake_minimum_required(VERSION 3.12)

project(ct-refl)

set(INSTALL_DIR "lib/cmake/${LIB_NAME}")

# Install header files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION ${PROJECT_NAME}                
    FILES_MATCHING PATTERN "*.h"
)

