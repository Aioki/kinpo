@echo off
set program=.\prototype_kinpo.exe
del result.txt
del array_01.png
del array_02.png
del array_03.png
del array_04.png

echo 01 - ���������� ������. ��������� �������  >> result.txt
echo ��������� �� ������: >> result.txt
%program% 01_size_dimension.txt 01_expression.txt 01_value.txt >> result.txt
echo. >> result.txt

If Exist "array.png" (
 ren array.png array_01.png
 echo ����������� ������� >> result.txt
)

echo. >> result.txt
echo 02 - ��������� ������. ��������� ������  >> result.txt
echo ��������� �� ������: >> result.txt
%program% 02_size_dimension.txt 02_expression.txt 02_value.txt >> result.txt
echo. >> result.txt

If Exist "array.png" (
 ren array.png array_02.png
 echo ����������� ������� >> result.txt
)

echo. >> result.txt
echo 03 - ���������� ������. ��������� ������  >> result.txt
echo ��������� �� ������: >> result.txt
%program% 03_size_dimension.txt 03_expression.txt 03_value.txt >> result.txt
echo. >> result.txt

If Exist "array.png" (
 ren array.png array_03.png
 echo ����������� ������� >> result.txt
)

echo. >> result.txt
echo 04 - ���� ������. ��������� �����  >> result.txt
echo ��������� �� ������: >> result.txt
%program% 04_size_dimension.txt 04_expression.txt 04_value.txt >> result.txt
echo. >> result.txt

If Exist "array.png" (
 ren array.png array_04.png
 echo ����������� ������� >> result.txt
)

echo. >> result.txt
echo ====================== �������� ���������� ======================= >> result.txt

echo. >> result.txt
echo 05 - ������������ ���������� ��� ������� ���������  >> result.txt
echo ��������� �� ������: >> result.txt
%program% 05_size_dimension.txt 05_expression.txt >> result.txt
echo. >> result.txt

echo. >> result.txt
echo 06 - ������� ���� �� ������� ��� � ��������� ��������� >> result.txt
echo ��������� �� ������: >> result.txt
%program% 06_size_dimension.docx 06_expression.txt 06_value.txt >> result.txt
echo. >> result.txt

echo. >> result.txt
echo 07 - ����� ����������� � ����� ��������� >> result.txt
echo ��������� �� ������: >> result.txt
%program% 07_size_dimension.txt 07_expression.txt 07_value.txt >> result.txt
echo. >> result.txt

echo. >> result.txt
echo 08 - � ��������� ��������� ���������� j k  >> result.txt
echo ��������� �� ������: >> result.txt
%program% 08_size_dimension.txt 08_expression.txt 08_value.txt >> result.txt
echo. >> result.txt

echo. >> result.txt
echo 09 - � ��������� ������ q  >> result.txt
echo ��������� �� ������: >> result.txt
%program% 09_size_dimension.txt 09_expression.txt 09_value.txt >> result.txt
echo. >> result.txt

echo. >> result.txt
echo 10 - ����� �� ������� �������  >> result.txt
echo ��������� �� ������: >> result.txt
%program% 10_size_dimension.txt 10_expression.txt 10_value.txt >> result.txt
echo. >> result.txt

echo. >> result.txt
echo 11 - � ������� � ����������� ������������ ������  >> result.txt
echo ��������� �� ������: >> result.txt
%program% 11_size_dimension.txt 11_expression.txt 11_value.txt >> result.txt
echo. >> result.txt

echo. >> result.txt
echo 12 - � ������� � ����������� ������������ ������������� ��������  >> result.txt
echo ��������� �� ������: >> result.txt
%program% 12_size_dimension.txt 12_expression.txt 12_value.txt >> result.txt
echo. >> result.txt

echo. >> result.txt
echo 13 - � ������� � ����������� ��������� ���������� ��������  >> result.txt
echo ��������� �� ������: >> result.txt
%program% 13_size_dimension.txt 13_expression.txt 13_value.txt >> result.txt
echo. >> result.txt

echo. >> result.txt
echo 14 - � ������� � ����������� ������������ ��������  >> result.txt
echo ��������� �� ������: >> result.txt
%program% 14_size_dimension.txt 14_expression.txt 14_value.txt >> result.txt
echo. >> result.txt

echo. >> result.txt
echo 15 - �������� ������ ������� ��� ����������� �������  >> result.txt
echo ��������� �� ������: >> result.txt
%program% 15_size_dimension.txt 15_expression.txt 15_value.txt >> result.txt
echo. >> result.txt

echo. >> result.txt
echo 16 - ����������� ������� �� ����� "1","2" ��� "3" >> result.txt
echo ��������� �� ������: >> result.txt
%program% 16_size_dimension.txt 16_expression.txt 16_value.txt >> result.txt
echo. >> result.txt

echo. >> result.txt
echo 17 - � ��������� ���������� �� ����������� �����  >> result.txt
echo ��������� �� ������: >> result.txt
%program% 17_size_dimension.txt 17_expression.txt 17_value.txt >> result.txt
echo. >> result.txt

echo. >> result.txt
echo 18 - �������� ���������� ������, ��� ���������� � ���������  >> result.txt
echo ��������� �� ������: >> result.txt
%program% 18_size_dimension.txt 18_expression.txt 18_value.txt >> result.txt
echo. >> result.txt

echo. >> result.txt
echo 19 - �������� ���������� ������, ��� ���������� � ���������  >> result.txt
echo ��������� �� ������: >> result.txt
%program% 19_size_dimension.txt 19_expression.txt 19_value.txt >> result.txt
echo. >> result.txt

echo. >> result.txt
echo 20 - ��������� ������� � ��������� ������, ��� ����������� �������  >> result.txt
echo ��������� �� ������: >> result.txt
%program% 20_size_dimension.txt 20_expression.txt 20_value.txt >> result.txt
echo. >> result.txt
