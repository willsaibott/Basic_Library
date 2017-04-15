#include "Gtk_CustomCheckButton.h"


Gtk_CustomCheckButton::Gtk_CustomCheckButton(buttonSize size) : Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL), hBox(Gtk::Orientation::ORIENTATION_HORIZONTAL){
    this->setDefaultEvents();
    this->setSize(size);
    hBox.pack_start(button, Gtk::PackOptions::PACK_SHRINK, 0);
    this->pack_start(hBox, Gtk::PackOptions::PACK_SHRINK, 0 );
}

Gtk_CustomCheckButton::Gtk_CustomCheckButton(buttonSize size, string label)  : Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL) , hBox(Gtk::Orientation::ORIENTATION_HORIZONTAL){
    this->setDefaultEvents();
    this->setSize(size);
    this->setLabel(label);
    hBox.pack_start(button, Gtk::PackOptions::PACK_SHRINK, 0);
    this->pack_start(hBox, Gtk::PackOptions::PACK_SHRINK, 0 );
}


Gtk_CustomCheckButton::Gtk_CustomCheckButton(buttonSize size, string imageName, string label)  : Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL) , hBox(Gtk::Orientation::ORIENTATION_HORIZONTAL){
    this->setDefaultEvents();
    this->setSize(size);
    this->setLabel(imageName, label);
    hBox.pack_start(button, Gtk::PackOptions::PACK_SHRINK, 0);
    this->pack_start(hBox, Gtk::PackOptions::PACK_SHRINK, 0 );
}


Gtk_CustomCheckButton::~Gtk_CustomCheckButton(){

}


//setters
void Gtk_CustomCheckButton::setDefaultEvents(){
    button.signal_clicked().connect(sigc::mem_fun(this, &Gtk_CustomCheckButton::onClicked));
    this->signal_focus_in_event().connect(sigc::mem_fun(this, &Gtk_CustomCheckButton::onFocus));
    button.signal_pressed().connect(sigc::mem_fun(this, &Gtk_CustomCheckButton::onPressed));
    button.signal_enter_notify_event().connect(sigc::mem_fun(this, &Gtk_CustomCheckButton::onEnter));
    button.signal_leave_notify_event().connect(sigc::mem_fun(this, &Gtk_CustomCheckButton::onLeave));
    button.signal_released().connect(sigc::mem_fun(this, &Gtk_CustomCheckButton::onReleased));
}

void Gtk_CustomCheckButton::setLabel(string label){
    button.add_label(label);

}

void Gtk_CustomCheckButton::setLabel(string imageName, string label){
    button.add_pixlabel(imageName, label);
}

void Gtk_CustomCheckButton::setSize(buttonSize size){
    this->size = size;
    button.set_size_request(size.width, size.height);
}

void Gtk_CustomCheckButton::setOnPressedListener(void (&f)()){
    button.signal_pressed().connect(sigc::ptr_fun(f));
}

void Gtk_CustomCheckButton::setOnClickedListener(void (&f)()){
    button.signal_clicked().connect(sigc::ptr_fun(f));
}

void Gtk_CustomCheckButton::setOnReleasedListener(void (&f)()){
    button.signal_released().connect(sigc::ptr_fun(f));
}

void Gtk_CustomCheckButton::setOnEnterListener(bool (&f)(GdkEventCrossing *)){
    button.signal_enter_notify_event().connect(sigc::ptr_fun(f));
}

void Gtk_CustomCheckButton::setOnLeaveListener(bool (&f)(GdkEventCrossing *)){
    button.signal_leave_notify_event().connect(sigc::ptr_fun(f));
}

void Gtk_CustomCheckButton::setOnFocusListener(bool (&f)(GdkEventFocus *)){
    this->signal_focus_in_event().connect(sigc::ptr_fun(f));
}

//events
void Gtk_CustomCheckButton::onPressed(){
    cout << "\nButton was pressed";
}

void Gtk_CustomCheckButton::onClicked(){
    cout << "\nButton was clicked";
}

void Gtk_CustomCheckButton::onReleased(){
    cout << "\nButton was released";
}

bool Gtk_CustomCheckButton::onEnter(GdkEventCrossing *){
    cout << "\nPointer entered the Button Area";
    return true;
}

bool Gtk_CustomCheckButton::onLeave(GdkEventCrossing *){
    cout << "\nPointer left the Button Area";
    return true;
}

bool Gtk_CustomCheckButton::onFocus(GdkEventFocus *){
    cout << "\nBox Focused";
    return true;
}

//others
void Gtk_CustomCheckButton::setPosition(margin<int> m){
    if (m.bottom!=MARGIN_OFF)
        this->set_margin_bottom(m.bottom);
    if (m.right!=MARGIN_OFF)
        this->set_margin_right(m.right);
    if (m.left!=MARGIN_OFF)
        this->set_margin_left(m.left);
    if (m.left!=MARGIN_OFF)
        this->set_margin_top(m.top);

}

