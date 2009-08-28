solution "esqlite3"
    configurations { "Debug", "Release" }
    project "esqlite3"
        kind "StaticLib"
        language "C++"
        files  { "src/**.cpp" }
        excludes { "src/main.cpp" }
        includedirs { "." }

