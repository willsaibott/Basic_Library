#ifndef GTK_CUSTOM_WINDOW_H
#define GTK_CUSTOM_WINDOW_H

#include "../../../Library/Structures/Basic.h"
#include "Gtk_Basic.h"


class Gtk_CustomWindow : public Gtk::Window{
protected:
    string window_title;
    windowSize window_size;
    const Glib::RefPtr<Gtk::Application> &application;
    bool maximized = false;
public:

    Gtk_CustomWindow(const Glib::RefPtr<Gtk::Application> &app);
    Gtk_CustomWindow(const Glib::RefPtr<Gtk::Application> &app, string title, windowSize size);
    virtual ~Gtk_CustomWindow();

    //getters
    string getTitle(){return window_title;}
    windowSize getSize(){return window_size;}
    bool isMaximized(){return maximized;}

    //setters
    void setTitle(string title);
    void setSize(windowSize size);
    void setDefaultEvents();

    //events
    virtual bool onCloseButtonClicked(GdkEventAny*);
    virtual bool onWindowStateChange(GdkEventWindowState*);
    virtual bool onMaximizeButtonClicked(GdkEventWindowState*);
    virtual bool onDesMaximizeButtonClicked(GdkEventWindowState*);
    virtual bool onMinimizeButtonClicked(GdkEventWindowState*);
    virtual bool onFullScreen(GdkEventWindowState*);
    virtual bool onFocus(GdkEventFocus*);
    virtual bool onLostFocus(GdkEventFocus*);

    //others
    void setPosition(point_2D<int> p);



    //others
};




#endif // WINDOW_H
