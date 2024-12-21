<h1 align="center">
	<a href="https://github.com/In-spectrum/FaNAT" target="_blank">
		<img src="manual/images/baner.bmp" width="750" height="250">
	</a>
	<br>
	<a href="https://github.com/In-spectrum/FaNAT" target="_blank">
		System for remote access to devices
	</a>
</h1>

<br>

**Purpose**
* get remote access to devices located on a network where NAT is used;
* using a private (or other accessible) server for:
  * device management;
  * file sharing;
  * capture, broadcast and watch a desktop; 
* ssh-tunnel setup, device access using ssh-protocol;
 
**Application was tested** 
* Windows 10, Ubuntu 20.04.6;

**Planned**
* deployment on (Raspberry Pi, NVIDIA Jetson), macOS, Android ( [client-lite](#fanat-client-lite) );
* capture desktop in Linux using Wayland; 

## Table of contents

* [**FaNAT-client**](#fanat-client)
  * [Functions](#functions)
  * [Compile from source](#compile-from-source)
  * [Exemples](#exemples-1)
  	* [File sharing](#file-sharing)
  	* [Use Command line](#use-command-line)
	* [Reverse SSH Tunneling](#reverse-ssh-tunneling)
	* [Use another available server](#use-another-available-server)
	* [Commands for the server](#commands-for-the-server)
  * [**FaNAT-client-fv**](#fanat-client-fv)
	* [Available](#available)
	* [Install](#install)
  	  	* [Windows](#windows)
  	  	* [Ubuntu](#ubuntu)
  * [**FaNAT-client-lite**](#fanat-client-lite)
	* [Available](#available-1)
	* [Unavailable](#unavailable)
	* [Install](#install-1)
		* [Windows](#windows-1)
		* [Ubuntu](#ubuntu-1)
  * [**FaNAT-client-console-fv**](#fanat-client-console-fv)
	* [Available](#available-2)
	* [Unavailable](#unavailable-1)
	* [Install](#install-2)
		* [Windows](#windows-2)
		* [Ubuntu](#ubuntu-2)
	* [Properties](#properties)
  * [**FaNAT-client-console-lite**](#fanat-client-console-lite)
	* [Available](#available-3)
	* [Unavailable](#unavailable-2)
	* [Install](#install-3)
		* [Windows](#windows-3)
		* [Ubuntu](#ubuntu-3)
	* [Properties](#properties-1)
* [**Installing additional software**](#installing-additional-software)
   * [GStreamer for Windows](#gstreamer-for-windows)
* [**FaNAT-server**](#fanat-server)
  * [Functions](#functions-1)
  * [Features](#features)
  * [Properties](#properties-2)  * 
  * [Install](#install-4)
  * [Example script to check FaNATA-server](#example-script-to-check-fanat-server)
* [**Video-server**](#video-server)
  * [Functions](#functions-2)
  * [Exemple](#exemple)
  * [Features](#features-1)
* [**License**](#license)


## **FaNAT-client**
### &emsp;Functions  
  &emsp;&nbsp;- capture, broadcast, watch a desktop (RTSP, RTMP-protocol);
  <br>&emsp;&nbsp;- sending, emulating mouse and keyboard signals;
  <br>&emsp;&nbsp;- use command line on the controlled device. [Use Command line](#use-command-line);
  <br>&emsp;&nbsp;- ability to run an ssh-client with a reverse tunnel and access the device using the ssh-protocol.
  <br>&emsp;&nbsp;&ensp;&nbsp;[Reverse SSH Tunneling](#reverse-ssh-tunneling);
  <br>&emsp;&nbsp;- file copying. Files are saved in **Download** folder. [File sharing](#file-sharing);
  <br>&emsp;&nbsp;- exchange of clipboards;
  <br>&emsp;&nbsp;- console version for use in your applications or as an additional support service for your device.
    
### &emsp;Compile from source
 &emsp;&nbsp;- install <a href="https://git-scm.com/downloads" target="_blank">git</a> and <a href="https://doc.qt.io/qt-6/get-and-install-qt.html" target="_blank">Qt</a> (v.6.7.3 or v.5.15.2, Qt Creator v.14.0.1);
 <br>&emsp;&nbsp;- clone <a href="https://github.com/In-spectrum/FaNAT" target="_blank">the FaNAT repository</a> and go to the folder;
 <br>&emsp;&nbsp;- open file ***.pro** in the Qt Creator;
 <br>&emsp;&nbsp;- run the project;

### &emsp;[Exemples](#exemples-1)

### FaNAT-client-fv
**Full version.**<br>
_&ensp;&nbsp;*installation of additional software required_

#### **Available:**
- search and manage devices on the network;
- capture, broadcast, watch a desktop;
- sending mouse and keyboard signals;
- emulation of mouse and keyboard signals;
- sending, executing instructions in the command line on the controlled device and receiving the result from it;
- file sharing;
- receives/sends clipboard;
- setting the video stream quality;

#### **Install**
##### &emsp;Windows:
- GStreamer install - [GStreamer for Windows](#gstreamer-for-windows);
- download <a href="https://github.com/In-spectrum/FaNAT/releases" target="_blank">application archive</a> and unzip it. Run **_FaNATClient.ехе_**

##### &emsp;Ubuntu:
- for show user interface and emulate keyboard signals:
```
#sudo apt-get install '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev -y
```
- GStreamer plugins:
```
#sudo apt-get install gstreamer1.0-plugins-ugly gstreamer1.0-plugins-bad gstreamer1.0-rtsp -y
```
- download <a href="https://github.com/In-spectrum/FaNAT/releases" target="_blank">application archive</a> and unzip it. In the command line, run **_./FaNATClient.sh_**

### **FaNAT-client-lite**
**With user interface.**<br>
_&ensp;&nbsp;*reduced functionality_
<br>_&ensp;&nbsp;*lite installation of additional software required_
<br>_&ensp;&nbsp;***under testing - some devices (PC) do not show the video stream**_

#### **Available:**
- search and manage devices on the network;
- watch a desktop;
- sending mouse and keyboard signals;
- sending, executing instructions in the command line on the controlled device and receiving the result from it;
- file sharing;
- receives clipboard;
- setting the video stream quality;

#### **Unavailable:**
- capture, broadcast a desktop;;
- using RTMP-protocol (use RTSP-server);
- emulation of mouse and keyboard signals;
- sends clipboard;

#### **Install**
##### &emsp;Windows:
- codec installed for watch video;
- download <a href="https://github.com/In-spectrum/FaNAT/releases" target="_blank">application archive</a> and unzip it. Run **_FaNATClient.ехе_**

##### &emsp;Ubuntu:
- for show user interface and emulate keyboard signals:
```
#sudo apt-get install '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev -y
```
- GStreamer plugins:
```
#sudo apt-get install gstreamer1.0-libav gstreamer1.0-plugins-bad -y
```
- download <a href="https://github.com/In-spectrum/FaNAT/releases" target="_blank">application archive</a> and unzip it. In the command line, run **_./FaNATClient.sh_**

### **FaNAT-client-console-fv**
**Console application. 
<br>Use in your applications or as an additional support service for your device.**<br>
_&ensp;&nbsp;*installation of additional software required_

#### **Available:**
- capture, broadcast a desktop;
- emulation of mouse and keyboard signals;
- sending, executing instructions in the command line on the controlled device and receiving the result from it;
- file sharing;
- receives/sends clipboard;

#### **Unavailable:**
- user interface;
- search and manage devices on the network;
- sending mouse and keyboard signals;
- watch stream;
  
#### **Install** 
##### &emsp;Windows:
- GStreamer install - [GStreamer for Windows](#gstreamer-for-windows);
- download <a href="https://github.com/In-spectrum/FaNAT/releases" target="_blank">application archive</a> and unzip it. Run **_FaNATClient.ехе_**

##### &emsp;Ubuntu:
- for emulate keyboard signals:
```
#sudo apt-get install '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev -y
```
- GStreamer plugins:
```
#sudo apt-get install gstreamer1.0-plugins-ugly gstreamer1.0-plugins-bad gstreamer1.0-rtsp -y
```
- download <a href="https://github.com/In-spectrum/FaNAT/releases" target="_blank">application archive</a> and unzip it. In the command line, run **_./FaNATClient.sh_**

#### **Properties**
 **-spas** - set server password (default 1111); _**./FaNATClient.sh -spas 2227**_
<br> **-sip** - set IP for connect to server;  _**./FaNATClient.sh -sip 137.34.15.27**_
<br> **-ptcp** - set port for connect to server;  _**./FaNATClient.sh -ptcp 1135**_
<br> **-prtsp** - set port for broadcast video-stream; _**./FaNATClient.sh -prtsp 8554**_
<br> **-prtmp** - set port for broadcast video-stream;  _**./FaNATClient.sh -prtmp 1927**_
<br> **-log** - set your login;  _**./FaNATClient.sh -log user1**_
<br> **-pas** - set your password;  _**./FaNATClient.sh -pas user1111**_
<br> **-ds** - use another available server;  _**./FaNATClient.sh -ds 1**_ [Use another available server](#use-another-available-server)
<br> **-kds** - use another available server with an access key;  _**./FaNATClient.sh -ds 1 -kds ExxxRt17j**_ [Use another available server](#use-another-available-server)

### **FaNAT-client-console-lite**
**Console application. 
<br>Use in your applications or as an additional support service for your device.**<br>
_&ensp;&nbsp;*reduced functionality_
_<br>&ensp;&nbsp;*no additional software installation required_

#### **Available:**
- sending, executing instructions in the command line on the controlled device and receiving the result from it;
- file sharing;

#### **Unavailable:**
- user interface;
- search and manage devices on the network;
- sending mouse and keyboard signals;
- emulation of mouse and keyboard signals;
- receives/sends clipboard;
- capture, broadcast a desktop;
- watch stream;

#### **Install** 
##### &emsp;Windows:
- download <a href="https://github.com/In-spectrum/FaNAT/releases" target="_blank">application archive</a> and unzip it. Run **_FaNATClient.ехе_**

##### &emsp;Ubuntu:
- download <a href="https://github.com/In-spectrum/FaNAT/releases" target="_blank">application archive</a> and unzip it. In the command line, run **_./FaNATClient.sh_**

#### **Properties**
 **-spas** - set server password (default 1111); _**./FaNATClient.sh -spas 2227**_
<br> **-sip** - set IP for connect to server;  _**./FaNATClient.sh -sip 137.34.15.27**_
<br> **-ptcp** - set port for connect to server;  _**./FaNATClient.sh -ptcp 1135**_
<br> **-log** - set your login;  _**./FaNATClient.sh -log user1**_
<br> **-pas** - set your password;  _**./FaNATClient.sh -pas user1111**_
<br> **-ds** - use another available server;  _**./FaNATClient.sh -ds 1**_ [Use another available server](#use-another-available-server)
<br> **-kds** - use another available server with an access key;  _**./FaNATClient.sh -ds 1 -kds ExxxRt17j**_ [Use another available server](#use-another-available-server)

## Exemples

### File sharing
- use FaNAT-client - Menu - File copy;
- insert the full path to the file. Exemple: /home/user/folderKey/ssh-key-2020-11-09.key;
- click the button to copy the file;
  
### Use Command line
- use sudo - '**sudo 1111 ping localhost' or 'sudo password apt-get install App**'. 1111 - user password;
- use ssh with password - '**sshpass -p 1111 ssh user_server@0.0.0.0**'. 1111 - user_server password;
- current directory - '**cd**'. Default - "home path";
- go to directory - '**cd ..**' or '**cd home/user_name/Video**' or '**cd D:/**';
- return to directory "home path" - '**cd \~**';
- list of directories and files - '**ls**'. It's custom function;
- list of directories and files including hidden ones - '**ls -a**'. It's custom function;

### Reverse SSH Tunneling
**Allows you to run an ssh-client with a reverse tunnel and access the device (_dev_target_).**
#### &ensp;&nbsp;Server requirements
- server _**user_server@0.0.0.0**_ must have **white IP**;
- port _**6744**_ must be available on server _**user_server@0.0.0.0**_;

#### &emsp;Create a reverse ssh-tunnel
&emsp;Use FaNATClient - Menu - Comand line - send a command to the controlled device _**dev_target**_
~~~
# sshpass -p password_user_server ssh -o StrictHostKeyChecking=accept-new user_server@0.0.0.0 -R 6744:localhost:22
~~~
&emsp;***password_user_server** - _it's password of user_server_
<br><br>&emsp;... or send a command with a key
~~~
# ssh -i /home/dev_target/folderKey/ssh-key-2020-11-09.key user_server@0.0.0.0 -R 6744:localhost:22
~~~

<br>&emsp;Use server _**user_server@0.0.0.0**_ and connect to the device _**dev_target**_
~~~
# ssh dev_target@localhost -p 6744
~~~
&emsp;&nbsp;_- enter password of **dev_target**._

### Use another available server
**Allows you to  <ins>TEMPORARILY</ins>  use an already configured server _158.101.219.244_**
<br>
<br>The time of using a third-party server (_without an access key_) **10 min**. Next, the server is unavailable **30 min**. Next, again, you can use the server **10 min**. And so on...
<br>The access key allows you to use a third-party server longer (_until a specific date. Date is discussed additionally_).
<br>
<br>&emsp;**- console version of the application:**
~~~
# ./FaNATClient.sh -sip 158.101.219.244 -log user1 -pas user1111 -ds 1 -kds ExxxRt37j2
~~~
&emsp;**- versions of the application with user interface:** select Menu -> Server -> **use the developer server** -> enter **158.101.219.244** -> _( optional: enter **key** )_ -> New connect;

### Commands for the server
- set time for [disconnecting clients with low activity](#properties-2): values ​​from 30 to 300sec.
<br>( _0 - disables the function on the server_ );
  
## Installing additional software
### GStreamer for Windows
- download installation files: <a href="https://gstreamer.freedesktop.org/data/pkg/windows/1.20.7/mingw/" target="_blank">gstreamer-1.0-mingw-x86_64-1.20.7.msi и gstreamer-1.0-devel-mingw-x86_64-1.20.7.msi</a>;
- run with administrator rights;
- when installing **select all plugins**;
- add 'C:\gstreamer\1.0\mingw_x86_64\bin\' to **PATH** system;

## FaNAT-server
### Functions
- search for available devices and exchange data between them;

### Features
- the server must be online (statistics are kept on the number of working FaNAT-servers);
- server usage, including in local networks, without collecting statistics is under development;
   
### Properties
**-pas** - set server password (default 1111); _**./FaNATServer.sh -pas 2227**_<br>
**-p** - set listen port; _**./FaNATServer.sh -p 1675**_<br>
**-la** - time to disconnect clients with low activity; _**./FaNATServer.sh -la 60**_<br>
_<h style="font-size:8; ">&emsp;&emsp;&emsp;*if the client is connected and not in use, it will be disconnected from the server after 60sec.<br>
&emsp;&emsp;&emsp;&ensp;After 30sec the client will reconnect to the server to identification on the network.</h>_

### Install
 - download <a href="https://github.com/In-spectrum/FaNAT/releases" target="_blank">application archive</a> and unzip;
 - start the server with parameters:
<br>**_./FaNATServer.sh -pas 2227 -p 1675 -la 60_** - for Ubuntu
<br>**_FaNATServer.ехе -pas 2227 -p 1675 -la 60_** - for Windows;

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
 _&ensp;&nbsp;*used third-party software_<br>
 
### Functions
Publishing and broadcasting a video stream of a desktop.

### Exemple
- <a href="https://github.com/bluenviron/mediamtx/tree/main" target="_blank">mediamtx</a> - RTSP, RTMP and other protocols available;
- <a href="https://www.digitalocean.com/community/tutorials/how-to-set-up-a-video-streaming-server-using-nginx-rtmp-on-ubuntu-20-04" target="_blank">Nginx-RTMP</a> - RTMP protocol available;
- or other RTSP, RTMP server;

### Features
- if you are not using desktop capture/broadcast, then installing a **Video-server** is not required.

## License
All code in this repository is released under the <a href="https://github.com/In-spectrum/FaNAT/blob/main/LICENSE">MIT license</a>. 
<br>Application archives and compiled binaries make use of some third-party dependencies:
- Qt - the primary <a href="https://www.qt.io/licensing/open-source-lgpl-obligations#" target="_blank">open-source license</a> is the GNU Lesser General Public License v.3 <a href="https://www.gnu.org/licenses/lgpl-3.0.txt" target="_blank">“LGPL v3”</a>;
- GStreamer - <a href="https://github.com/GStreamer/gstreamer/blob/main/LICENSE" target="_blank">licensed under the LGPL v2.1;
