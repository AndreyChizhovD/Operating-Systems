# ДР №11
### задание
Разработать клиент-серверное приложение, использующее TCP/IP и реализующее следующие взаимодействия: клиент №1 передает сообщения серверу, который перенаправляет их клиенту №2.

В качестве исходных данных задавать: IP-адрес сервера, порт сервера. Эти данные можно задавать либо в командной строке, либо с использованием функций стандартного ввода.

Передаваемое сообщение задается из стандартного ввода в цикле. То есть, можно передать не одно а несколько сообщений от клиента №1 клиенту №2. При передаче сообщения «The End» необходимо завершить работу как клиентов, так и сервера.

Приложение должно функционировать в конфигурациях от одного до трех компьютеров с различными комбинациями размещения клиентов и сервера.
### пример работы программы:
![](screenshot.png)
###
К [серверу](server.c) подключаются два клиента: [Client_1](client_1.c) и [Client_2](client_2.c). \
Адрес и порт заадются аргументами командной строки. \
Клиент 1 передает сообщения клиенту 2, который выводит их на экран, пока не будет введено "The End".\
Тогда клиенты и сервер завершают работу.
