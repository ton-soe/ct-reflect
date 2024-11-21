cmake_minimum_required(VERSION 3.12)

project(ct-refl-demo)

add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES 
		CXX_STANDARD 20
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/ct-refl>"
)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}-targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION install
)