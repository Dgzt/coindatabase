SET( QloseCombat_SRCS
    addcountrydialog.cpp
    localdatabase.cpp
    countriesdialog.cpp
    mainwindow.cpp
    main.cpp
)

# Tell CMake to create the executable file
ADD_EXECUTABLE( ${PROJECT_NAME} ${QloseCombat_SRCS} )

# Use the Widgets module from Qt 5.
qt5_use_modules( ${PROJECT_NAME} Widgets Sql )
