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
          m_Frame_FpsCount("Visualization Frames per Second"),
          m_Frame_SampleRate("Sample Rate of Audio"),
          m_VBox(Gtk::ORIENTATION_VERTICAL)
{
    auto config = configService->getConfig();

    set_size_request(200, 400);
    set_title("Settings");
    set_border_width(5);

    add(m_VBox);

    m_Entry_FileName.set_max_length(100);
    m_Entry_FileName.set_text(configService->getConfig()->getFileName());

    m_refTreeModelSampleRate = Gtk::ListStore::create(sampleRateColumns);
    m_ComboBox_SampleRate.set_model(m_refTreeModelSampleRate);

    m_refTreeModelFpsCount = Gtk::ListStore::create(fpsCountColumns);
    m_ComboBox_FpsCount.set_model(m_refTreeModelFpsCount);

    //fill sample size combo box
    Gtk::TreeModel::Row sampleRow_2 = *(m_refTreeModelSampleRate->append());
    sampleRow_2[sampleRateColumns.m_col_val] = 44100;
    sampleRow_2[sampleRateColumns.m_col_desc] = "44100";
    if(config->getSampleRate() == 44100) m_ComboBox_SampleRate.set_active(sampleRow_2);

    Gtk::TreeModel::Row sampleRow_3 = *(m_refTreeModelSampleRate->append());
    sampleRow_3[sampleRateColumns.m_col_val] = 48000;
    sampleRow_3[sampleRateColumns.m_col_desc] = "48000";
    if(config->getSampleRate() == 48000) m_ComboBox_SampleRate.set_active(sampleRow_3);

    Gtk::TreeModel::Row sampleRow_4 = *(m_refTreeModelSampleRate->append());
    sampleRow_4[sampleRateColumns.m_col_val] = 192000;
    sampleRow_4[sampleRateColumns.m_col_desc] = "192000";
    if(config->getSampleRate() == 192000) m_ComboBox_SampleRate.set_active(sampleRow_4);

    m_ComboBox_SampleRate.pack_start(sampleRateColumns.m_col_desc);

    //fill default visualizer combo box
    Gtk::TreeModel::Row defVisRow_1 = *(m_refTreeModelFpsCount->append());
    defVisRow_1[fpsCountColumns.m_col_val] = 10;
    defVisRow_1[fpsCountColumns.m_col_desc] = "10";
    if(config->getFpsCount() == 10) m_ComboBox_FpsCount.set_active(defVisRow_1);

    Gtk::TreeModel::Row defVisRow_2 = *(m_refTreeModelFpsCount->append());
    defVisRow_2[fpsCountColumns.m_col_val] = 25;
    defVisRow_2[fpsCountColumns.m_col_desc] = "25";
    if(config->getFpsCount() == 25) m_ComboBox_FpsCount.set_active(defVisRow_2);

    Gtk::TreeModel::Row defVisRow_3 = *(m_refTreeModelFpsCount->append());
    defVisRow_3[fpsCountColumns.m_col_val] = 40;
    defVisRow_3[fpsCountColumns.m_col_desc] = "40";
    if(config->getFpsCount() == 40) m_ComboBox_FpsCount.set_active(defVisRow_3);

    m_ComboBox_FpsCount.pack_start(fpsCountColumns.m_col_desc);

    m_Frame_FileName.add(m_Entry_FileName);

    m_Frame_SampleRate.add(m_ComboBox_SampleRate);

    m_Frame_FpsCount.add(m_ComboBox_FpsCount);

    m_VBox.pack_start(m_Frame_FileName);

    m_VBox.pack_start(m_Frame_SampleRate);

    m_VBox.pack_start(m_Frame_FpsCount);

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
    Gtk::TreeModel::iterator iter = m_ComboBox_SampleRate.get_active();
    if(iter){
        Gtk::TreeModel::Row row = *iter;
        if(row){
            config->setSampleRate(row[sampleRateColumns.m_col_val]);
        }
    }
    iter = m_ComboBox_FpsCount.get_active();
    if(iter){
        Gtk::TreeModel::Row row = *iter;
        if(row){
            config->setFpsCount(row[fpsCountColumns.m_col_val]);
        }
    }
    configService->writeConfig();
    readerService->reInit();
    processorService->reInit();

    hide();
}

void SettingsDialog::on_button_cancel() {
    configService->writeConfig();
    hide();
}