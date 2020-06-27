#ifndef RPN_H
#define RPN_H

#include <QObject>

class RPN
{
public:
    //Конструктор
    RPN(QString str);

    void set_excep(QString str);
    //Проверка "операнда" на число
    static bool isNum(QString num);

    //\brief Возвращает корректность введенного выражения
    bool isCorrect();
    QString getError();
    QVector<int> getIndexes(); //TODO - Rename

protected:
    //Словарь операций
    enum OPERATION {
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
    QVector<int> indexes; //TODO - Rename

    //Парсинг выражения
    bool parceExp();
    //Взятие числа из стека. Возвращает true, если получилось взять, иначе false
    bool takeNum(int & a);
    //Взятие чисел из стека. Возвращает true, если получилось взять, иначе false
    bool takeNum(int & a, int & b);
    //Обработчик ошибки во время вычисления
    void genError(QString str);
    //Выполнение операций
    void performCalc(OPERATION cur);


};

#endif // RPN_H
