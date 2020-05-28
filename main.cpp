#include "image.h"
#include "calcimage.h"
#include "rpn.h"
#include <math.h>
#include <windows.h>

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

    int dimension   = 0;
    int count_cell  = 0;
    int count_row   = 0;
    int count_table = 0;

    int count_access;
    QVector<int> index;

    //Проверка входных данных
    //===================================================================================

    try {
        QString str_error;
        qDebug() << QString().setNum(argc);
        qDebug() << "Проверка аргументов";

        //Если недостаточно аргументов
        if (argc != 4) {
            throw "Ошибка передачи аргументов в программу. Недостаточно переданных значений.";
        }

        qDebug() << "Проверка считывания фаила";
        //Чтение из фаилов

        if (!QString(argv[1]).endsWith(".txt") || !QString(argv[2]).endsWith(".txt") || !QString(argv[3]).endsWith(".txt")) {
            throw "Ошибка передачи аргументов в программу. Был передан недопустимый файл.";
        }

        //Если значения не удалось прочитать из фаила
        //  Первый аргумент - размер и размерность матрицы.
        //  Второй аргумент - выражение, содержащее переменные i, j, k.
        //  Третий аргумент - значения переменных i, j, k
        if (!openFile(argv[1],&str_dimension_size) ||
                !openFile(argv[2],&str_expression)     ||
                !openFile(argv[3],&str_value_param))
        {
            //Сообщаем об ошибке
            throw "Ошибка передачи аргументов в программу. Неправильно названы файлы или они отсутствуют в каталоге.";
        }


        qDebug() << "Проверка выражения";
        //Если выражение неверно
        if (correctExpression(str_expression, &str_error) == false) {
            //Сооющаем об ошибке
            throw str_error;
        }

        qDebug() << "Проверка размера и размерности";
        //Если размерность и размер введены неправильно
        if (correctDimensionAndSize(str_dimension_size,&str_error) == false) {
            //Сооющаем об ошибке
            throw str_error;
        } else {
            //Заменить значения

            QTextStream(&str_dimension_size) >> dimension >> count_cell  >> count_row >> count_table;

        }

        qDebug() << "Проверка значений размера и размерности";
        //Проверка на размерность 1-3
        // Одномерный массив до 100 элементов
        // Двумерный массив до 100 в каждом направлении
        // Трехмерный массив 58х1 2х44 19х4 10х8 и (j =90,7/i-1,036 и k до 90)

        if (dimension == 1) {
            if (count_cell > 100) {
                throw "Ошибка размера или размерности. Превышен размер массива.";
            }
        } else
            if (dimension == 2) {
                if (count_cell > 100 || count_row >100){
                    throw "Ошибка размера или размерности. Превышены размеры массива.";
                }
            }
            else
                if (dimension == 3){
                    int calc_row = round(90.7/count_table-1.036);
                    if (count_cell > 90 || count_row > calc_row) {
                        throw "Ошибка размера или размерности. Превышены размеры массива.";
                    }
                }
                else {
                    throw "Ошибка размера или размерности. Неверно введено значение размерности.";
                }

        qDebug() << "Проверка значений переменных";
        //Если присутствует символ в значениях переменных
        if(!isDigits(str_value_param)){
            throw "Ошибка значений переменных. Значения переменных заданы неверно.";
        }

        qDebug() << "Проверка количества значений переменных";
        int count_param_in_excep = str_expression.count('i')+
                                   str_expression.count('j')+
                                   str_expression.count('k');

        int count_value_for_param = 0;

        if (!str_value_param.isEmpty()) {
            count_value_for_param = str_value_param.split(" ").size();
        }

        if (count_value_for_param > count_param_in_excep) {
            throw  "Ошибка значений переменных. Превышено количество значений переменных для данного выражения.";
        }
        else if (count_value_for_param < count_param_in_excep){
            throw  "Ошибка значений переменных. Недостаточно значений переменных для данного выражения.";
        }

        qDebug() << "Проверка операций по взятию индекса";
         //Проверка на количество [ и 1* и размерности
        count_access = str_expression.count("[") + str_expression.count("1*");
        if (count_access > dimension) {
            throw "Ошибка. В выражении операций получения индекса больше, чем размерность массива.";
        }

        qDebug() << "Замена переменных в выражении";
        //Заменить в выражении переменные на их значения
        QStringList parce_value = str_value_param.split(" ");

        if (parce_value.size() >= 1)
        str_expression.replace(QChar('i'),parce_value[0]);
        if (parce_value.size() >= 2)
        str_expression.replace(QChar('j'),parce_value[1]);
        if (parce_value.size() >= 3)
        str_expression.replace(QChar('k'),parce_value[2]);

        qDebug() << "Обработка выражения";
        //Передать выражение в класс и обработать его
        RPN expression(str_expression);

        qDebug() << "Получения значений";
        //Если ошибки нет
        if (expression.getError().isNull()){
            //Получить значения
            index = expression.getIndexes();
        } else
        {
            //Сообщить об ошибке
            throw  expression.getError().toUtf8().constData();
        }

        //Проверка полученных значений на диапазон
        qDebug() << "Проверка полученных значений на диапазон";
        QVector<int> tmp_index = index;
        QVector<int> bound_arr;

        switch (dimension) {
        case 1:
            bound_arr << count_cell ;
            break;
        case 2:
            bound_arr << count_row << count_cell ;
            break;
        case 3:
            bound_arr << count_table << count_row << count_cell ;
            break;

        }

        tmp_index.insert(tmp_index.size(),dimension - index.size(),0);

        for (int i = 0; i<tmp_index.size();i++){
            if (tmp_index[0] >= bound_arr[0])
            {
                throw "Ошибка. Выход за пределы массива.";
            }
        }

    }

    catch (const char* msg_err) {
        //Вывести ошибку в консоль
        qCritical() << msg_err;
        return -1;
    }
    catch (QString msg_err) {
        qCritical() << msg_err.toUtf8().constData();
        return -1;
        }


    //===================================================================================

    //Считаем, что все проверки прошли



    qDebug() << "Расчет изображения";
    //Расчет изображения
    CalcImage size_image(dimension,count_cell,count_row,count_table);

    //Ограничение:
    // Одномерный массив до 100 элементов
    // Двумерный массив до 100 в каждом направлении
    // Трехмерный массив 58х1 2х44 19х4 10х8 и (j =90,7/i-1,036 и k до 90)
    if (size_image.getHeight() >= 16384 || size_image.getWidth() >= 16384){
        qDebug() << "Over resolution";
        return -1;
    }
    // ^^^^^^^^^^^^^^^^^^ it's test ^^^^^^^^^^^^^^^^^^^^^^^^^^
    qDebug() << "Создание изображения";
    //Создание изображение нужного размера
    image img_matrix(size_image.getHeight(),size_image.getWidth());


    //Отрисовка

    img_matrix.drawArrays(size_image.getSizeCell(),dimension,count_cell,count_row,count_table);

    qDebug() << "Отрисовка";
    if (count_access == 0) {
        img_matrix.fillAll();
    } else

        switch (dimension) {
        case 1:
            if (count_access == 1){
                img_matrix.fillCell(index[0]);
            }
            break;
        case 2:
            if (count_access == 1){
                img_matrix.fillRow(index[0]);
            }
            if (count_access == 2){
                img_matrix.fillCell(index[1],index[0]);
            }
            break;
        case 3:
            if (count_access == 1){
                img_matrix.fillTable(index[0]);
            }
            if (count_access == 2){
                img_matrix.fillRow(index[1],index[0]);
            }
            if (count_access == 3){
                img_matrix.fillCell(index[2],index[1],index[0]);
            }
            break;
        }

    qDebug() << "Сохранение";
    //Сохранение
    img_matrix.saveImage();


    return 0;
}
