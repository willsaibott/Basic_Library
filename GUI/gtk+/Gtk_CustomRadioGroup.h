#ifndef GTK_CUSTOMRADIOGROUP_H
#define GTK_CUSTOMRADIOGROUP_H

#include <gtkmm/box.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/label.h>

#include "../Library/GUI/gtk+/Gtk_CustomRadioButton.h"

#define SELECTIONED_BUTTON_NONE 0
#define V Gtk::ORIENTATION_VERTICAL
#define H Gtk::ORIENTATION_HORIZONTAL

class Gtk_CustomRadioGroup : public Gtk::Box
{
    string title;
    Gtk::Label titleView;
    Gtk::Box hBox;
    Gtk::RadioButton::Group group;
    Gtk::RadioButton **radioButtons;
    const uint n;

public:
    Gtk_CustomRadioGroup(string title, const uint totalRadioButtons, Gtk::Orientation orientation);
    virtual ~Gtk_CustomRadioGroup();

    //getters
    string getTitle(){return title;}
    uint getNumberOfButtons(){return n;}
    uint getSelectionedButton();


    //setters
    void setTitle(string title);
    void setSelectionedButton(uint index);
    void setPosition(margin<int>);
    void setLabels(string *labels);
    void setLabel(string label, uint radioButton);
    void setImageLabel(string imageName, string label, uint radioButton);
    void setOnPressedListener(void (&f)(), uint radioButton);
    void setOnClickedListener(void (&f)(), uint radioButton);
    void setOnReleasedListener(void (&f)(), uint radioButton);
    void setOnEnterListener(bool (&f)(GdkEventCrossing *), uint radioButton);
    void setOnLeaveListener(bool (&f)(GdkEventCrossing *), uint radioButton);
    void setOnFocusListener(bool (&f)(GdkEventFocus *), uint radioButton);
    void setTitleVisible(bool visible);
    void setRadioButtonVisible(bool visible, uint radioButton);


    //others
};

#endif // GTK_CUSTOMRADIOGROUP_H
