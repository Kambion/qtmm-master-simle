/*
 *  Main application window for AFSK1200 demodulator
 */
#pragma once

#include <QMainWindow>
#include <QComboBox>
#include <QLabel>
#include <QAudioInput>
#include <QList>
#include "audiobuffer.h"
#include "ssi.h"
#include "multimon/cafsk12.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QComboBox *comSelector;

private slots:
    void samplesReceived(float *buffer, const int length);
    void audioStateChanged(QAudio::State state);
    void inputSelectionChanged(int index);
    void on_actionDecode_toggled(bool enabled);
    void on_actionClear_triggered();
    void on_actionSave_triggered();
    void on_actionAbout_triggered();
    void on_actionAboutQt_triggered();

    void on_comOpen_clicked();

    void on_filterCSBox_toggled(bool checked);

    void on_pushButton_clicked();

    void on_setFilterButton_clicked();

private:
    Ui::MainWindow *ui;
    QLabel     *inputLabel;
    QComboBox  *inputSelector;  // Audio input delector
    QWidget    *ssiSpacer;      // Spacer used to right align ssi
    CSsi       *ssi;            // Input level indicator

    QList<QAudioDeviceInfo> inputDevices;   // List of available audio input devices
    QAudioInput  *audioInput;               // Audio input object
    QAudioFormat  audioFormat;              // Audio format info
    CAudioBuffer *audioBuffer;              // Audio buffer

    CAfsk12      *afsk12;

    QVarLengthArray<float, 8192> tmpbuf;   // Needed to remember "overlap" smples

    void createDeviceSelector();
    void initialiseAudio();

    void process(QByteArray buff);

};
