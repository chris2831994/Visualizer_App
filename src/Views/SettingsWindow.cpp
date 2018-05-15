//
// Created by chris on 5/15/18.
//

#include "SettingsWindow.h"
#include "../Services/IConfigService.h"

SettingsWindow::SettingsWindow(std::shared_ptr<IConfigService> configService)
    : configService(configService),
      m_VBox(Gtk::ORIENTATION_VERTICAL),
      m_Button_Cancel("Cancel"),
      m_Button_Save("Save"),
      m_Frame_FileName("Fifo Filename"),
      m_Frame_DefaultVisualizer("Default Visualizer"),
      m_Frame_SampleSize("Sample Size")
{
    set_size_request(200, 400);
    set_title("Settings");
    set_border_width(5);

    add(m_VBox);

    m_Entry_FileName.set_max_length(100);
    m_Entry_FileName.set_text(configService->getConfig().getFileName());

    m_Frame_FileName.add(m_Entry_FileName);

    m_VBox.pack_start(m_Frame_FileName);

    m_VBox.pack_start(m_Frame_SampleSize);

    m_VBox.pack_start(m_Frame_DefaultVisualizer);

    m_Button_Cancel.signal_clicked().connect(sigc::mem_fun(*this, &SettingsWindow::on_button_cancel));
    m_Button_Save.signal_clicked().connect(sigc::mem_fun(*this, &SettingsWindow::on_button_save));

    m_ButtonBox.add(m_Button_Cancel);
    m_ButtonBox.add(m_Button_Save);

    m_VBox.pack_start(m_ButtonBox);

    show_all_children();
}

SettingsWindow::~SettingsWindow() {

}

void SettingsWindow::on_button_cancel() {

}

void SettingsWindow::on_button_save() {

}