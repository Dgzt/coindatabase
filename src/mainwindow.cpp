#include "QDebug"
#include "QAction"
#include "QMenu"
#include "QMenuBar"
#include "mainwindow.h"

MainWindow::MainWindow()
{
    qDebug()<< "Init.";

    createMenu();
}

void MainWindow::createMenu()
{
    QAction *quitAction = new QAction(tr("Quit"), this);

    connect(quitAction, SIGNAL( triggered() ), this, SLOT( close() ) );

    QMenu *fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction( quitAction );
}
