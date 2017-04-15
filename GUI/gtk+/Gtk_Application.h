#ifndef GTK_APPLICATION_H
#define GTK_APPLICATION_H

#include "Gtk_Basic.h"
#include <thread>
using std::thread;

class Gtk_Application
{
protected:
    int argc = 1;
    Glib::RefPtr<Gtk::Application> application;
public:
    Glib::RefPtr<Gtk::Application> getApplication(){return application;}
    Gtk_Application(char *argv[]);

    int run(Gtk::Window &window);
};

#endif // GTK_APPLICATION_H
