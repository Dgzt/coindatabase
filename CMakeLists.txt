CMAKE_MINIMUM_REQUIRED( VERSION 2.8.9 )

PROJECT( coins )

# Find includes in corresponding build include_directories
SET( CMAKE_INCLUDE_CURRENT_DIR ON )

# Instruct CMake to run moc automatically when needed.
SET( CMAKE_AUTOMOC ON )

# Find the QtWidgets library
FIND_PACKAGE( Qt5Widgets )

IF( NOT Qt5Widgets_FOUND )
    MESSAGE( FATAL_ERROR
"---------------------------------

The Qt5Widgets library not found!

---------------------------------")
ENDIF( NOT Qt5Widgets_FOUND )

ADD_SUBDIRECTORY( src )
