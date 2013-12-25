#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_search_clicked();
    
private:
    Ui::MainWindow *ui;
    QString css;
    QString acquireResult(const QString& keyword);
    QString readResult();
    void loadCSS();
    QString assemblyResult(const QString& result);
    void loadResult(const QString& result);
};

#endif // MAINWINDOW_H
