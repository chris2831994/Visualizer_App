//
// Created by chris on 5/31/18.
//

#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(std::shared_ptr<IConfigService> configService,
                               std::shared_ptr<IFifoReaderService> readerService,
                               std::shared_ptr<IFifoProcessorService> processorService)
        : configService(configService),
          readerService(readerService),
          processorService(processorService),
          m_Button_Cancel("Cancel"),
          m_Button_Save("Save"),
          m_Frame_FileName("Fifo Filename"),
          m_Frame_DefaultVisualizer("Default Visualizer"),
          m_Frame_SampleSize("Sample Size"),
          m_VBox(Gtk::ORIENTATION_VERTICAL)
{
    auto config = configService->getConfig();

    set_size_request(200, 400);
    set_title("Settings");
    set_border_width(5);

    add(m_VBox);

    m_Entry_FileName.set_max_length(100);
    m_Entry_FileName.set_text(configService->getConfig()->getFileName());

    m_refTreeModelSampleSize = Gtk::ListStore::create(sampleSizeColumns);
    m_ComboBox_SampleSize.set_model(m_refTreeModelSampleSize);

    m_refTreeModelDefaultVisualizer = Gtk::ListStore::create(defaultVisualizerColumns);
    m_ComboBox_DefaultVisualizer.set_model(m_refTreeModelDefaultVisualizer);

    //fill sample size combo box
    Gtk::TreeModel::Row sampleRow_2 = *(m_refTreeModelSampleSize->append());
    sampleRow_2[sampleSizeColumns.m_col_val] = 1024;
    sampleRow_2[sampleSizeColumns.m_col_desc] = "1024";
    if(config->getSampleSize() == 1024) m_ComboBox_SampleSize.set_active(sampleRow_2);

    Gtk::TreeModel::Row sampleRow_3 = *(m_refTreeModelSampleSize->append());
    sampleRow_3[sampleSizeColumns.m_col_val] = 2048;
    sampleRow_3[sampleSizeColumns.m_col_desc] = "2048";
    if(config->getSampleSize() == 2048) m_ComboBox_SampleSize.set_active(sampleRow_3);

    Gtk::TreeModel::Row sampleRow_4 = *(m_refTreeModelSampleSize->append());
    sampleRow_4[sampleSizeColumns.m_col_val] = 4096;
    sampleRow_4[sampleSizeColumns.m_col_desc] = "4096";
    if(config->getSampleSize() == 4096) m_ComboBox_SampleSize.set_active(sampleRow_4);

    Gtk::TreeModel::Row sampleRow_5 = *(m_refTreeModelSampleSize->append());
    sampleRow_5[sampleSizeColumns.m_col_val] = 8192;
    sampleRow_5[sampleSizeColumns.m_col_desc] = "8192";
    if(config->getSampleSize() == 8192) m_ComboBox_SampleSize.set_active(sampleRow_5);

    Gtk::TreeModel::Row sampleRow_6 = *(m_refTreeModelSampleSize->append());
    sampleRow_6[sampleSizeColumns.m_col_val] = 16384;
    sampleRow_6[sampleSizeColumns.m_col_desc] = "16384";
    if(config->getSampleSize() == 16384) m_ComboBox_SampleSize.set_active(sampleRow_6);

    Gtk::TreeModel::Row sampleRow_7 = *(m_refTreeModelSampleSize->append());
    sampleRow_7[sampleSizeColumns.m_col_val] = 32768;
    sampleRow_7[sampleSizeColumns.m_col_desc] = "32768";
    if(config->getSampleSize() == 32768) m_ComboBox_SampleSize.set_active(sampleRow_7);

    m_ComboBox_SampleSize.pack_start(sampleSizeColumns.m_col_desc);

    //fill default visualizer combo box
    Gtk::TreeModel::Row defVisRow_1 = *(m_refTreeModelDefaultVisualizer->append());
    defVisRow_1[defaultVisualizerColumns.m_col_val] = 1;
    defVisRow_1[defaultVisualizerColumns.m_col_desc] = "Line Visualizer";
    if(config->getDefaultVisualizer() == 1) m_ComboBox_DefaultVisualizer.set_active(defVisRow_1);

    Gtk::TreeModel::Row defVisRow_2 = *(m_refTreeModelDefaultVisualizer->append());
    defVisRow_2[defaultVisualizerColumns.m_col_val] = 2;
    defVisRow_2[defaultVisualizerColumns.m_col_desc] = "Block Visualizer";
    if(config->getDefaultVisualizer() == 2) m_ComboBox_DefaultVisualizer.set_active(defVisRow_2);

    Gtk::TreeModel::Row defVisRow_3 = *(m_refTreeModelDefaultVisualizer->append());
    defVisRow_3[defaultVisualizerColumns.m_col_val] = 3;
    defVisRow_3[defaultVisualizerColumns.m_col_desc] = "Circle Visualizer";
    if(config->getDefaultVisualizer() == 3) m_ComboBox_DefaultVisualizer.set_active(defVisRow_3);

    m_ComboBox_DefaultVisualizer.pack_start(defaultVisualizerColumns.m_col_desc);

    m_Frame_FileName.add(m_Entry_FileName);

    m_Frame_SampleSize.add(m_ComboBox_SampleSize);

    m_Frame_DefaultVisualizer.add(m_ComboBox_DefaultVisualizer);

    m_VBox.pack_start(m_Frame_FileName);

    m_VBox.pack_start(m_Frame_SampleSize);

    m_VBox.pack_start(m_Frame_DefaultVisualizer);

    m_Button_Cancel.signal_clicked().connect(sigc::mem_fun(*this, &SettingsDialog::on_button_cancel));
    m_Button_Save.signal_clicked().connect(sigc::mem_fun(*this, &SettingsDialog::on_button_save));

    m_ButtonBox.add(m_Button_Cancel);
    m_ButtonBox.add(m_Button_Save);

    m_VBox.pack_start(m_ButtonBox);

    show_all_children();
}

SettingsDialog::~SettingsDialog(){

}

void SettingsDialog::on_button_save() {
    auto config = this->configService->getConfig();
    config->setFileName(m_Entry_FileName.get_text());
    Gtk::TreeModel::iterator iter = m_ComboBox_SampleSize.get_active();
    if(iter){
        Gtk::TreeModel::Row row = *iter;
        if(row){
            config->setSampleSize(row[sampleSizeColumns.m_col_val]);
        }
    }
    iter = m_ComboBox_DefaultVisualizer.get_active();
    if(iter){
        Gtk::TreeModel::Row row = *iter;
        if(row){
            config->setDefaultVisualizer(row[defaultVisualizerColumns.m_col_val]);
        }
    }
    readerService->reInit();
    processorService->reInit();
    configService->writeConfig();
    hide();
}

void SettingsDialog::on_button_cancel() {
    hide();
}