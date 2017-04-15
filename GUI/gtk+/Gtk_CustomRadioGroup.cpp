#include "Gtk_CustomRadioGroup.h"


Gtk_CustomRadioGroup::Gtk_CustomRadioGroup(std::string title, const uint totalRadioButtons, Gtk::Orientation orientation) : Gtk::Box((orientation==H)?V: H), titleView(title), hBox(orientation), n(totalRadioButtons)
{
    radioButtons = new Gtk::RadioButton*[n];
    hBox.pack_start(titleView, Gtk::PackOptions::PACK_SHRINK, 0);
    for(uint i = 0; i < n; i++){
        radioButtons[i] = new Gtk::RadioButton;
        if (i==0)
            group = radioButtons[0]->get_group();
        else
            radioButtons[i]->set_group(group);
        hBox.pack_start(*radioButtons[i], Gtk::PackOptions::PACK_SHRINK, 0);
    }

    this->setTitle(title);
    this->pack_start(hBox, Gtk::PackOptions::PACK_SHRINK, 0);
}

Gtk_CustomRadioGroup::~Gtk_CustomRadioGroup(){
    for (uint i = 0; i < n; i++)
        delete radioButtons[i];
    delete []radioButtons;
}

void Gtk_CustomRadioGroup::setTitle(std::string title){
    this->title = title;
    titleView.set_label(title);
}

void Gtk_CustomRadioGroup::setPosition(margin<int> m){
    if (m.bottom!=MARGIN_OFF)
        this->set_margin_bottom(m.bottom);
    if (m.right!=MARGIN_OFF)
        this->set_margin_right(m.right);
    if (m.left!=MARGIN_OFF)
        this->set_margin_left(m.left);
    if (m.left!=MARGIN_OFF)
        this->set_margin_top(m.top);
}

void Gtk_CustomRadioGroup::setLabels(string *labels){
    for(uint i = 0; i < n; i++)
        this->setLabel(labels[i], i);
}

void Gtk_CustomRadioGroup::setLabel(std::string label, uint radioButton){
    radioButtons[radioButton]->add_label(label);
}


void Gtk_CustomRadioGroup::setOnPressedListener(void (&f)(), uint radioButton){
    radioButtons[radioButton]->signal_pressed().connect(sigc::ptr_fun(f));
}

void Gtk_CustomRadioGroup::setOnClickedListener(void (&f)(), uint radioButton){
   radioButtons[radioButton]->signal_clicked().connect(sigc::ptr_fun(f));
}

void Gtk_CustomRadioGroup::setOnReleasedListener(void (&f)(), uint radioButton){
    radioButtons[radioButton]->signal_released().connect(sigc::ptr_fun(f));
}

void Gtk_CustomRadioGroup::setOnEnterListener(bool (&f)(GdkEventCrossing *), uint radioButton){
    radioButtons[radioButton]->signal_enter_notify_event().connect(sigc::ptr_fun(f));
}

void Gtk_CustomRadioGroup::setOnLeaveListener(bool (&f)(GdkEventCrossing *), uint radioButton){
    radioButtons[radioButton]->signal_leave_notify_event().connect(sigc::ptr_fun(f));
}

void Gtk_CustomRadioGroup::setOnFocusListener(bool (&f)(GdkEventFocus *), uint radioButton){
    radioButtons[radioButton]->signal_focus_in_event().connect(sigc::ptr_fun(f));
}

void Gtk_CustomRadioGroup::setImageLabel(std::string imageName, std::string label, uint radioButton){
    radioButtons[radioButton]->add_pixlabel(imageName, label);
}

void Gtk_CustomRadioGroup::setSelectionedButton(uint index){
    radioButtons[index]->set_active(true);
}

void Gtk_CustomRadioGroup::setTitleVisible(bool visible){
    titleView.set_visible(visible);
}

void Gtk_CustomRadioGroup::setRadioButtonVisible(bool visible, uint radioButton){
    radioButtons[radioButton]->set_visible(visible);
}

uint Gtk_CustomRadioGroup::getSelectionedButton(){
    for(uint i = 0; i < n; i++)
        if (radioButtons[i]->get_active())
            return i;
}
