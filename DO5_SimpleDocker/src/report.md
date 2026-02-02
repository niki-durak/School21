# S21_SimpleDocker

## Part1. Ready-made docker

* Загружаем официальный docker-образ с nginx `docker pull` 
![pull_nginx](images/1-1.png)

* `docker images` 
![docker_images](images/1-2.png)

* Запустим docker-образ через команду `docker run -d [image_id|repository]` 
![docker_run_nginx](images/1-3.png)
```
-d: это флаг, который указывает Docker на запуск контейнера в фоновом режиме (detached mode). Это означает, что контейнер будет работать в фоновом режиме, и командная строка будет освобождена для дальнейшего использования.
```

* Удостоверимся, что контейнер успешно запустился через команду `docker ps` 
![docker_ps_1](images/1-4.png)

* Теперь посмотрим информацию о контейнере через команду `docker inspect [container_id|container_name]` 
![docker_inspect](images/1-5.png)

* Выведем размер контейнера  
![grep_size](images/1-6.png)

* А теперь - список замапленных портов  
![mapped_ports](images/1-7.png)

* И, наконец, IP контейнера  
![docker_ipaddress](images/1-8.png)

* Остановим docker-образ командой `docker stop [container_id|container_name]` и проверим, что образ успешно остановился через уже знакомую команду `docker ps` 
![docker_stop](images/1-9.png)

* Теперь запустим docker-образ с портами 80:80 и 443:443 чере команду `docker run` 
![docker_run_8080](images/1-10.png)

* Удостоверимся, что все работает, открыв в браузере страницу по адресу `localhost` 
![docker_localhost](images/1-12.png)

* Наконец, перезапустим контейнер через команду `docker restart [container_id|container_name]` и проверим, что контейнер снова запустился командой `docker ps` 
![docker_restart](images/1-13.png)

# Part2. Operations with container

* Для начала прочтем конфигурационный файл `nginx.conf` внутри docker-контейнера через команду `docker exec` 
![docker_restart](images/2-1.png)

* Теперь создадим локальный файл `nginx.conf` при помощи команды `touch nginx.conf` и настроем в нем выдачу страницы-статуса сервера по пути `/status` 
![docker2_myconf](images/2-2.png)
![nginx.conf](images/2-3.png)

* Наконец, перенесем созданный файл внутрь docker-образа командой `docker cp` 
![docker2_cp](images/2-4.png)

* И перезапустим nginx внутри docker-образа командой `docker exec [container_id|container_name] nginx -s reload` 
![docker2_exec_nginx](images/2-5.png)

* Убедимся, что все работает, проверив страницу по адресу `localhost/status` 
![docker2_new_conf](images/2-7.png)

* Теперь экспортируем наш контейнер в файл `container.tar` командой `docker export` 
![docker2_tar](images/2-8.png)

* Затем удалим образ командой `docker rmi -f [image_id|repository]`, не удаляя перед этим контейнеры 
![docker2_remove_nginx](images/2-9.png)
![rmi](images/2-10.png)


* После чего удалим остановленный контейнер командой `docker rm [container_id|container_name]` 
![docker2_remove_container](images/2-11.png)

* Теперь импортируем контейнер обратно командой `docker import` и запустим импортированный контейнер уже знакомой командой `dicker run` 
![docker2_import](images/2-12.png)
![docker2_run](images/2-13.png)

* Наконец проверим, что по адресу `localhost/status` выдается страничка со статусом сервера nginx 
![docker2_localhost8080](images/2-14.png)

## Part3. Mini web server

* Чтобы создать свой мини веб-сервер, необходимо создать .c файл, в котором будет описана логика сервера (в нашем случае - вывод сообщения `Hello World!`), а также конфиг `nginx.conf`, который будет проксировать все запросы с порта 81 на порт 127.0.0.1:8080 
![docker3_server](images/3-1.png) 
![docker3_conf](images/3-2.png)

* Теперь выкачаем новый docker-образ и на его основе запустим новый контейнер 
![docker3_new_nginx](images/3-3.png)

