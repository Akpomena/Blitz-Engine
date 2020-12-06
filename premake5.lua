workspace "BlitzEngine"
    configurations { "Debug", "Release" }
    architecture "x64"
    cppdialect "c++17"
    startproject "Sandbox"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

project "Blitz Engine"
    targetname "BlitzEngine"
    kind "SharedLib" 
    language "C++"
    location "Blitz Engine"
    objdir "bin-int\\%{prj.name}\\%{cfg.architecture}\\%{cfg.buildcfg}\\"
    targetdir "bin\\%{prj.name}\\%{cfg.architecture}\\%{cfg.buildcfg}\\"
    files {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h"
    }
    defines {
        "BLITZENGINE__EXPORTS"
    }
    postbuildcommands {
        "xcopy /Y \"..\\bin\\%{prj.name}\\%{cfg.architecture}\\%{cfg.buildcfg}\\%{cfg.targetname}%{cfg.targetextension}\" \"..\\bin\\Sandbox\\%{cfg.architecture}\\%{cfg.buildcfg}\\\""
    }
    includedirs {
        "%{prj.name}/vendor/spdlog/include/"
    }

project "Sandbox"
    kind "ConsoleApp" 
    language "C++"
    location "Sandbox"
    objdir "bin-int/%{prj.name}/%{cfg.architecture}/%{cfg.buildcfg}/"
    targetdir "bin/%{prj.name}/%{cfg.architecture}/%{cfg.buildcfg}/"
    files {
    "%{prj.name}/src/**.cpp",
    "%{prj.name}/src/**.h"
    }
    links {"Blitz Engine"}
    includedirs {
        "Blitz Engine/src"
    }