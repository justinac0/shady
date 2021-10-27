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

architecture "x86_64"

-- objdir "build"

targetname "shady"
targetdir  ""-- "bin\\%{cfg.buildcfg}"

files {
   "*.h",
   "*.c",
  
   "deps\\glad\\*.c"
}

--------------------------------------------------------------------------------
-- Setup Dependences --
-----------------------

local GLFW_INCLUDES = "deps\\glfw-3.3.4\\include"
local GLFW_LIBS     = "deps\\glfw-3.3.4\\lib-vc2019"

function include_glfw()
   includedirs(GLFW_INCLUDES)
end

function link_glfw()
   libdirs { GLFW_LIBS }

   filter "kind:not StaticLib"
   links { "opengl32", "glfw3", "gdi32", "winmm" }
end

includedirs("deps\\glad\\")

include_glfw()
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
