//
// Created by chris on 5/15/18.
//

#ifndef GTKMM_MVC_TEST_SETTINGSWINDOW_H
#define GTKMM_MVC_TEST_SETTINGSWINDOW_H

#include <gtkmm.h>
#include "../Services/IConfigService.h"

class SettingsWindow : public Gtk::Window{
public:
    SettingsWindow(std::shared_ptr<IConfigService> configService);
    ~SettingsWindow();
protected:
    //signal handlers
    void on_button_cancel();
    void on_button_save();

    //child widgets
    Gtk::Box m_VBox;
    Gtk::Frame m_Frame_FileName, m_Frame_SampleSize, m_Frame_DefaultVisualizer;
    //Gtk::Label m_Label_FileName, m_Label_SampleSize, m_Label_DefaultVisualizer;
    Gtk::Entry m_Entry_FileName;
    Gtk::ComboBox m_ComboBox_SampleSize, m_ComboBox_DefaultVisualizer;
    Gtk::ButtonBox m_ButtonBox;
    Gtk::Button m_Button_Cancel;
    Gtk::Button m_Button_Save;

    //service handles
    std::shared_ptr<IConfigService> configService;
};
#endif //GTKMM_MVC_TEST_SETTINGSWINDOW_H
