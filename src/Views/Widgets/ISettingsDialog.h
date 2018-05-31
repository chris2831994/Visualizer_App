//
// Created by chris on 5/31/18.
//

#ifndef GTKMM_MVC_TEST_ISETTINGSDIALOG_H
#define GTKMM_MVC_TEST_ISETTINGSDIALOG_H

class ISettingsDialog : public Gtk::Window {
public:

protected:
    virtual void on_button_save() = 0;
    virtual void on_button_cancel() = 0;
};

#endif //GTKMM_MVC_TEST_ISETTINGSDIALOG_H
