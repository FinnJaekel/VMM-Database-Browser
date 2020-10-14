# VMM-Database-Browser
This is an analysis tool to evaluate the results of VMM-Hybrid testing using the VMM Slow control (https://gitlab.cern.ch/rd51-slow-control/vmmsc). 

## Requirements
* [Qt 5.12]
* C++11 (gcc>=4.7)

## Installation
To install follow the following steps:

## Download 
```
git clone https://github.com/FinnJaekel/VMM-Database-Browser.git
```

## Compile Software
Change to build folder
```
cd VMM-Database-Browser/build
```
Run qmake:
```
qmake VMM_database_browser.pro
```
Run make
```
make
```
To use the software then execute:
```
./VMM_database_browser
```

## Test software
When starting the software, the program should automatically download a database file called testdb.db. If this is not the case, and errors concerning ssl (check terminal), openssl drivers might need to be installed. Check the manual https://www.howtoforge.com/tutorial/how-to-install-openssl-from-source-on-linux/ to install these drivers. 
