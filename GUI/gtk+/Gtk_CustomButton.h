#ifndef GTK_CUSTOMBUTTON_H
#define GTK_CUSTOMBUTTON_H


#include <gtkmm/button.h>
#include <gtkmm/box.h>

#include "../../../Library/Structures/Basic.h"

#include "Gtk_CustomWindow.h"
#include "Gtk_Basic.h"

class Gtk_CustomButton : public Gtk::Box
{
protected:
    string label;
    buttonSize size;
    Gtk::Box hBox;
    Gtk::Button button;

public:
    Gtk_CustomButton(buttonSize size);
    Gtk_CustomButton(buttonSize size, string label);
    Gtk_CustomButton(buttonSize size, string imageName, string label);
    virtual ~Gtk_CustomButton();

    //getters
    string getLabel(){return label;}
    buttonSize getSize(){return size;}

    //setters
    void setDefaultEvents();
    void setLabel(string label);
    void setLabel(string imageName, string label);
    void setSize(buttonSize size);
    void setOnPressedListener(void (&f)());
    void setOnClickedListener(void (&f)());
    void setOnReleasedListener(void (&f)());
    void setOnEnterListener(bool (&f)(GdkEventCrossing *));
    void setOnLeaveListener(bool (&f)(GdkEventCrossing *));
    void setOnFocusListener(bool (&f)(GdkEventFocus *));

    //events
    virtual void onPressed();
    virtual void onClicked();
    virtual void onReleased();
    virtual bool onEnter(GdkEventCrossing *);
    virtual bool onLeave(GdkEventCrossing *);
    virtual bool onFocus(GdkEventFocus *);

    //others
    void setPosition(margin<int>);

};

#endif // GTK_CUSTOMBUTTON_H
