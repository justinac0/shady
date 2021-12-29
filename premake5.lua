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
cdialect "C89"

architecture "x86_64"

objdir "objects"

targetname "shady"
targetdir  "./"-- "build\\%{cfg.buildcfg}"

files {
   "source/*.h",
   "source/*.c",
  
   "thirdparty/glad/*.c"
}

includedirs("thirdparty/glad/")

--------------------------------------------------------------------------------
-- Setup Dependences --
-----------------------

if os.target() == "windows" then
   -- ignore msvc defaults
   ignoredefaultlibraries { "MSVCRT" }

   local GLFW_INCLUDES = "thirdparty/glfw-3.3.6.bin.WIN64/include"
   local GLFW_LIBS     = "thirdparty/glfw-3.3.6.bin.WIN64/lib-vc2019"

   includedirs(GLFW_INCLUDES)

   libdirs { GLFW_LIBS }

   filter "kind:not StaticLib"
   links { "opengl32", "glfw3", 'gdi32', "winmm" }
else
   filter "kind:not StaticLib"
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
