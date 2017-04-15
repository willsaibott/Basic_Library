#include "Gtk_CustomButton.h"



Gtk_CustomButton::Gtk_CustomButton(buttonSize size) : Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL), hBox(Gtk::Orientation::ORIENTATION_HORIZONTAL){
    this->setDefaultEvents();
    this->setSize(size);
    hBox.pack_start(button, Gtk::PackOptions::PACK_SHRINK, 0);
    this->pack_start(hBox, Gtk::PackOptions::PACK_SHRINK, 0 );
}

Gtk_CustomButton::Gtk_CustomButton(buttonSize size, string label)  : Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL) , hBox(Gtk::Orientation::ORIENTATION_HORIZONTAL){
    this->setDefaultEvents();
    this->setSize(size);
    this->setLabel(label);
    hBox.pack_start(button, Gtk::PackOptions::PACK_SHRINK, 0);
    this->pack_start(hBox, Gtk::PackOptions::PACK_SHRINK, 0 );
}

Gtk_CustomButton::Gtk_CustomButton(buttonSize size, string imageName, string label)  : Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL) , hBox(Gtk::Orientation::ORIENTATION_HORIZONTAL){
    this->setDefaultEvents();
    this->setSize(size);
    this->setLabel(imageName, label);
    hBox.pack_start(button, Gtk::PackOptions::PACK_SHRINK, 0);
    this->pack_start(hBox, Gtk::PackOptions::PACK_SHRINK, 0 );
}

Gtk_CustomButton::~Gtk_CustomButton(){

}


//setters
void Gtk_CustomButton::setDefaultEvents(){
    button.signal_clicked().connect(sigc::mem_fun(this, &Gtk_CustomButton::onClicked));
    this->signal_focus_in_event().connect(sigc::mem_fun(this, &Gtk_CustomButton::onFocus));
    button.signal_pressed().connect(sigc::mem_fun(this, &Gtk_CustomButton::onPressed));
    button.signal_enter_notify_event().connect(sigc::mem_fun(this, &Gtk_CustomButton::onEnter));
    button.signal_leave_notify_event().connect(sigc::mem_fun(this, &Gtk_CustomButton::onLeave));
    button.signal_released().connect(sigc::mem_fun(this, &Gtk_CustomButton::onReleased));
}

void Gtk_CustomButton::setLabel(string label){
    button.add_label(label);

}

void Gtk_CustomButton::setLabel(string imageName, string label){
    button.add_pixlabel(imageName, label);
}

void Gtk_CustomButton::setSize(buttonSize size){
    this->size = size;
    button.set_size_request(size.width, size.height);
}



void Gtk_CustomButton::setOnPressedListener(void (&f)()){
    button.signal_pressed().connect(sigc::ptr_fun(f));
}

void Gtk_CustomButton::setOnClickedListener(void (&f)()){
    button.signal_clicked().connect(sigc::ptr_fun(f));
}

void Gtk_CustomButton::setOnReleasedListener(void (&f)()){
    button.signal_released().connect(sigc::ptr_fun(f));
}

void Gtk_CustomButton::setOnEnterListener(bool (&f)(GdkEventCrossing *)){
    button.signal_enter_notify_event().connect(sigc::ptr_fun(f));
}

void Gtk_CustomButton::setOnLeaveListener(bool (&f)(GdkEventCrossing *)){
    button.signal_leave_notify_event().connect(sigc::ptr_fun(f));
}

void Gtk_CustomButton::setOnFocusListener(bool (&f)(GdkEventFocus *)){
    this->signal_focus_in_event().connect(sigc::ptr_fun(f));
}

//events
void Gtk_CustomButton::onPressed(){
    cout << "\nButton was pressed";
}

void Gtk_CustomButton::onClicked(){
    cout << "\nButton was clicked";
}

void Gtk_CustomButton::onReleased(){
    cout << "\nButton was released";
}

bool Gtk_CustomButton::onEnter(GdkEventCrossing *){
    cout << "\nPointer entered the Button Area";
    return true;
}

bool Gtk_CustomButton::onLeave(GdkEventCrossing *){
    cout << "\nPointer left the Button Area";
    return true;
}

bool Gtk_CustomButton::onFocus(GdkEventFocus *){
    cout << "\nBox Focused";
    return true;
}

//others
void Gtk_CustomButton::setPosition(margin<int> m){
    if (m.bottom!=MARGIN_OFF)
        this->set_margin_bottom(m.bottom);
    if (m.right!=MARGIN_OFF)
        this->set_margin_right(m.right);
    if (m.left!=MARGIN_OFF)
        this->set_margin_left(m.left);
    if (m.left!=MARGIN_OFF)
        this->set_margin_top(m.top);

}

