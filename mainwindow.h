#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QListWidget>
#include <QUrl>
#include <QMessageBox>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_addFiles_clicked();

    void on_spinBoxFront_valueChanged(int arg1);

    void on_spinBoxBack_valueChanged(int arg1);

    void on_rename_clicked();

    void on_insertText_textChanged(const QString &arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_spinBoxCounterBegin_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    QString filepath;
    QStringList filenames;
    QStringList filenamesRenamed;
    QString insertText = "";

    int enumerate = 0;

    int counterBegin = 0;
    int nFrontChars = 0;
    int nBackChars = 0;

    void updateRenameList(bool renameFilesNow);
};
#endif // MAINWINDOW_H
