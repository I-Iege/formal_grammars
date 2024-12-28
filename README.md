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
Install OS dependencies
sudo apt install libxcomposite-dev libxcursor-dev libxdamage-dev libxfixes-dev libxi-dev libxinerama-dev libxkbfile-dev libxmuu-dev libxrandr-dev libxres-dev libxtst-dev libxv-dev libxxf86vm-dev libxcb-glx0-dev libxcb-render-util0-dev libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-shape0-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-xinerama0-dev libxcb-dri3-dev libxcb-cursor-dev libxcb-dri2-0-dev libxcb-dri3-dev libxcb-present-dev libxcb-composite0-dev libxcb-ewmh-dev libxcb-res0-dev libx11-dev libx11-xcb-dev libfontenc-dev libice-dev libsm-dev  libxau-dev libxaw7-dev libgl-dev
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
