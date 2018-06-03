//
// Created by chris on 5/10/18.
//

#include "VisualizerWindow.h"

VisualizerWindow::VisualizerWindow(std::shared_ptr<IVisualizer> m_visualizer, std::shared_ptr<ISettingsDialog> m_settings)
        : m_visualizer(m_visualizer),
          m_settings(m_settings),
          m_Button_Settings("Settings"),
          m_VBox(Gtk::ORIENTATION_VERTICAL),
          m_ButtonBox(Gtk::ORIENTATION_HORIZONTAL)
{
    set_size_request(400, 400);
    set_title("Visualizer App");
    add(m_VBox);
    m_VBox.pack_start(*m_visualizer, Gtk::PACK_EXPAND_WIDGET);
    m_Button_Settings.signal_clicked().connect(sigc::mem_fun(*this, &VisualizerWindow::on_button_settings));
    m_ButtonBox.add(m_Button_Settings);
    m_VBox.pack_start((m_ButtonBox), Gtk::PACK_SHRINK);
    show_all_children();
}

VisualizerWindow::~VisualizerWindow(){

}

void VisualizerWindow::on_button_settings() {
    m_settings->show();
}

//void VisualizerWindow::setSettingsWindow(SettingsWindow window){
//
//}