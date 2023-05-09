#ifndef GUI_MAINWINDOW_HH
#define GUI_MAINWINDOW_HH

// Widgets headers
#include "ProjectTree.hh"

// GTKMM headers
#include <gtkmm/applicationwindow.h>

//! @brief This is the main window, it constructs the window widgets and childs
//!
//! The main window contain all the base resources which will appear on screen.
//! The derived objects will be contained inside the base classes, and forward.
//!
class MainWindow : public Gtk::ApplicationWindow
{
public:

    //! @brief Windows constructor with
    //!
    //! Creates and sets the widgets in place, taking the following criteria:
    //!
    MainWindow();

    //! @brief Windows destructor
    //!
    //! This class is designed no to be derived
    //!
    ~MainWindow() override = default;

private:

    //! @brief Project tree box.
    //!
    ProjectTree m_project_tree;
};

#endif // GUI_MAINWINDOW_HH
