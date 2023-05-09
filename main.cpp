// GTKMM headers
#include <gtkmm/applicationwindow.h>

// GLIBMM headers
#include <glibmm/init.h>

// Widgets headers
#include "MainWindow.hh"

int
main(int argc, char* argv[])
{
    // Initializes glib
    Glib::init();

    // Creates a new application instance
    // Takes argc and argv as arguments for gtk standard command options.
    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create("com.gtkmm.listview_tree");

    // Show window instances
    return app->make_window_and_run<MainWindow>(argc, argv);
}
