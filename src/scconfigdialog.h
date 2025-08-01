#ifndef SCCONFIGDIALOG_H
#define SCCONFIGDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class SCConfigDialog;
}

class SCConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SCConfigDialog(QWidget *parent = nullptr);
    ~SCConfigDialog();

    void FillInCurrentValues(void);

signals:
    void processModeChanged(void);

private slots:
    void ExtractSettings(void);
    void SetDarkLevelThreshold(int);
    void SetNumSCToAvg(int);
    void SetBlurWidth(int);
    void on_calculate_tform_pushButton_clicked(void);
    void on_saveVideoTform_pushButton_clicked(void);
    void on_loadVideoTform_pushButton_clicked(void);
    void SetVideoFileFormat(int);
    void SetMovingAvgWidth(int);
    void on_videoDevice_comboBox_activated(int idx);

private:
    Ui::SCConfigDialog *ui;
    QStringList getVideoDevices(void);
};

#endif // SCCONFIGDIALOG_H