* После перекинем конфиг и логику сервера в новый контейнер 
![docker3_copied](images/3-4.png)

* Затем установим требуемые утилиты для запуска мини веб-сервера на FastCGI, в частности `spawn-fcgi` и `libfcgi-dev` 
![docker3_install](images/3-5.png)

* Наконец скомпилируем и запустим наш мини веб-сервер через команду `spawn-fcgi` на порту 8080 
![docker3_start_server](images/3-6.png)

* Чтобы удостовериться, что все работает корректно, проверим, что в браузере по адресу `localhost:81` отдается написанная нами страница 
![docker3_hello_world](images/3-7.png)



## Part4. Your own docker

* Напишем свой docker-образ, который собирает исходники 3-й части, запускает на порту `80`, после копирует внутрь написанный нами `nginx.conf` и, наконец, запускает `nginx` (ниже приведены файлы `run.sh` и `Dockerfile`, файлы `nginx.conf` и `server.c` остаются с 3-й части)

![docker4_runsh](images/4-1.png)  
![docker4_dockerfile](images/4-2.png)  

* Соберем написанный docker-образ через команду `docker build`, при этом указав имя и тэг нашего контейнера  
![docker4_build.png](images/4-3.png)  

* Теперь удостоверимся, что все собралось, проверив наличие соответствующего образа командой `docker images`  
![docker4_images.png](images/4-4.png)  

* После запустим собранный docker-образ с мапингом порта `81` на порт `80` локальной машины, а также мапингом папки `./nginx` внутрь контейнера по адресу конфигурационных файлов nginx'а, и проверим, что страничка написанного сервера по адресу 
![docker4_run_server.png](images/4-5.png)


* Теперь добавим в файл `nginx.conf` проксирование странички `/status`, по которой необходимо отдавать статус сервера `nginx  
![docker4_nginx.png](images/4-6.png)

* Теперь перезапустим `nginx` в своем docker-образе командой `nginx -s reload`  
![docker4_reload_serv.png](images/4-7.png)

* Наконец, проверим, что по адресу `localhost/status` выдается страничка со тсатусом сервера `nginx`  
![docker4_success.png](images/4-8.png)


## Part5. Dockle

```
!!Примечание!!
Перед выполнением данного шага необходимо установить утилиту [dockle], инструкция по установке [https://github.com/goodwithtech/dockle], если машина не видит утилиту [https://github.com/aquasecurity/trivy/issues/2432], также рекомендую добавить своего пользователя в группу [docker]
```

* Просканируем docker-образ из предыдущего задания на предмет наличия ошибок командой `dockle [image_id|repository]`  
![part5_troubles.png](images/5-1.png)

* Далее исправим конфигурационные файлы docker-образа так, чтобы при проверке через утилиту `dockle` не возникало ошибок и предупреждений (для Part5 я создал отдельный контейнер с тэгом `part5`, куда подгрузил измененные конфиги)  
![part5_new_build.png](images/5-2.png)
![part5_check_build.png](images/5-3.png)
![part5_success.png](images/5-4.png)

## Part6. Basic Docker Compose

```
!!Примечание!!
Перед выполнением данного шага необходимо установить утилиту [docker-compose], инструкция по установке [https://www.digitalocean.com/community/tutorials/how-to-install-and-use-docker-compose-on-ubuntu-20-04]
```

* Для начала остановим все запущенные контейнеры командой `docker stop`  
![docker6_remove.png](images/6-1.png)

* Затем изменим конфигурационные файлы (их можно найти в папке `src/part6`)

* Теперь сбилдим контейнер командой `docker-compose build`
![part6_build.png](images/6-2.png)  

* После необходимо поднять сбилженный контейнер командой `docker compose up`
![part6_dockerup.png](images/6-3.png)  

* В завершение насладимся плодами своей усердной работы, удостоверившись, что по адресу `localhost` отдается страничка с надписью `Hello World!`
![part6_success.png](images/6-4.png)  
