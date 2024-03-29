# Отчет по ИДЗ-1
# Чижов Андрей Дмитриевич БПИ218
# Вариант 32
Разработать программу, которая на основе анализа двух входных
ASCII-строк формирует на выходе две другие строки. В первой из
выводимых строк содержатся символы, которых нет во второй исходной строке. Во второй выводимой строке содержатся символы,
отсутствующие в первой входной строке (разности символов).
Каждый символ в соответствующей выходной строке должен встречаться только один раз.
## 
Для удобства будем использовать отдельный файл с функцией обработки двух строк. \
[32.c](32.c)
##
Будем запускать программу с помощью [скрипта](run.sh), который осуществляет чтение имен файлов ввода и вывода, которые передаются программе в качестве аргументов коммандной строки.
```bash
#!/bin/bash

read input
read output
gcc {mark}.c
./a.out $input $output
rm a.out
```
## 4
### Схема работы :
* первый процесс читает текстовые данные из заданного файла
и через неименованный канал передает их второму процессу;
* второй процесс осуществляет обработку данных в соответствии
с заданием и передает результат обработки через неименованный канал третьему процессу;
* третий процесс осуществляет вывод данных в заданный файл.

[Сама программа](4.c) работает следующим образом:
* Создаем fs, ft - первый и второй неименованные каналы для передачи из первого во второй процесс и из второго в третий соответственно.
* Создаем дочерний процесс process1.
* Делим второй (потомок) процесс и создаем третий, который выводит результат buf в output_i.txt. Создадим process2.
* Второй процесс осуществляет обработку данных и передает результат третьему.
* Первый процесс считывает содержимое файла в buf.

## 5
### Схема работы :
* первый процесс читает текстовые данные из заданного файла
и через именованный канал передает их второму процессу;
* второй процесс осуществляет обработку данных в соответствии
с заданием и передает результат обработки через именованный
канал третьему процессу;
* третий процесс осуществляет вывод данных в заданный файл.

[Сама программа](5.c) работает следующим образом:
* Создаем именованные каналы с именами pipe1 и pipe2 соответственно.
* Создаем второй процесс process1.
* Делим второй (потомок) процесс и создаем третий, который выводит результат buf в output_i.txt. Создадим process2.
* Действуем аналогично. Находясь в третьем процессе удаляем имена из системы unlink(pipe).

## Tests
| i | input_i.txt          | output_i.txt         |
|-----------------|:---------------:|:---------------:|
| 1| wbeiufvg8o28vgmcw-=+cskc  | +-28=bcefgikmosuvw |
| | dddddddddddddddddddaaaaaa | ad|
| 2  |  ab   |     |
|    |   ba  |     |
| 3 | abcdefghijklmnopqrstuvwxyz | bcdfghjklmnpqrstvwxyz |
|   | aeiou  |   |
| 4  |1234567890  | 0123456789|
|    | abcdefghij  | abcdefghij |
| 5 | -+*&^%$@%~!##!?>']  |  !#$'+->?]~|
|   |  E^DA*SGbcdibc&^%EW@^*(000** *765 | (0567ADEGSWbcdi |
###
[input{1..5}.txt](input) \
[output{1..5}.txt](output)
