#ifndef GTK_CUSTOM_WINDOW_CPP
#define GTK_CUSTOM_WINDOW_CPP

#include "Gtk_CustomWindow.h"

Gtk_CustomWindow::Gtk_CustomWindow(const Glib::RefPtr<Gtk::Application> &app) : Gtk::Window(),  application(app){
    this->unmaximize();
    this->setDefaultEvents();
    this->show_all_children(true);
}

Gtk_CustomWindow::Gtk_CustomWindow(const Glib::RefPtr<Gtk::Application> &app, std::string title, windowSize size) :  Gtk::Window(),  application(app){
    this->unmaximize();
    this->setDefaultEvents();
    setTitle(title);
    setSize(size);
    this->show_all_children(true);
}

Gtk_CustomWindow::~Gtk_CustomWindow(){

}

//setters
void Gtk_CustomWindow::setSize(windowSize size){
    this->window_size = size;
    this->set_default_size(size.width, size.height);
}

void Gtk_CustomWindow::setTitle(std::string title){
    this->window_title = title;
    this->set_title(title);
}

void Gtk_CustomWindow::setDefaultEvents(){
    this->signal_delete_event().connect(sigc::mem_fun(this, &Gtk_CustomWindow::onCloseButtonClicked));
    this->signal_window_state_event().connect(sigc::mem_fun(this, &Gtk_CustomWindow::onWindowStateChange));
    this->signal_focus_in_event().connect(sigc::mem_fun(this, &Gtk_CustomWindow::onFocus));
    this->signal_focus_out_event().connect(sigc::mem_fun(this, &Gtk_CustomWindow::onLostFocus));
}

//events
bool Gtk_CustomWindow::onCloseButtonClicked(GdkEventAny*){
    application->quit();
    return true;
}

bool Gtk_CustomWindow::onWindowStateChange(GdkEventWindowState* window_state_event){
    switch (window_state_event->changed_mask) {
    case GDK_WINDOW_STATE_WITHDRAWN: break;
    case GDK_WINDOW_STATE_ICONIFIED:
        return this->onMinimizeButtonClicked(window_state_event);
        break;
    case GDK_WINDOW_STATE_MAXIMIZED:
        if (!isMaximized())
            return this->onMaximizeButtonClicked(window_state_event);
        else
            return this->onDesMaximizeButtonClicked(window_state_event);
        break;
    case GDK_WINDOW_STATE_STICKY:
        return cout << "\nSticky";
        break;
    case GDK_WINDOW_STATE_FULLSCREEN:
        return this->onFullScreen(window_state_event);
        break;
    case GDK_WINDOW_STATE_ABOVE:
        cout << "\nAbove Something";
        break;
    case GDK_WINDOW_STATE_BELOW:
        cout << "\nBelow Something";
        break;
    case GDK_WINDOW_STATE_FOCUSED:
        cout << "\nFocused";
        break;
    case GDK_WINDOW_STATE_TILED:
        cout << "\nTiled";
        break;
    default:
        cout << "\n:(";
        break;
    }
    return true;
}

bool Gtk_CustomWindow::onMaximizeButtonClicked(GdkEventWindowState*){
    maximized = true;
    cout << "\nMaximized";
    return true;
}

bool Gtk_CustomWindow::onDesMaximizeButtonClicked(GdkEventWindowState*){
    maximized = false;
    cout << "\nDesMaximized";
    return true;
}

bool Gtk_CustomWindow::onMinimizeButtonClicked(GdkEventWindowState*){
    cout << "\nMinimized";
    return true;
}

bool Gtk_CustomWindow::onFocus(GdkEventFocus *){
    cout << "\nOnFocus";
    return true;
}

bool Gtk_CustomWindow::onFullScreen(GdkEventWindowState *){
    cout << "\nonFullScreen";
    return true;
}

bool Gtk_CustomWindow::onLostFocus(GdkEventFocus *){
    cout << "\nOnLostFocus";
    return true;
}

void Gtk_CustomWindow:: setPosition(point_2D<int> p){
    this->move(p.x, p.y);
}



#endif
