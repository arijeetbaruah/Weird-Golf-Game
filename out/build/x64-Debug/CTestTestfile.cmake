# CMake generated Testfile for 
# Source directory: C:/Users/b6024306/source/Group Work/weird-golf-game
# Build directory: C:/Users/b6024306/source/Group Work/weird-golf-game/out/build/x64-Debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test1 "test1.exe")
set_tests_properties(test1 PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/b6024306/source/Group Work/weird-golf-game/CMakeLists.txt;113;add_test;C:/Users/b6024306/source/Group Work/weird-golf-game/CMakeLists.txt;0;")
add_test(test2 "test2.exe")
set_tests_properties(test2 PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/b6024306/source/Group Work/weird-golf-game/CMakeLists.txt;117;add_test;C:/Users/b6024306/source/Group Work/weird-golf-game/CMakeLists.txt;0;")
add_test(ComponentTest "ComponentTest.exe")
set_tests_properties(ComponentTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/b6024306/source/Group Work/weird-golf-game/CMakeLists.txt;121;add_Test;C:/Users/b6024306/source/Group Work/weird-golf-game/CMakeLists.txt;0;")
subdirs("submodules/spdlog")
subdirs("submodules/enet")
subdirs("externals/physx")
