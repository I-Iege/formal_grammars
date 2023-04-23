# Formal Languages

## supported platforms

The code is tested in windows 10 and ubuntu 22.10

## 1. Prerequisites

### install conan
````
pip install conan==1.59
````

## 2. Download dependencies

### install profiles for conan
````
conan config install profiles -tf profiles
````

###  Windows
````
conan install . --build missing -pr vs2022-debug -if build/vs2022-debug
 ````
###  Linux
First it is recommended to run the install step with admin rights to be able to install external dependencies

````
sudo su
export NOT_ON_C3I=1
conan install . --build missing -pr gcc-debug -if build/gcc-debug -c  tools.system.package_manager:mode=install
 ````
after that it is enough to run:

````
export NOT_ON_C3I=1
conan install . --build missing -pr gcc-debug -if build/gcc-debug
 ````
## 3. Build
### Windows
````
cmake --preset vs2022-debug
cmake --build --preset vs2022-debug
````
### Linux
````
cmake --preset gcc-debug
cmake --build --preset gcc-debug
````
## 4. Test
### Windows
````
ctest --preset vs2022-debug
````
### Linux
````
ctest --preset gcc-debug
````
