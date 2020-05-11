#ifndef RPN_H
#define RPN_H

#include <QObject>

class RPN
{
public:
    //Конструктор
    RPN(QString str);
    //\brief Возвращает корректность введенного выражения
    bool isCorrect();
    QString getError();
    QVector<int> getParam(); //TODO - Rename

protected:
    //Словарь операций
    enum Operation {
        ADD,
        MUL,
        SUB,
        DIV,
        INC,
        DEC,
        PRE_INC,
        PRE_DEC,
        INDEX
    };
    //Переменная для выражения
    QString expression_;
    //Cтэк
    QVector<int> stack;
    //Флаг наличия ошибок
    bool isOk = true;
    //Сообщение об ошибке
    QString error;
    QVector<int> parameters; //TODO - Rename

    //Парсинг выражения
    bool parceExp();
    //Взятие числа из стека. Возвращает true, если получилось взять, иначе false
    bool takeNum(int & a);
    //Взятие чисел из стека. Возвращает true, если получилось взять, иначе false
    bool takeNum(int & a, int & b);
    //Обработчик ошибки во время вычисления
    void genError(QString str);
    //Выполнение операций
    void performCalc(Operation cur);
    //Проверка "операнда" на число
    bool isNum(QString num);

};

#endif // RPN_H
