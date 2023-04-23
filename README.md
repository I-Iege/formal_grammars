# Formal Languages

## 1. Prerequisites

### install conan
````
pip install conan==1.59
````

## 2. Download dependencies

###  Windows
````
conan install . --build missing -pr vs2022-debug -if build/vs2022-debug
 ````
###  Linux
````
pip install conan==1.59
export NOT_ON_C3I=1
conan install . --build missing -pr gcc-debug -if build/gcc-debug -c  tools.system.package_manager:mode=install
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
