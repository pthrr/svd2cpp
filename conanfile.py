import shutil
import os
import json

from conan import ConanFile, tools
from conan.tools.cmake import CMake, CMakeToolchain


class Project(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = ["catch2/3.4.0", "spdlog/1.12.0", "tinyxml2/9.0.0", "cxxopts/3.1.1"]
    generators = "CMakeDeps"

    def generate(self) -> None:
        ninja_available: bool = shutil.which("ninja") is not None
        generator = "Ninja" if ninja_available else None
        tc = CMakeToolchain(self, generator=generator)
        tc.generate()
        self.patch_cmake_presets()

    def patch_cmake_presets(self):
        cmake_presets_path = os.path.join(self.recipe_folder, "CMakePresets.json")
        presets = json.dumps(
            {
                "version": 6,
                "include": [
                    f"build/{self.settings.build_type}/generators/CMakePresets.json"
                ],
            }
        )

        with open(cmake_presets_path, "w") as presets_file:
            presets_file.write(presets)

    def layout(self) -> None:
        self.folders.source = "src"
        self.folders.build = f"build/{self.settings.build_type}"
        self.folders.generators = f"build/{self.settings.build_type}/generators"

    def build(self) -> None:
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
