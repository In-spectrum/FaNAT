<h1 align="center">
	<a href="https://github.com/In-spectrum/FaNAT" target="_blank">
		<img src="manual/images/baner.bmp" width="750" height="250">
	</a>
	<br>
	<a href="https://github.com/In-spectrum/FaNAT" target="_blank">
		Система удаленного доступа к устройствам
	</a>
</h1>

<br>

**Функции**
* удаленный доступ к устройствам, которые находятся в сети, где используется NAT;
* использование собственного (или другого доступного) сервера для:
  * управления устройствами;
  * обмена файлами;
  * захвата, трансляции и просмотра рабочего стола; 
* настройка ssh-туннеля и доступ к устройству по ssh-протоколу;

**Планируется**
* развертывание на АРМ (Raspberry Pi, NVIDIA Jetson TX2), macOS, Android (client-lite);
* захват рабочего стола в Linux, где используется Wayland; 

<br>**Application was tested:** Windows 10, Ubuntu 20.04.6;

## Table of contents

* [**FaNAT-client**](#fanat-client)
  * [Функции](#functions)
  * [Compile from source](#compile-from-source)
  * [Exemples](#exemples-1)
  	* [File sharing](#file-sharing)
  	* [Use Command line](#use-command-line)
	* [Reverse SSH Tunneling](#reverse-ssh-tunneling)
	* [Use another available server](#use-another-available-server)
	* [Commands for the server](#commands-for-the-server)
  * [**FaNAT-client-fv**](#fanat-client-fv)
	* [Available](#available)
	* [Установка](#install)
  	  	* [Windows](#windows)
  	  	* [Ubuntu](#ubuntu)
  * [**FaNAT-client-lite**](#fanat-client-lite)
	* [Available](#available-1)
	* [Unavailable](#unavailable)
	* [Установка](#install-1)
		* [Windows](#windows-1)
		* [Ubuntu](#ubuntu-1)
  * [**FaNAT-client-console-fv**](#fanat-client-console-fv)
	* [Available](#available-2)
	* [Unavailable](#unavailable-1)
	* [Установка](#install-2)
		* [Windows](#windows-2)
		* [Ubuntu](#ubuntu-2)
	* [Параметры запуска](#properties)
  * [**FaNAT-client-console-lite**](#fanat-client-console-lite)
	* [Available](#available-3)
	* [Unavailable](#unavailable-2)
	* [Установка](#install-3)
		* [Windows](#windows-3)
		* [Ubuntu](#ubuntu-3)
	* [Параметры запуска](#properties-1)
* [**Installing additional software**](#installing-additional-software)
   * [GStreamer for Windows](#gstreamer-for-windows)
* [**FaNAT-server**](#fanat-server)
  * [Функции](#functions-1)
  * [Особенности](#особенности)
  * [Установка](#install-4)
  * [Параметры запуска](#properties-2)
  * [Example script to check FaNATA-server](#example-script-to-check-fanat-server)
* [**Video-server**](#video-server)
  * [Функции](#функции)
  * [Пример](#пример)
  * [Особенности](#особенности-1)
* [**License**](#license)


## **FaNAT-client**
### &emsp;Functions  
  &emsp;&nbsp;- захват, трансляция, просмотр рабочего стола (RTSP, RTMP-поток);
  <br>&emsp;&nbsp;- отправка, эмуляция сигналов мышки и клавиатуры;
  <br>&emsp;&nbsp;- использование командной строки на управляемом устройстве. [Use Command line](#use-command-line);
  <br>&emsp;&nbsp;- возможность запустить ssh-клиент с обратным туннелем и получить доступ к устройству по ssh-протоколу.
  <br>&emsp;&nbsp;&ensp;&nbsp;[Reverse SSH Tunneling](#reverse-ssh-tunneling);
  <br>&emsp;&nbsp;- обмен файлами. Файлы сохраняются в **Download** folder. [File sharing](#file-sharing);
  <br>&emsp;&nbsp;- exchange of clipboards;
  <br>&emsp;&nbsp;- консольный вариант для использования в ваших приложениях или как дополнительная служба поддержки при запуске устройства.
    
### &emsp;Compile from source
 &emsp;&nbsp;- install <a href="https://git-scm.com/downloads" target="_blank">git</a> and <a href="https://doc.qt.io/qt-6/get-and-install-qt.html" target="_blank">Qt</a> (v.6.7.3 and v.5.15.2, Qt Creator v.14.0.1);
 <br>&emsp;&nbsp;- clone <a href="https://github.com/In-spectrum/FaNAT" target="_blank">the FaNAT repository</a> and enter into the folder;
 <br>&emsp;&nbsp;- open file *.pro in the Qt Creator;
 <br>&emsp;&nbsp;- run the project;

### &emsp;[Exemples](#exemples-1)

### FaNAT-client-fv
**Фул-версия.**<br>
_&ensp;&nbsp;*требуется установка дополнительного ПО_

#### **Available:**
- поиск и управление устройствами в сети;
- захват, трансляция, просмотр рабочего стола;
- отправка сигналов мышки и клавиатуры;
- эмуляцию сигналов мышки и клавиатуры;
- отправка, выполнение инструкций в командной строке на управляемом устройстве и получение результата от него;
- обмен файлами;
- receives/sends clipboard;
- настройка качества видеопотока;  
#### **Install**
##### &emsp;Windows:
- установите GStreamer - [GStreamer for Windows](#gstreamer-for-windows);
- загрузите <a href="https://github.com/In-spectrum/FaNAT/releases" target="_blank">архив приложения</a> и разархивируйте его. Запустите **_FaNATClient.ехе_**

##### &emsp;Ubuntu:
- для отображения интерфейса и эмуляции сигналов клавиатуры:
```
#sudo apt-get install '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev -y
```
- дополнительные плагины GStreamer:
```
#sudo apt-get install gstreamer1.0-plugins-ugly gstreamer1.0-plugins-bad gstreamer1.0-rtsp -y
```
- загрузите <a href="https://github.com/In-spectrum/FaNAT/releases" target="_blank">архив приложения</a>. В Command Line запустите **_./FaNATClient.sh_**
  
### **FaNAT-client-lite**
**C пользовательским интерфейсом.**<br>
_&ensp;&nbsp;*уменьшен функционал_
<br>_&ensp;&nbsp;*требуется незначительная установка дополнительного ПО_

#### **Available:**
- поиск и управление устройствами в сети;
- просмотр рабочего стола ( **только RTSP-поток** );
- отправка сигналов мышки и клавиатуры;
- отправка, выполнение инструкций в командной строке на управляемом устройстве и получение результата от него;
- обмен файлами;
- receives clipboard;
- настройка качества видеопотока;
#### **Unavailable:**
- захват, трансляцию рабочего стола;
- просмотр RTMP-потока;
- эмуляция сигналов мышки и клавиатуры;
- sends clipboard;
- в Windows, просмотр RTMP-потока (используйте RTSP-сервер).  
#### **Install**
##### &emsp;Windows:
- наличие установленного кодека для просмотра видео;
- загрузите <a href="https://github.com/In-spectrum/FaNAT/releases" target="_blank">архив приложения</a> и разархивируйте его. Запустите **_FaNATClient.ехе_**

##### &emsp;Ubuntu:
- для отображения интерфейса и эмуляции сигналов клавиатуры:
```
#sudo apt-get install '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev -y
```
- дополнительные плагины GStreamer:
```
#sudo apt-get install gstreamer1.0-libav gstreamer1.0-plugins-bad -y
```
- загрузите <a href="https://github.com/In-spectrum/FaNAT/releases" target="_blank">архив приложения</a>. В Command Line запустите **_./FaNATClient.sh_**

### **FaNAT-client-console-fv**
**Console application. 
<br>Для использования в ваших приложениях или как дополнительная служба поддержки при запуске устройства.**<br>
_&ensp;&nbsp;*требуется установка дополнительного ПО_

#### **Available:**
- захват, трансляцию рабочего стола;
- эмуляция сигналов мышки и клавиатуры;
- выполнение инструкций в командной строке на управляемом устройстве и отпрвка результатов;
- обмен файлами;
- receives/sends clipboard;
- запуск приложения с дополнительными параметрами;

#### **Unavailable:**
- интерфейс пользователя.
- поиск и управление устройствами в сети;
- отправка сигналов мышки и клавиатуры;
- отображение видеопотока;
  
#### **Install** 
##### &emsp;Windows:
- установите GStreamer - [GStreamer for Windows](#gstreamer-for-windows);
- загрузите <a href="https://github.com/In-spectrum/FaNAT/releases" target="_blank">архив приложения</a> и разархивируйте его. Запустите **_FaNATClient.ехе_**

##### &emsp;Ubuntu:
- для эмуляции сигналов клавиатуры:
```
#sudo apt-get install '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev -y
```
- дополнительные плагины GStreamer:
```
#sudo apt-get install gstreamer1.0-plugins-ugly gstreamer1.0-plugins-bad gstreamer1.0-rtsp -y
```
- загрузите <a href="https://github.com/In-spectrum/FaNAT/releases" target="_blank">архив приложения</a>. В Command Line запустите **_./FaNATClient.sh_**

#### **Properties**
 **-spas** - set server password (по умолчанию 1111); _**./FaNATClient.sh -spas 2227**_
<br> **-sip** - set port for connect to server;  _**./FaNATClient.sh -sip 137.34.15.27**_
<br> **-ptcp** - set port for connect to server;  _**./FaNATClient.sh -ptcp 1135**_
<br> **-prtsp** - set port for публикации видео-потока; _**./FaNATClient.sh -prtsp 8554**_
<br> **-prtmp** - set port for публикации видео-потока;  _**./FaNATClient.sh -prtmp 1927**_
<br> **-log** - set ваш логин;  _**./FaNATClient.sh -log user1**_
<br> **-pas** - set ваш пароль;  _**./FaNATClient.sh -pas user1111**_
<br> **-ds** - использовать другой доступный сервер;  _**./FaNATClient.sh -ds 1**_ [Use another available server](#use-another-available-server)
<br> **-kds** - использовать другой доступный сервер c ключом доступа;  _**./FaNATClient.sh -ds 1 -kds ExxxRt17j**_ [Use another available server](#use-another-available-server)

### **FaNAT-client-console-lite**
**Console application. Для использования в ваших приложениях или как дополнительная служба поддержки при запуске устройства.**<br>
_&ensp;&nbsp;*уменьшен функционал_
_<br>&ensp;&nbsp;*не требуется установка дополнительного ПО_

#### **Available:**
- выполнение инструкций в командной строке на управляемом устройстве и отпрвка результатов;
- обмен файлами;
- запуск приложения с дополнительными параметрами;

#### **Unavailable:**
- интерфейс пользователя.
- поиск и управление устройствами в сети;
- отправка сигналов мышки и клавиатуры; 
- эмуляция сигналов мышки и клавиатуры;
- receives/sends clipboard;
- захват, трансляцию рабочего стола;
- отображение видеопотока;

  
#### **Install** 
##### &emsp;Windows:
- загрузите <a href="https://github.com/In-spectrum/FaNAT/releases" target="_blank">архив приложения</a> и разархивируйте его. Запустите **_FaNATClient.ехе_**

##### &emsp;Ubuntu:
- загрузите <a href="https://github.com/In-spectrum/FaNAT/releases" target="_blank">архив приложения</a>. В Command Line запустите **_./FaNATClient.sh_**

#### **Properties**
 **-spas** - set server password (по умолчанию 1111); _**./FaNATClient.sh -spas 2227**_
<br> **-sip** - set port for connect to server;  _**./FaNATClient.sh -sip 137.34.15.27**_
<br> **-ptcp** - set port for connect to server;  _**./FaNATClient.sh -ptcp 1135**_
<br> **-log** - set ваш логин;  _**./FaNATClient.sh -log user1**_
<br> **-pas** - set ваш пароль;  _**./FaNATClient.sh -pas user1111**_
<br> **-ds** - использовать другой доступный сервер;  _**./FaNATClient.sh -ds 1**_ [Use another available server](#use-another-available-server)
<br> **-kds** - использовать другой доступный сервер c ключом доступа;  _**./FaNATClient.sh -ds 1 -kds ExxxRt17j**_ [Use another available server](#use-another-available-server)

## Exemples

### File sharing
- используйте FaNATClient - Menu - File copy.
- вставте полный путь к файлу. Exemple: /home/user/folderKey/ssh-key-2020-11-09.key
  
### Use Command line
- use sudo - '**sudo 1111 ping localhost' or 'sudo password apt-get install App**'. 1111 - user password;
- use ssh with password - '**sshpass -p 1111 ssh user_server@0.0.0.0**'. 1111 - user_server password;
- текущий каталог - '**cd**'. По умолчанию - home path;
- перейти в каталог - '**cd ..**' или '**cd home/user_name/Video**' или '**cd D:/**';
- вернуться в каталог "home path" - '**cd \~**';
- список каталогов и файлов - '**ls**'. It's custom function;
- список каталогов и файлов включая скрытые - '**ls -a**'. It's custom function;

### Reverse SSH Tunneling
**Позволяет запустить ssh-клиент с обратным тунелем и получить доступ к устройству (_dev_target_).**
#### &ensp;&nbsp;Server requirements
- сервер _**user_server@0.0.0.0**_ должен иметь **белый IP**;
- на сервере _**user_server@0.0.0.0**_ должен быть доступен порт _**6744**_;

#### &emsp;Создаем обратный ssh-тоннель
&emsp;Используя FaNATClient - Menu - Comand line - отправляем команду на управляемое устройсво _**dev_target**_
~~~
# sshpass -p password_user_server ssh -o StrictHostKeyChecking=accept-new user_server@0.0.0.0 -R 6744:localhost:22
~~~
&emsp;***password_user_server** - _it's password of user_server_
<br><br>&emsp;... или отправляем команду с ключем
~~~
# ssh  -i /home/dev_target/folderKey/ssh-key-2020-11-09.key user_server@0.0.0.0 -R 6744:localhost:22
~~~

<br>&emsp;С сервера _**user_server@0.0.0.0**_ подключаемся к устройству _**dev_target**_
~~~
# ssh dev_target@localhost -p 6744
~~~
&emsp;&nbsp;_- enter password of **dev_target**._

### Use another available server
**Позволяет, <ins>ВРЕМЕННО</ins>, использовать уже настроенный сервер _158.101.219.244_**
<br>
<br>Время использования стороннего сервера (_без ключа доступа_) составляет **10мин**. Далее, сервер недоступен на протяжении **30мин**. Далее, снова, можна пользоваться сервером на протяжении **10мин**. И так далее...
<br>Ключ доступа дает возможность использовать сторонний сервер дольше ( _до определенной даты - время оговаривается дополнительно_ ).
<br>
<br>&emsp;**- консольная версия приложения:**
~~~
# ./FaNATClient.sh -sip 158.101.219.244 -log user1 -pas user1111 -ds 1 -kds ExxxRt37j2
~~~
&emsp;**- версии приложения с интерфейсом пользователя:** выберите Menu -> Server -> **use the developer server** -> введите **158.101.219.244** -> _( не обязательно: введите **key** )_ -> New connect;

### Commands for the server
- установка времени для [отключения клиентов с низкой активность](#properties-2): значения от 30 до 300сек.
<br>( _0 - деактивирует функцию на сервере_ );
  
## Installing additional software
### GStreamer for Windows
- загрузите установочные файлы: <a href="https://gstreamer.freedesktop.org/data/pkg/windows/1.20.7/mingw/" target="_blank">gstreamer-1.0-mingw-x86_64-1.20.7.msi и gstreamer-1.0-devel-mingw-x86_64-1.20.7.msi</a>;
- запустите их с правами администратора;
- при установке **выберите все плагины**;
- add 'C:\gstreamer\1.0\mingw_x86_64\bin\' to **PATH** system;

## FaNAT-server
### Functions
- поиск доступных устройств и обмен данными между ними;

### Особенности
- сервер дожен быть онлайн (ведется статистика о количестве работающих FaNAT-server);
- сервер для использования, в том числе в локальных сетях, без сбора статистик - находится в разработке;
   
### Install
 - загрузите <a href="https://github.com/In-spectrum/FaNAT/releases" target="_blank">архив приложения</a> соответствующий вашей ОС и разархивируйте;
 - запустите сервер с входними параметрами:
<br>**_./FaNATServer.sh -pas 2227 -p 1675 -la 60_** - для Ubuntu
<br>**_FaNATServer.ехе -pas 2227 -p 1675 -la 60_** - для Windows;

### Properties
**-pas** - set server password (по умолчанию 1111); _**./FaNATServer.sh -pas 2227**_<br>
**-p** - set listen port; _**./FaNATServer.sh -p 1675**_<br>
**-la** - время для отключения клиентов с низкой активность; _**./FaNATServer.sh -la 60**_<br>
_<h style="font-size:8; ">&emsp;&emsp;&emsp;*если клиент подключён и не используется - он будет отключен от сервера через 60сек.<br>
&emsp;&emsp;&emsp;&ensp;Через 30сек. клиент переподключится к серверу для повторной идентификации в сети.</h>_

### Example script to check FaNAT-server

~~~
#!/bin/bash

sleep 10

a_pFNS_tcp=1137 #for FaNatServer
a_pRTSP=8554 #for RTSP
a_pRTMP=1927 #for RTMP
a_pSSH=6744 #for SSH

# opening of ports
sudo systemctl start firewalld
sudo firewall-cmd --zone=public --add-port=${a_pSSH}/tcp --permanent #for SSH
sudo firewall-cmd --zone=public --add-port=${a_pRTSP}/tcp --permanent #for RTSP
sudo firewall-cmd --zone=public --add-port=${a_pRTMP}/tcp --permanent #for RTMP
sudo firewall-cmd --zone=public --add-port=${a_pFNS_tcp}/tcp --permanent #for FaNatServer
sudo firewall-cmd --reload

while true
do
    # FaNatServer check
    if pgrep "FaNatServer" > /dev/null; then
        echo "FaNatServer STARTED!"
    else
        echo "FaNatServer NOT STARTED"

        cd /home/user/FaNatServer
        ./FaNatServer.sh -p ${a_pFNS_tcp} &
    fi

    # Mediamtx check
    if pgrep "mediamtx" > /dev/null; then
        echo "RTSP-server STARTED!"
    else
        echo "RTSP-server NOT STARTED"

        cd /home/user/Mediamtx
        MTX_RTSPADDRESS=":${a_pRTSP}" MTX_RTMPADDRESS=":${a_pRTMP}" MTX_PROTOCOLS="tcp,udp" ./mediamtx &
    fi

    sleep 2
done
~~~

## Video-server
 _&ensp;&nbsp;*используется сторонне ПО_<br>
 
### Функции
Публикация и трансляция видеопотока рабочего стола управляемого устройства.

### Пример
- <a href="https://github.com/bluenviron/mediamtx/tree/main" target="_blank">mediamtx</a> - доступно RTSP, RTMP.... протоколы;
- <a href="https://www.digitalocean.com/community/tutorials/how-to-set-up-a-video-streaming-server-using-nginx-rtmp-on-ubuntu-20-04" target="_blank">Nginx-RTMP</a> - доступно RTMP-протокол;
- или другой RTSP, RTMP сервер;

### Особенности
- установка видео-сервера не нужна, если на управляемом устройстве используется версия клиента
<br>[**FaNAT-client-lite**](#fanat-client-lite) или [**FaNAT-client-console-lite**](#fanat-client-console-lite);

## License
Увесь код у цьому репозиторії випущено згідно з <a href="https://github.com/In-spectrum/FaNAT/blob/main/LICENSE">ліцензією MIT</a>. 
<br>Архіви додатків та зкомпільовані двійкові файли використовують деякі сторонні залежності:
- Qt - the primary <a href="https://www.qt.io/licensing/open-source-lgpl-obligations#" target="_blank">open-source license</a> is the GNU Lesser General Public License v.3 <a href="https://www.gnu.org/licenses/lgpl-3.0.txt" target="_blank">“LGPL v3”</a>;
- GStreamer - <a href="https://github.com/GStreamer/gstreamer/blob/main/LICENSE" target="_blank">licensed under the LGPL v2.1;
