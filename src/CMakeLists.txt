# All source files for the Engine
set ( SOURCES
    Engine.cc
    Window.cc
)

add_library(glad STATIC ../dep/glad/src/glad.c)
set_target_properties(glad PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(glad PUBLIC ../dep/glad/include)

# Create an object library or static library for reuse
add_library(nphys STATIC ${SOURCES})
set_target_properties(nphys PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories( nphys PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ../dep/glad/include
    ../dep/glfw/include
    models/
    ${pybind11_INCLUDE_DIRS} # Add pybind11 include directories
)
target_link_libraries(nphys PRIVATE glfw glad)

# Build the pybind11 Python module
pybind11_add_module(nphysPy bindings/Bindings.cc)
target_link_libraries(nphysPy PRIVATE nphys)
target_include_directories( nphysPy PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../dep/glfw/include
    ../dep/glad/include
)

# Create a symlink to nphys.so after building nphysPy
add_custom_command(TARGET nphysPy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        $<TARGET_FILE:nphysPy>                         # source
        $<TARGET_FILE_DIR:nphysPy>/nphys.so            # destination
    COMMENT "Creating symlink: nphys.so -> $<TARGET_FILE:nphysPy>"
)