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

//Загрузка изображения на форму
void MainWindow::on_loadImageBtn_clicked()
{
    QString fileImage = QFileDialog::getOpenFileName(
                this,
                tr("Выберите изображение"),
                "",
                "Images(*.png *.jpg *.jpeg)"
                );
    image = QImage(fileImage);
    QGraphicsScene *graphic = new QGraphicsScene(this);
    graphic->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView->setScene(graphic);
    ui->graphicsView->fitInView(graphic->sceneRect(),Qt::KeepAspectRatio);
}

//Преобразование изображения в бинарный файл
void MainWindow::on_toBinaryBtn_clicked()
{
    if(!image.isNull())
    {
        QByteArray ba;
        QBuffer buf(&ba);
        buf.open(QIODevice::WriteOnly);
        image.save(&buf,"jpg");
        QFile bin("bin.txt");
        if(bin.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&bin);
            stream << ba.toBase64();
            bin.close();
        }
        QMessageBox::information(this," ","Успешно");
    }
    else QMessageBox::information(this," ","Ошибка");
}

//Преобразование бинарного файла в изображение
//Сохранение нового изображения
void MainWindow::on_toImageBtn_clicked()
{
    QString fileTxt = QFileDialog::getOpenFileName(
                this,
                tr("Выберите текстовый файл"),
                "",
                "Text file(*.txt)"
                );
    QFile bin(fileTxt);
    if(bin.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&bin);
        while(!stream.atEnd())
        {
            QString str = stream.readLine();
            QByteArray ba = QByteArray::fromBase64(str.toUtf8());
            QImage newImage;
            newImage.loadFromData(ba);
            QGraphicsScene *graphic = new QGraphicsScene(this);
            graphic->addPixmap(QPixmap::fromImage(newImage));
            ui->graphicsView->setScene(graphic);
            ui->graphicsView->fitInView(graphic->sceneRect(),Qt::KeepAspectRatio);
            newImage.save("newImage.jpg","JPG");
        }
        bin.close();
    }
    else QMessageBox::information(this," ","Ошибка");
}

