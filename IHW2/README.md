# Чижов Андрей Дмитриевич БПИ218
# ИДЗ-2 вариант 26
### условие задачи
```text
Задача о производстве булавок. В цехе по заточке булавок все необходимые операции осуществляются тремя рабочими.
Первый из них берет булавку и проверяет ее на предмет кривизны. Если булавка не кривая, то рабочий передает ее своему напарнику.
Иначе выбрасывает в отбраковку. Напарник осуществляет собственно заточку и передает заточенную булавку третьему рабочему,
который осуществляет контроль качества операции бракуя булавку или отдавая на упаковку. Требуется создать приложение,
моделирующее работу цеха. При решении использовать парадигму «производитель-потребитель». Следует учесть, 
что каждая из операций выполняется за случайное время которое не связано с конкретным рабочим. 
Возможны различные способы реализации передачи (на усмотрение разработчика). Либо непосредственно по
одной булавке, либо через ящики, в которых буферизируется некоторое конечное количество булавок.
```
### Пример работы программы:
![](https://github.com/AndreyChizhovD/Operating-Systems/blob/main/IHW2/ihw2.png)
##
* Булавки обрабатываются последовательно тремя рабочими.
* Каждый из рабочих может ее забраковать. 
* У каждого следующего рабочего вероятность забраковать булавку меньше предыдущего.
* Если булавка бракуется на любом этапе, начинает обрабатываться следующая.
##
[4.c](4.c) - используется неименованные семафоры \
[5.c](5.c) - используется именованные семафоры
##
Программы запускаются с помощью скрипта
```bash
#!/bin/bash

gcc {mark}.c
./a.out
rm a.out
```
