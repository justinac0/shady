--------------------------------------------------------------------------------
-- Workspace Configuration --
-----------------------------
workspace "shady-workspace"
location  "./"

configurations {
   "development",
   "production"
}

flags { "MultiProcessorCompile" }

filter   "configurations:development"
   defines  "DEBUG"
   symbols  "On"
   optimize "Debug"

filter   "configurations:production"
   defines  "NDEBUG"
   symbols  "On"
   optimize "Speed"
   flags { "LinkTimeOptimization" }

--------------------------------------------------------------------------------
-- Project Configuration --
---------------------------
project  "shady"
kind     "ConsoleApp"
language "C++"
cppdialect "C++11"

architecture "x86_64"

objdir "objects"

targetname "shady"
targetdir  "build/%{cfg.buildcfg}"

files {
   "source/*.hpp",
   "source/*.cpp",
  
   "thirdparty/glad/src/*.c"
}

includedirs{"thirdparty/", "thirdparty/glad/include/", "thirdparty/glfw/include/", "thirdparty/imgui/","thirdparty/stb/"}

--------------------------------------------------------------------------------
-- Setup Dependences --
-----------------------

links { "GLFW", "imgui" }
filter "system:linux"
   links { "dl", "pthread", "m", "X11" }

   defines { "_X11"}

filter "system:windows"
   ignoredefaultlibraries { "MSVCRT" }
   defines { "_WINDOWS"}
   links { "opengl32", "gdi32", "GLFW" }

include "thirdparty/glfw.lua"
include "thirdparty/imgui.lua"
