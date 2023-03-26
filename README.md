# Formal Languages

## 1. Prerequisites

### install conan
````
pip install conan==1.59
````

## 2. Download dependencies

###  Windows
````
conan install . --build missing -if build/vs2022-debug
 ````
###  Linux
````
conan install . --build missing -if build/gcc-debug
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
