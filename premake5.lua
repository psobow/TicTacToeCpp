workspace "Tic-Tac-Toe"
	location "Premake-generated-files"
	configurations { "Debug", "Release" }


project "Tic-Tac-Toe"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++11"

	targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")
	objdir ("Build/Obj/%{prj.name}/%{cfg.longname}")

	files { "./include/*.hpp", "./src/*.cpp" }

	filter { "configurations:Debug" }
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release"
      		defines { "NDEBUG" }
      		optimize "On"
	
	filter {}

project "Tests"
	kind "ConsoleApp"
	includedirs "./libs"

	files { "./tests/**", "./include/*.hpp", 
		"./src/BoardManager.cpp", 
		"./src/Coordinates.cpp",
		"./src/GameManager.cpp",  
		"./src/GameOptionsManager.cpp",
		"./src/MinMaxManager.cpp",
		"./src/MyStdIn.cpp" }


	targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")
	objdir ("Build/Obj/%{prj.name}/%{cfg.longname}")
	
	filter { "configurations:Debug" }
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release"
      		defines { "NDEBUG" }
      		optimize "On"
	
	filter {}

