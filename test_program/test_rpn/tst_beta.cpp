#include <QtTest>
#include "rpn.h"

// add necessary includes here

class beta : public QObject
{
    Q_OBJECT

public:
    explicit beta(QObject *parent = 0);

private slots:
    void test_RPN_isNum();
    void test_RPN_excep();

};



beta::beta(QObject *parent) :
    QObject(parent)
{

}

void beta::test_RPN_isNum()
{
    QCOMPARE(RPN::isNum("a"),false);
    QCOMPARE(RPN::isNum("100"),true);
    QCOMPARE(RPN::isNum("0123456789"),true);

}

void beta::test_RPN_excep()
{
    QMap<QString,QString> err;
    err.insert("low_operation","Ошибка. Выражение задано неправильно - недостаточно операций над операндами");
    err.insert("low_operand_sub","Ошибка. недостаточно операндов для операции вычитания");
    err.insert("low_operand_add","Ошибка. недостаточно операндов для операции сложения");
    err.insert("low_operand_mul","Ошибка. недостаточно операндов для операции умножения");
    err.insert("low_operand_div","Ошибка. недостаточно операндов для операции деления");
    err.insert("low_operand_inc","Ошибка. недостаточно операндов для операции инкрементации");
    err.insert("low_operand_dec","Ошибка. недостаточно операндов для операции декрементации");
    err.insert("low_operand_pre_inc","Ошибка. недостаточно операндов для операции инкрементации");
    err.insert("low_operand_pre_dec","Ошибка. недостаточно операндов для операции декрементации");
    err.insert("low_operand_index","Ошибка. недостаточно операндов для операции обращения к элементу массива");
    err.insert("unknown","Ошибка. Встречен неизвестный операнд: ");
    RPN a("");
    QCOMPARE(a.getError(), "");
    a.set_excep("2 +");
    QCOMPARE(a.getError(), err["low_operand_add"]);
    a.set_excep("2 -");
    QCOMPARE(a.getError(), err["low_operand_sub"]);
    a.set_excep("2 2*");
    QCOMPARE(a.getError(), err["low_operand_mul"]);
    a.set_excep("2 /");
    QCOMPARE(a.getError(), err["low_operand_div"]);
    a.set_excep("1++");
    QCOMPARE(a.getError(), err["low_operand_inc"]);
    a.set_excep("1--");
    QCOMPARE(a.getError(), err["low_operand_dec"]);
    a.set_excep("++1");
    QCOMPARE(a.getError(), err["low_operand_pre_inc"]);
    a.set_excep("--1");
    QCOMPARE(a.getError(), err["low_operand_dec"]);
    a.set_excep("[");
    QCOMPARE(a.getError(), err["low_operand_index"]);
    a.set_excep("1*");
    QCOMPARE(a.getError(), err["low_operand_index"]);
    a.set_excep("2 *");
    QCOMPARE(a.getError(), err["unknown"]+"*");

    QVector<int> exp_index;

    a.set_excep("1 2 + [ 12 3 / [ 5 3 - [ 2 5 2* [");
    exp_index = {3,4,2,10};
    QCOMPARE(a.getIndexes(),exp_index);
}

QTEST_APPLESS_MAIN(beta)

#include "tst_beta.moc"
