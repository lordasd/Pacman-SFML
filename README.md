# Pacman SFML Project
### Created by: David Zaydenberg

# How to use (Windows)
### Files to have
1) SFML 2.5.1 - https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-64-bit.zip
2) Latest Visual Studio version

### Adding levels
1) Add a level file to /resources/levels/
2) Add to playlist file the name of the level
3) In the CMakeLists add the line "configure_file ("levelname.txt" ${CMAKE_BINARY_DIR} COPYONLY)"
