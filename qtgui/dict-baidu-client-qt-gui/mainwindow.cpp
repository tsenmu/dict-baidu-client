#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QProcess>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Dict Baidu");
    loadCSS();
}

void MainWindow::loadCSS()
{
    QFile f(":/css/index.css");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream in(&f);
    QString result = in.readAll();
    this->css = result;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_search_clicked()
{
    qDebug() << "Search button clicked.";
    QString result = acquireResult(ui->lineEdit_keyword->text());
    //qDebug() << result;
    loadResult(result);
}

QString MainWindow::acquireResult(const QString& keyword)
{
    QProcess pycrawler;
    pycrawler.setWorkingDirectory("../../pycrawler/bin");
    pycrawler.start("./pycrawler.py", QStringList() << keyword);

    while(!pycrawler.waitForStarted())
    {
        return "ERROR";
    }
    qDebug() << "Crawler started.";
    while(!pycrawler.waitForFinished())
    {
        return "ERROR";
    }
    qDebug() << "Crawler finished.";
   // qDebug() << pycrawler.exitCode();
    return readResult();
}

QString MainWindow::readResult()
{
    QFile f("../../pycrawler/temp/result.html");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return "ERROR";
    }
    QTextStream in(&f);
    QString result = in.readAll();
    return result;
}

QString MainWindow::assemblyResult(const QString& result)
{
    return QString("<html><head><style type=\"text/css\">") + css + QString("</style></head><body>"
                                                                            "<div id=\"en-collins\" class=\"tab en-collins dict-en-collins-english\" style=\"display:block\"")
            + result+QString("</div></body></html>");
}

void MainWindow::loadResult(const QString &result)
{
    QString html = assemblyResult(result);
    qDebug() << html;
    ui->webView->setHtml(html);

}
