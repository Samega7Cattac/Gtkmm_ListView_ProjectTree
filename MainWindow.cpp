#include "MainWindow.hh"

MainWindow::MainWindow ()
{
    // Set base default window title
    set_title("ListView Tree");

    // Set ProjectTree widget has window child
    set_child(m_project_tree);
}
