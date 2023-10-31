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

//Преобразование изображения в двоичное представление
void MainWindow::on_toBinaryBtn_clicked()
{
    if (!image.isNull())
    {
        QByteArray ba;
        QBuffer buf(&ba);
        buf.open(QIODevice::WriteOnly);
        image.save(&buf, "jpg");
        QString binaryString;
        for (int i = 0; i < ba.size(); ++i) // Перебор байтов
        {
            uchar byte = ba[i];
            for (int j = 7; j >= 0; --j) // Перебор каждого бита в байте
            {
                int bit = (byte >> j) & 1;
                binaryString += QString::number(bit);
            }
        }
        QFile bin("bin.txt");
        if (bin.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&bin);
            stream << binaryString;
            bin.close();
        }
        QMessageBox::information(this, " ", "Успешно");
    }
    else QMessageBox::information(this," ","Error");
}

// Преобразование текстового файла с 0 и 1 в изображение
// Сохранение нового изображения
void MainWindow::on_toImageBtn_clicked()
{
    QString fileTxt = QFileDialog::getOpenFileName(
                this,
                tr("Выберите текстовый файл"),
                "",
                "Text file(*.txt)"
                );
    QFile bin(fileTxt);
    if (bin.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&bin);
        QString binaryString = stream.readAll();
        QByteArray ba;
        for (int i = 0; i < binaryString.size(); i += 8) // Перебор всех бит
        {
            QString byteStr = binaryString.mid(i, 8); // Получение 1 байта
            ba.append(static_cast<char>(byteStr.toInt(nullptr, 2)));
        }
        QImage newImage;
        newImage.loadFromData(ba);
        QGraphicsScene *graphic = new QGraphicsScene(this);
        graphic->addPixmap(QPixmap::fromImage(newImage));
        ui->graphicsView->setScene(graphic);
        ui->graphicsView->fitInView(graphic->sceneRect(), Qt::KeepAspectRatio);

        bin.close();
        newImage.save("newImage.jpg", "JPG");
        QMessageBox::information(this, " ", "Изображение сохранено");
    }
    else
        QMessageBox::information(this, " ", "Ошибка");
}

