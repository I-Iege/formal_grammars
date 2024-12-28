from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps

class Package(ConanFile):

    settings = 'os', 'build_type', 'compiler'
    generators = 'CMakeDeps'

    def requirements(self):
        self.requires("qt/6.7.0")
        self.test_requires("gtest/1.13.0")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
