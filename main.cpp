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
      isOk = (RPN::isNum(parce_str[0]));
      parce_str.pop_front();
    }
    return isOk;
}

bool checkExpression(const QString & expression, QString * error)
{
    bool isOk = true;
    QStringList operation = {"+","-","1*","2*","/","["};
    //Проверка на количество введенных переменных
    if (expression.count("i") >1 ||
           expression.count("j") >1 ||
            expression.count("k") >1) {
        isOk = false;
        *error = "Ошибка в выражении. Встречено несколько одинаковых переменных";
    }

    QStringList parce_expr = expression.split(" ");
    while (parce_expr.size() != 0 && isOk){
        //Проверка на число
        if (!isDigits(parce_expr[0])){
            //Проверка на оператор и на букву i j k
            if (operation.contains(parce_expr[0]) || parce_expr[0] == "i" || parce_expr[0] == "j" || parce_expr[0] == "k") {
                //Все ОК, продолжаем
                isOk = true;
            } else {
                //Иначе сообщаем, что встречен посторонний символ
                *error = "Ошибка в выражении. Встречен недопустимый символ.";
                isOk   = false;
            }
        }
        parce_expr.pop_back();
    }
    return isOk;
}

bool correctDimensionAndSize(const QString & dimension_size,  QString * error){
    bool isOk = true;

    //Проверка на лишние символы
    if(!isDigits(dimension_size)){
      *error = "Ошибка размера или размерности. Присутствуют недопустимые символы.";
      isOk   = false;
    }

    //Проверка на отрицательные значения
    if (dimension_size.count("-")> 0) {
        *error = "Ошибка размера или размерности. Введено отрицательное значение.";
        isOk   = false;
    }

    QStringList parse_dimension_size = dimension_size.split(" ");
    parse_dimension_size.removeOne("");

    //Проверка на количество входных данных
    int  count_value = parse_dimension_size.size();

    if (count_value > 4){
       *error = "Ошибка размера или размерности. Превышено количество значений.";
       isOk   = false;
    }

    if (count_value < 2) {
        *error = "Ошибка размера или размерности. Недостаточно значений.";
        isOk   = false;
    }

    return isOk;
}

int main(int argc, char *argv[])
{
    QGuiApplication app( argc, argv );                      //Инициализация ядра приложения

    //Фикс русского языка
    SetConsoleOutputCP(1251);

    QString str_dimension_size;
    QString str_expression;
    QString str_value_param;

    //Проверка входных данных
    //===================================================================================

    //Проверка количества аргументов и их порядок
    if (argc != 3) {

        qDebug() << "Недостаточно переданных значений";
        //return 1;

    } else {
        //Чтение из фаилов
        //Если значения не удалось прочитать из фаила
        //  Первый аргумент - размер и размерность матрицы. Из строки в 4 числа
        //  Второй аргумент - выражение, содержащее переменные i, j, k.
        //  Третий аргумент - значения переменных i, j, k
        if (!openFile(argv[0],&str_dimension_size) ||
            !openFile(argv[1],&str_expression) ||
            !openFile(argv[2],&str_value_param)){
            //Сообщаем об ошибке и завершаем программу
            qDebug()<< "Неправильно названы фаилы или они отсутсвуют в каталоге";
            //return 2;
        }
    }
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
