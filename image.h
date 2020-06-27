/*!
 * \file image.h
 * \brief файл содержащий описание класса image
 */
#ifndef IMAGE_H
#define IMAGE_H

#include <QGuiApplication>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QObject>

/*!
 * \class image
 * \brief Класс для создания изображения и отрисовки массива на нем
 * \author Гуляев Иван
 */
class image
{
public:
    /*!
    * \brief Конструктор класса, создающий изображение в оперативной памяти
    * \param [in] height Высота изображения
    * \param [in] width Ширина изображения
    */
    image(int height, int width);

    /*!
     * \brief Сохранение изображения на диск
     * \result Файл "array.png" в директории программы
     */
    void saveImage();

    /*!
     * \brief Отрисовать массивы
     * \param [in] size_cell Размер ячейки
     * \param [in] dimension Размерность массива
     * \param [in] countCell Количество ячеек
     * \param [in] countRow Количество строк, по умолчанию 0
     * \param [in] countTable Количество таблиц, по умолчанию 0
     * \return true если таблица отрисована без ошибок, иначе false
     */
    bool drawArrays(int size_cell, int dimension, int countCell, int countRow = 0, int countTable = 0);

    /*!
     * \brief Полная закраска массива
     */
    void fillAll();

    /*!
     * \brief Выделение таблицы
     * \param [in] i Номер таблицы
     * \return true если таблица выделена без ошибок, иначе false
     */
    bool fillTable(int i);

    /*!
     * \brief Выделение строки
     * \param [in] row Номер строки
     * \param [in] numTable Номер таблицы, по умолчанию 0
     * \return true если строка выделена без ошибок, иначе false
     */
    bool fillRow(int row, int numTable = 0);

    /*!
     * \brief Выделение ячейки
     * \param [in] cell Номер ячейки
     * \param [in] row Номер строки, по умолчанию 0
     * \param [in] numTable Номер таблицы, по умолчанию 0
     * \return true если ячейка выделена без ошибок, иначе false
     */
    bool fillCell(int cell, int row = 0, int numTable = 0);

private:

    QImage   *img;                          ///< Изображение
    QPainter *p;                            ///< Перо, при помощи которого происходит отрисовка
    QRect    tmp;                           ///< Объект прямоугольника

    /*!
     * \brief Рисует таблицу с элементами массива
     * \param [in] row Количество строк
     * \param [in] column Количество столбцов
     * \param [in] start Верхний левый угол таблицы
     * \param [in] num Номер таблицы. При значении -1 элементы не указывают на номер таблицы (по умолчанию)
    */
    void drawTable(int row, int column, QPoint start, int num = -1);

    /*!
     * \brief Составление подписи элемента массива
     * \param [in] i Номер ячейки
     * \param [in] j Номер строки. При значении -1 элементы не указывают на номер строки (по умолчанию)
     * \param [in] k Номер таблицы. При значении -1 элементы не указывают на номер таблицы (по умолчанию)
     * \return Подпись элемента массива
     */
    QString getElementName(int i,int j=-1,int k=-1);
    /*!
     * \brief Получение подстрочного числа
     * \param [in] num Число
     * \return Строка с подстрочным числом
     */
    QString getSubscriptNumber(int num);

protected:

    int size_cell_  = 0;                    ///< Размер ячейки
    int dimension_;                         ///< Размерность
    int count_cell_ = 0;                    ///< Количество ячеек
    int count_row_  = 0;                    ///< Количество строк
    int count_table_ = 0;                   ///< Количество таблиц

    // Вспомогательный словарь перевода цифры в подстрочную цифру
    const QString subscript_number[10] = {"\u2080","\u2081","\u2082","\u2083","\u2084","\u2085","\u2086","\u2087","\u2088","\u2089"};

    /// Размеры отступов
    enum SIZE_INDENTS {
        SIZE_INDENT             = 2*5,     ///< Отступ от края изображения
        SIZE_INDENT_BETWEEN_ARR = 100      ///< Отступ между таблицами
    };

    QRgb COLOR_SELECTED_CELL    = qRgb(255,200,200); ///< Цвет выделения
};

#endif // IMAGE_H
