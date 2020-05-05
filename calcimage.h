#ifndef CALCIMAGE_H
#define CALCIMAGE_H

#include <QObject>

//\brief Класс, расчитывающий размеры изображения по характеристикам массива - размера и размерности. Расчет происходит при объвлении класса
class CalcImage
{
public:
    CalcImage(int dimension, int size_i, int size_j = 0, int size_k = 0);

    int getSizeCell() const;
    int getWidth() const;
    int getHeight() const;

private:


    //\brief Расчитывает размер одной ячейки, из которых будет составлена таблица.
    void calcCell();
    //\brief Расчитывает конечный размер изображения
    void calcSizeImage();

    int height     = 0;
    int width      = 0;
    int size_cell  = 0;


    int dimension_;
    int size_i_;
    int size_j_;
    int size_k_;

protected:
    const int size_name_array         = 21;
    const int size_indent             = 2*5;
    const int size_subscript_number   = 15;
    const int size_comma              = 9;
    const int size_indent_between_arr = 100;
};

#endif // CALCIMAGE_H
