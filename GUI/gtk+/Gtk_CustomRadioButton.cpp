#include "Gtk_CustomRadioButton.h"

Gtk_CustomRadioButton::Gtk_CustomRadioButton(buttonSize size) : Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL), hBox(Gtk::Orientation::ORIENTATION_HORIZONTAL){
    this->setDefaultEvents();
    this->setSize(size);
    hBox.pack_start(button, Gtk::PackOptions::PACK_SHRINK, 0);
    this->pack_start(hBox, Gtk::PackOptions::PACK_SHRINK, 0 );
}

Gtk_CustomRadioButton::Gtk_CustomRadioButton(buttonSize size, string label)  : Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL) , hBox(Gtk::Orientation::ORIENTATION_HORIZONTAL){
    this->setDefaultEvents();
    this->setSize(size);
    this->setLabel(label);
    hBox.pack_start(button, Gtk::PackOptions::PACK_SHRINK, 0);
    this->pack_start(hBox, Gtk::PackOptions::PACK_SHRINK, 0 );
}


Gtk_CustomRadioButton::Gtk_CustomRadioButton(buttonSize size, string imageName, string label)  : Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL) , hBox(Gtk::Orientation::ORIENTATION_HORIZONTAL){
    this->setDefaultEvents();
    this->setSize(size);
    this->setLabel(imageName, label);
    hBox.pack_start(button, Gtk::PackOptions::PACK_SHRINK, 0);
    this->pack_start(hBox, Gtk::PackOptions::PACK_SHRINK, 0 );
}


Gtk_CustomRadioButton::~Gtk_CustomRadioButton(){
}


//setters
void Gtk_CustomRadioButton::setDefaultEvents(){
    button.signal_clicked().connect(sigc::mem_fun(this, &Gtk_CustomRadioButton::onClicked));
    this->signal_focus_in_event().connect(sigc::mem_fun(this, &Gtk_CustomRadioButton::onFocus));
    button.signal_pressed().connect(sigc::mem_fun(this, &Gtk_CustomRadioButton::onPressed));
    button.signal_enter_notify_event().connect(sigc::mem_fun(this, &Gtk_CustomRadioButton::onEnter));
    button.signal_leave_notify_event().connect(sigc::mem_fun(this, &Gtk_CustomRadioButton::onLeave));
    button.signal_released().connect(sigc::mem_fun(this, &Gtk_CustomRadioButton::onReleased));
}

void Gtk_CustomRadioButton::setLabel(string label){
    button.add_label(label);

}

void Gtk_CustomRadioButton::setLabel(string imageName, string label){
    button.add_pixlabel(imageName, label);
}

void Gtk_CustomRadioButton::setSize(buttonSize size){
    this->size = size;
    button.set_size_request(size.width, size.height);
}


void Gtk_CustomRadioButton::setOnPressedListener(void (&f)()){
    button.signal_pressed().connect(sigc::ptr_fun(f));
}

void Gtk_CustomRadioButton::setOnClickedListener(void (&f)()){
    button.signal_clicked().connect(sigc::ptr_fun(f));
}

void Gtk_CustomRadioButton::setOnReleasedListener(void (&f)()){
    button.signal_released().connect(sigc::ptr_fun(f));
}

void Gtk_CustomRadioButton::setOnEnterListener(bool (&f)(GdkEventCrossing *)){
    button.signal_enter_notify_event().connect(sigc::ptr_fun(f));
}

void Gtk_CustomRadioButton::setOnLeaveListener(bool (&f)(GdkEventCrossing *)){
    button.signal_leave_notify_event().connect(sigc::ptr_fun(f));
}

void Gtk_CustomRadioButton::setOnFocusListener(bool (&f)(GdkEventFocus *)){
    this->signal_focus_in_event().connect(sigc::ptr_fun(f));
}
//events
void Gtk_CustomRadioButton::onPressed(){
    cout << "\nButton was pressed";
}

void Gtk_CustomRadioButton::onClicked(){
    cout << "\nButton was clicked";
}

void Gtk_CustomRadioButton::onReleased(){
    cout << "\nButton was released";
}

bool Gtk_CustomRadioButton::onEnter(GdkEventCrossing *){
    cout << "\nPointer entered the Button Area";
    return true;
}

bool Gtk_CustomRadioButton::onLeave(GdkEventCrossing *){
    cout << "\nPointer left the Button Area";
    return true;
}

bool Gtk_CustomRadioButton::onFocus(GdkEventFocus *){
    cout << "\nBox Focused";
    return true;
}


//others
void Gtk_CustomRadioButton::setPosition(margin<int> m){
    if (m.bottom!=MARGIN_OFF)
        this->set_margin_bottom(m.bottom);
    if (m.right!=MARGIN_OFF)
        this->set_margin_right(m.right);
    if (m.left!=MARGIN_OFF)
        this->set_margin_left(m.left);
    if (m.left!=MARGIN_OFF)
        this->set_margin_top(m.top);

}

