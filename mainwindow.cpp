#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addFiles_clicked()
{
    ui->listWidget->clear();
    ui->listWidgetRename->clear();

    // Absolute file paths
    filenames = QFileDialog::getOpenFileNames(this, "Open files");

    // Save path to folder
    QUrl url(filenames[0]);
    filepath = url.adjusted(QUrl::RemoveFilename).toString();

    // Add filenames to UI list
    for (QString filename : filenames) {
        QUrl url(filename);
        new QListWidgetItem(url.fileName(), ui->listWidget);
    }
}

void MainWindow::on_spinBoxFront_valueChanged(int arg1)
{
    nFrontChars = arg1;
    updateRenameList(false);
}

void MainWindow::on_spinBoxBack_valueChanged(int arg1)
{
    nBackChars = arg1;
    updateRenameList(false);
}



void MainWindow::on_rename_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Are you sure you want to rename the files?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Yes:
        // Yes was clicked
        updateRenameList(true);
        break;
    case QMessageBox::Cancel:
        // Cancel was clicked
        return;
    default:
        // should never be reached
        return;
    }


}

void MainWindow::on_insertText_textChanged(const QString &arg1)
{
    insertText = arg1;
    updateRenameList(false);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    enumerate = arg1;
    updateRenameList(false);
}

void MainWindow::on_spinBoxCounterBegin_valueChanged(int arg1)
{
    counterBegin = arg1;
    updateRenameList(false);
}

void MainWindow::updateRenameList(bool renameFilesNow)
{
    ui->listWidgetRename->clear();

    // Starting number for filename enumeration
    int counter = counterBegin;
    QString number = "";

    // Number of digits in filename, e.g. nDigits=4->0001, 0002, 0003
    int nDigits = QString(filenames.size()).size()+1;

    // Change each filename
    for (QString filename : filenames) {

        // Filename without folder path
        QUrl url(filename);
        QString newFilename = url.fileName();

        // Save the filetype for re-insertion later
        QString filetype = newFilename.split(".").takeLast();

        // ".chop" filetype and n characters from the back and ".remove" n from the front
        newFilename.chop(filetype.size()+1 + nBackChars);
        newFilename.remove(0, nFrontChars);

        // Enumerate if box is checked
        if (enumerate) {
            number = QString("%1").arg(counter, nDigits, 10, QChar('0'));
            counter++;
        }

        // Merge string components to new filename
        newFilename = insertText+number+newFilename+"."+filetype;

        // Add filename to the UI new filename list
        new QListWidgetItem(newFilename, ui->listWidgetRename);

        // If rename-button was clicked, rename actual file
        if (renameFilesNow)
            QFile::rename(filename, filepath+newFilename);


    }
}
