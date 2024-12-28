from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps

#from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout


class Package(ConanFile):

    settings = 'os', 'build_type', 'compiler'
    generators = "cmake", "cmake_paths", "cmake_find_package"
    
    def requirements(self):
        self.tool_requires("qt/6.7.0")
        self.test_requires("gtest/1.13.0")
    
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
