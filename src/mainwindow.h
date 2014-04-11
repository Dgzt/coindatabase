#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow{

public:
    MainWindow();

private:
    /*!
     * Create the menu.
     */
    void createMenu();
};

#endif // MAINWINDOW_H
