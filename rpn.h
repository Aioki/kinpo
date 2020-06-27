/*!
 * \file rpn.h
 * \brief файл содержащий описание класса RPN
 */
#ifndef RPN_H
#define RPN_H

#include <QObject>
/*!
 * \class RPN
 * \brief Класс, обрабатывающий выражение обратной польской записи для получения индексов обращения к массиву
 * \author Гуляев Иван
 */
class RPN
{

public:
    /*!
    * \brief Конструктор класса, обрабатывающий выражение обратной польской записи для получения индексов обращения к массиву
    * \param [in] str Выражение
    */
    RPN(QString str);

    /*!
    * \brief Проверка "операнда" на число
    * \param [in] num Операнд в виде строки
    * \return true если операнд является числом, иначе false
    */
    static bool isNum(QString num);

    /*!
    * \brief Возвращает корректность введенного выражения
    * \return true если выражение не содержит ошибок, иначе false
    */
    bool isCorrect();

    /*!
    * \brief Возвращает сообщение об ошибке во время обработки выражения
    * \return Ошибка во время обработки выражения
    */
    QString getError();

    /*!
    * \brief Возвращает индексы обращения к массиву
    * \return Индексы обращения к массиву
    */
    QVector<int> getIndexes();

protected:
    /// Словарь операций
    enum OPERATION {
        ADD,                  ///< Сложение
        MUL,                  ///< Умножение
        SUB,                  ///< Вычитание
        DIV,                  ///< Деление
        INC,                  ///< Инкрементация
        DEC,                  ///< Декрементация
        PRE_INC,              ///< Префиксная инкрементация
        PRE_DEC,              ///< Префиксная декрементация
        INDEX                 ///< Обращение к элементу массива
    };

    QString expression_;      ///< Хранит выражение
    QVector<int> stack;       ///< Вычислительный стэк
    bool isOk = true;         ///< Флаг корректности
    QString error;            ///< Хранит сообщение об ошибке
    QVector<int> indexes;     ///< Хранит индексы обращения к массиву

    /// Парсинг выражения
    bool parceExp();

    /// Взятие числа из стека. Возвращает true, если получилось взять, иначе false
    bool takeNum(int & a);

    /// Взятие чисел из стека. Возвращает true, если получилось взять, иначе false
    bool takeNum(int & a, int & b);

    /// Обработчик ошибки во время вычисления
    void genError(QString str);

    /// Выполнение операций
    void performCalc(OPERATION cur);


};

#endif // RPN_H
