workspace "Tic-Tac-Toe"
	location "premake-generated-files"
	configurations { "Debug", "Release" }

project "Tic-Tac-Toe"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++11"

	targetdir ("build/bin/%{prj.name}/%{cfg.longname}")
	objdir ("build/obj/%{prj.name}/%{cfg.longname}")

	files { "./include/*.hpp", "./src/*.cpp" }

	filter { "configurations:Debug" }
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release"
      		defines { "NDEBUG" }
      		optimize "On"
	
	filter {}

project "Tests"
	language "C++"
	cppdialect "C++11"
	kind "ConsoleApp"
	includedirs "./libs"

	files { "./tests/**", "./include/*.hpp", "./src/*.cpp" }
	removefiles "./src/Main.cpp"

	targetdir ("build/bin/%{prj.name}/%{cfg.longname}")
	objdir ("build/obj/%{prj.name}/%{cfg.longname}")
	
	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release"
      		defines "NDEBUG"
      		optimize "On"
	
	filter {}
