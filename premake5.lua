---@diagnostic disable: undefined-global
workspace("NewCppProject")
    configurations { "Debug", "Release" }
    architecture "x86_64"
    startproject "NewCppProject"

    flags { "MultiProcessorCompile" }
    
    filter "system:windows"
        buildoptions { "/utf-8" }
        
    filter "configurations:Debug"
        defines { "DEBUG" }
        optimize "Off"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
    
local outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project("Cpp14")
    location "code/cpp14"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++14"

    files {
        "code/cpp14/**.cpp",
        "code/cpp14/**.h",
        "code/cpp14/**.hpp"
    }

    includedirs {
        "code/cpp14",
        "code/cpp14/include",
        "code/cpp14/utils"
    }

    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
