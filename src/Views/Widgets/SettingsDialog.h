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
#include "../../Services/IFifoReaderService.h"
#include "../../Services/IFifoProcessorService.h"

class SettingsDialog : public ISettingsDialog {
public:
    SettingsDialog(std::shared_ptr<IConfigService> configService,
                   std::shared_ptr<IFifoReaderService> readerService,
                   std::shared_ptr<IFifoProcessorService> processorService);
    ~SettingsDialog();

protected:
    //signal handlers
    void on_button_cancel();
    void on_button_save();

    //services
    std::shared_ptr<IConfigService> configService;
    std::shared_ptr<IFifoReaderService> readerService;
    std::shared_ptr<IFifoProcessorService> processorService;

    //combo box models
    IntegerColumn sampleRateColumns;
    IntegerColumn fpsCountColumns;

    //child widgets
    Gtk::Box m_VBox;
    Gtk::Frame m_Frame_FileName, m_Frame_SampleRate, m_Frame_FpsCount;
    //Gtk::Label m_Label_FileName, m_Label_SampleSize, m_Label_DefaultVisualizer;
    Gtk::Entry m_Entry_FileName;
    Gtk::ComboBox m_ComboBox_SampleRate, m_ComboBox_FpsCount;
    Gtk::ButtonBox m_ButtonBox;
    Gtk::Button m_Button_Cancel;
    Gtk::Button m_Button_Save;

    Glib::RefPtr<Gtk::ListStore> m_refTreeModelSampleRate;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModelFpsCount;
};

#endif //GTKMM_MVC_TEST_SETTINGSDIALOG_H
