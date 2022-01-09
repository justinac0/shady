--------------------------------------------------------------------------------
-- Workspace Configuration --
-----------------------------
workspace "shady-workspace"
location  ""

configurations {
   "development",
   "production"
}

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
targetdir  "./"-- "build\\%{cfg.buildcfg}"

files {
   "source/*.h",
   "source/*.c",
  
   "thirdparty/glad/src/*.c",
   "thirdparty/glfw/src/*.h",
   "thirdparty/glfw/src/*.c",
}

includedirs("thirdparty/glad/include/")
includedirs("thirdparty/glfw/include")

--------------------------------------------------------------------------------
-- Setup Dependences --
-----------------------

if os.target() == "windows" then
   -- ignore msvc defaults
   ignoredefaultlibraries { "MSVCRT" }

   links { "opengl32", "glfw3", 'gdi32', "winmm" }
else
   links { "glfw", 'dl' }
end

--------------------------------------------------------------------------------
-- Build Configurations --
--------------------------

filter   "configurations:development"
defines  "DEBUG"
symbols  "On"
optimize "Debug"

filter   "configurations:production"
defines  "NDEBUG"
symbols  "On"
optimize "Speed"

--------------------------------------------------------------------------------
