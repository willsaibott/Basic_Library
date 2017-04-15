#ifndef WILLY_GTKMM_IMPLEMENTATION_H
#define WILLY_GTKMM_IMPLEMENTATION_H

#include "../Library/GUI/gtk+/Gtk_CustomWindow.h"
#include "../Library/GUI/gtk+/Gtk_Application.h"
#include "../Library/GUI/gtk+/Gtk_CustomButton.h"
#include "../Library/GUI/gtk+/Gtk_CustomCheckButton.h"
#include "../Library/GUI/gtk+/Gtk_CustomRadioButton.h"
#include "../Library/GUI/gtk+/Gtk_CustomRadioGroup.h"

namespace CustomGtkmm {
    typedef Gtk_CustomButton Button;
    typedef Gtk_CustomCheckButton CheckButton;
    typedef Gtk_Application Application;
    typedef Gtk_CustomRadioButton RadioButton;
    typedef Gtk_CustomRadioGroup RadioGroup;
    typedef Gtk_CustomWindow Window;
}
#endif // WILLY_GTKMM_IMPLEMENTATION_H
