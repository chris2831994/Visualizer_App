//
// Created by chris on 5/10/18.
//

#include "VisualizerWindow.h"

VisualizerWindow::VisualizerWindow(std::shared_ptr<IVisualizer> visualizer)
        : m_visualizer(visualizer),
          m_Button_Quit("Quit"),
          m_Button_Settings("Settings"),
          m_VBox(Gtk::ORIENTATION_VERTICAL)
{

    set_title("Visualizer App");
    add(m_VBox);
    m_VBox.pack_start(*m_visualizer);
    m_ButtonBox.add(m_Button_Settings);
    m_ButtonBox.add(m_Button_Quit);
    m_VBox.pack_start((m_ButtonBox));
    show_all_children();
}

VisualizerWindow::~VisualizerWindow(){

}

void VisualizerWindow::on_button_quit() {
    hide();
}

void VisualizerWindow::on_button_settings() {

}

//void VisualizerWindow::setSettingsWindow(SettingsWindow window){
//
//}