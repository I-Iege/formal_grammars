from conans import ConanFile, CMake
#from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout


class Package(ConanFile):

    settings = 'os', 'build_type'

    generators = "cmake", "cmake_paths", "cmake_find_package"
    
    def requirements(self):
        self.requires("qt/6.4.2")
    
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
