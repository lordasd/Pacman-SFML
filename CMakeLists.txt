cmake_minimum_required (VERSION 3.23)

project (oop1_project)
set (MY_AUTHORS "david_zaydenberg")

include (cmake/CompilerSettings.cmake)

add_executable (${CMAKE_PROJECT_NAME} WIN32)

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)

#-----------------------------------------------#
add_subdirectory (include)
add_subdirectory (include/menu)
add_subdirectory (include/movingobjects)
add_subdirectory (include/movingobjects/ghost)
add_subdirectory (include/movingobjects/pacman)
add_subdirectory (include/staticobjects)
add_subdirectory (include/staticobjects/bonus)
add_subdirectory (include/singeltonresources)
#-----------------------------------------------#
add_subdirectory (src)
add_subdirectory (src/menu)
add_subdirectory (src/movingobjects)
add_subdirectory (src/movingobjects/ghost)
add_subdirectory (src/movingobjects/pacman)
add_subdirectory (src/staticobjects)
add_subdirectory (src/staticobjects/bonus)
add_subdirectory (src/singeltonresources)
#-----------------------------------------------#
add_subdirectory (resources/images)
add_subdirectory (resources/images/bonus)
add_subdirectory (resources/images/ghost/blinky)
add_subdirectory (resources/images/ghost/clyde)
add_subdirectory (resources/images/ghost/inky)
add_subdirectory (resources/images/ghost/pinky)
add_subdirectory (resources/images/ghost/scaredghost)
add_subdirectory (resources/images/menu)
add_subdirectory (resources/images/pacman)
add_subdirectory (resources/images/staticobjects)
add_subdirectory (resources/images/ui)
add_subdirectory (resources/audio)
add_subdirectory (resources/levels)
add_subdirectory (resources/fonts)
#-----------------------------------------------#

include (cmake/Zip.cmake)

set (SFML_LOCATION "C:/SFML/SFML-2.5.1")
set (SFML_DIR "${SFML_LOCATION}/lib/cmake/SFML")

find_package (SFML 2.5 COMPONENTS graphics audio REQUIRED)

set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

target_link_libraries (${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio sfml-main)

include (cmake/SFML.cmake)