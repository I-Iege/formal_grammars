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
 conan install . --build missing -pr:a vs2022-debug -of=build/vs2022-debug
 ````
###  Linux
First it is recommended to run the install step with admin rights to be able to install external dependencies
Depending on your gcc version this can be either gcc-12-debug or gcc-14-debug

````
conan install . --build missing -pr:a gcc-12-debug -of=build/gcc-12-debug
 ````
after that it is enough to run:

````
conan install . --build missing -pr:a gcc-12-debug -of build/gcc-12-debug
 ````
## 3. Build
### Windows
````
cmake --preset vs2022-debug
cmake --build --preset vs2022-debug
````
### Linux
````
cmake --preset gcc-12-debug
cmake --build --preset gcc-12-debug
````
## 4. Test
### Windows
````
ctest --preset vs2022-debug
````
### Linux
````
ctest --preset gcc-12-debug
````
