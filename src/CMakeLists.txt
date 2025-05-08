# All source files for the Engine
set ( SOURCES
    Engine.cc
    Window.cc
    EOMs.cc
    Frames.cc
    Collisions.cc
)

# Create an object library or static library for reuse
add_library(nphys STATIC ${SOURCES})
set_target_properties(nphys PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories( nphys PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    models/
    ${pybind11_INCLUDE_DIRS} # Add pybind11 include directories
)
target_link_libraries(nphys PRIVATE Qt5::Widgets )

# Build the pybind11 Python module
pybind11_add_module(nphysPy bindings/Bindings.cc)
target_link_libraries(nphysPy PRIVATE nphys Qt5::Widgets)
target_include_directories( nphysPy PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Create a symlink to nphys.so after building nphysPy
add_custom_command(TARGET nphysPy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        $<TARGET_FILE:nphysPy>                         # source
        $<TARGET_FILE_DIR:nphysPy>/nphys.so            # destination
    COMMENT "Creating symlink: nphys.so -> $<TARGET_FILE:nphysPy>"
)