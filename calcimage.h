/*!
 * \file calcimage.h
 * \brief файл содержащий описание класса calcimage
 */
#ifndef CALCIMAGE_H
#define CALCIMAGE_H

#include <QObject>
#include <QVector>
#include <QList>


/*!
 * \class CalcImage
 * \brief Класс, расчитывающий размеры изображения по характеристикам массива - размера и размерности. Расчет происходит при объвлении класса
 * \author Гуляев Иван
 */

class CalcImage
{
public:
    /*!
    * \brief Конструктор класса
    * \param [in] dimension размерность
    * \param [in] countCell количество ячеек
    * \param [in] countRow количество строк
    * \param [in] countTable количество таблиц
    */
    CalcImage(int dimension, int countCell, int countRow=0, int countTable=0);

    /*!
     * \brief Получить размер ячейки
     * \return размер ячейки
     */
    int getSizeCell() const;

    /*!
     * \brief Получить ширину изображения
     * \return ширина изображения
     */
    int getWidth() const;
    /*!
     * \brief Получить высоту изображения
     * \return Высота изображения
     */
    int getHeight() const;

private:


    /// Расчитывает размер одной ячейки, из которых будет составлена таблица.
    void calcCell();
    /// Расчитывает конечный размер изображения
    void calcSizeImage();


protected:
    /// Размеры элементов изображения
    enum SIZE_ELEM_PIC {
        SIZE_NAME_ARRAY         = 21,   ///< Размер символа массива
        SIZE_INDENT             = 10,   ///< Размер отступа
        SIZE_SUBSCRIPT_NUMBER   = 20,   ///< Размер подстрочной цифры
        SIZE_COMMA              = 10,   ///< Размер разделителя
        SIZE_INDENT_BETWEEN_ARR = 100   ///< Размер отступа между массивами
    };

    int height     = 0;                 ///< Высота изображения
    int width      = 0;                 ///< Ширина изображения
    int size_cell  = 0;                 ///< Размер ячейки

    /// [0]- Количество ячеек, [1]- Количество строк, [2]- Количество таблиц, size() - размерность
    QVector<int> arr_size;
};

#endif // CALCIMAGE_H
