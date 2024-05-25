-- this file is from https://github.com/gabrielmaneru/imgui-premake
-- under the MIT License
--
-- I have made some modifications to fit my use case.
-- 

project "ImGui"
	kind "StaticLib"
	language "C++"
	architecture "x86_64"

	targetdir "../build/%{cfg.buildcfg}"
	objdir "../objects/"

	includedirs { "imgui/", "glfw/include/" }

	files
	{
		"imgui/imconfig.h",
		"imgui/imgui.h",
		"imgui/imgui.cpp",
		"imgui/imgui_draw.cpp",
		"imgui/imgui_internal.h",
		"imgui/imgui_tables.cpp",
		"imgui/imgui_widgets.cpp",
		"imgui/imstb_rectpack.h",
		"imgui/imstb_textedit.h",
		"imgui/imstb_truetype.h",
		"imgui/backends/imgui_impl_opengl3.h",
		"imgui/backends/imgui_impl_opengl3.cpp",
		"imgui/backends/imgui_impl_opengl3_loader.h",
		"imgui/backends/imgui_impl_glfw.cpp",
		"imgui/backends/imgui_impl_glfw.h",
	}

	links { "GLFW" }
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"