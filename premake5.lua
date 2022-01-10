--------------------------------------------------------------------------------
-- Workspace Configuration --
-----------------------------
workspace "shady-workspace"
location  ""

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
language "C"
cdialect "C99"

architecture "x86_64"

objdir "objects"

targetname "shady"
targetdir  "build/%{cfg.buildcfg}"

files {
   "source/*.h",
   "source/*.c",
  
   "thirdparty/glad/src/*.c"
}

includedirs{"thirdparty/", "thirdparty/glad/include/", "thirdparty/glfw/include"}

--------------------------------------------------------------------------------
-- Setup Dependences --
-----------------------

links { "GLFW" }
filter "system:linux"
   links { "dl", "pthread", "m", "X11" }

   defines { "_X11"}

filter "system:windows"
   ignoredefaultlibraries { "MSVCRT" }
   defines { "_WINDOWS"}

include "thirdparty/glfw.lua"