#include "Gtk_Application.h"

Gtk_Application::Gtk_Application(char *argv[])
{
    application = Gtk::Application::create(argc, argv, "Customized Application");
}

int Gtk_Application::run(Gtk::Window &window){
    return application->run(window);
}

