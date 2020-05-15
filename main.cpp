#include "image.h"
#include "calcimage.h"
#include "rpn.h"

//a\u2081\u2082\u2083
//36pt = 24 пкс//17 пкс высота
//36pt = 21 пкс//9//12//12 ширина

bool openFile(QString filename, QString * content){
    bool opened = false;
    if(!filename.isEmpty())
    {
        QFile file(filename);
        opened = file.open(QIODevice::ReadOnly);

        if(opened)
        {
            QTextStream outputData(&file);

            *content = outputData.readLine();

            file.close();
        }
    }
    return opened;
}

bool isDigits(const QString & string)
{
    QStringList parce_str = string.split(" ");
    bool isOk = true;
    while (parce_str.size() != 0 && isOk){
      isOk = (RPN::isNum(parce_str[0]) || parce_str[0] == "-");
      parce_str.pop_front();
    }
    return isOk;
}

int main(int argc, char *argv[])
{
    QGuiApplication app( argc, argv );                      //Инициализация ядра приложения


    RPN excep("2 1 + [ 10 1 / 1*");



    qDebug() << excep.getParam();


    QString test;

    openFile("test.txt",&test);

    qDebug() << *argv;

    return 1;

    //======================================================================================


    int dimension   = 3;
    int count_cell  = 2;
    int count_row   = 4;
    int count_table = 3;

    //Расчет изображения
    CalcImage size_image(dimension,count_cell,count_row,count_table);

    qDebug() << size_image.getSizeCell() << " - Cell";
    qDebug() << size_image.getWidth() << "x" << size_image.getHeight();

    //Ограничение:
    // Одномерный массив до 100 элементов
    // Двумерный массив до 100 в каждом направлении
    // Трехмерный массив 58х1 2х44 19х4 10х8 и (j =90,7/i-1,036 и k до 90)
    if (size_image.getHeight() >= 16384 || size_image.getWidth() >= 16384){
        qDebug() << "Over resolution";
        return -1;
    }

    //Создание изображение нужного размера
    image img1(size_image.getHeight(),size_image.getWidth());



    return 0;
}
