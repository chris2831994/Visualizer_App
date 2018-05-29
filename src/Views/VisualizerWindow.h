//
// Created by chris on 5/10/18.
//

#ifndef GTKMM_MVC_TEST_VISUALIZERWINDOW_H
#define GTKMM_MVC_TEST_VISUALIZERWINDOW_H

#include <gtkmm.h>
#include "Widgets/IVisualizer.h"
#include "SettingsWindow.h"

class VisualizerWindow : public Gtk::Window
{

public:
    VisualizerWindow(std::shared_ptr<IVisualizer> visualizer);
    virtual ~VisualizerWindow();
    //void setSettingsWindow(SettingsWindow window);

protected:
    //signal handlers:
    void on_button_quit();
    void on_button_settings();

    //child widgets:
    Gtk::Box m_VBox;
    std::shared_ptr<IVisualizer> m_visualizer;
    Gtk::ButtonBox m_ButtonBox;
    Gtk::Button m_Button_Quit;
    Gtk::Button m_Button_Settings;


};

#endif //GTKMM_MVC_TEST_VISUALIZERWINDOW_H
