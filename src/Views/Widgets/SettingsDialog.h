//
// Created by chris on 5/31/18.
//

#ifndef GTKMM_MVC_TEST_SETTINGSDIALOG_H
#define GTKMM_MVC_TEST_SETTINGSDIALOG_H

#include <memory>
#include <gtkmm.h>
#include "ISettingsDialog.h"
#include "../../Services/IConfigService.h"
#include "ComboBoxModels/IntegerColumn.h"

class SettingsDialog : public ISettingsDialog {
public:
    SettingsDialog(std::shared_ptr<IConfigService> configService);
    ~SettingsDialog();

protected:
    //signal handlers
    void on_button_cancel();
    void on_button_save();

    //services
    std::shared_ptr<IConfigService> configService;

    //combo box models
    IntegerColumn sampleSizeColumns;
    IntegerColumn defaultVisualizerColumns;

    //child widgets
    Gtk::Box m_VBox;
    Gtk::Frame m_Frame_FileName, m_Frame_SampleSize, m_Frame_DefaultVisualizer;
    //Gtk::Label m_Label_FileName, m_Label_SampleSize, m_Label_DefaultVisualizer;
    Gtk::Entry m_Entry_FileName;
    Gtk::ComboBox m_ComboBox_SampleSize, m_ComboBox_DefaultVisualizer;
    Gtk::ButtonBox m_ButtonBox;
    Gtk::Button m_Button_Cancel;
    Gtk::Button m_Button_Save;

    Glib::RefPtr<Gtk::ListStore> m_refTreeModelSampleSize;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModelDefaultVisualizer;
};

#endif //GTKMM_MVC_TEST_SETTINGSDIALOG_H
