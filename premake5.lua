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
  
   "source/glad/*.c"
}

--------------------------------------------------------------------------------
-- Setup Dependences --
-----------------------

function link_glfw()
   filter "kind:not StaticLib"
   links { "glfw", 'dl' }
end

includedirs("source/glad/")

link_glfw()

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
