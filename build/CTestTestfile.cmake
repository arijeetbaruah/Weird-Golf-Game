# CMake generated Testfile for 
# Source directory: C:/Users/b6038386/Documents/GitHub/weird-golf-game
# Build directory: C:/Users/b6038386/Documents/GitHub/weird-golf-game/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(test1 "test1.exe")
  set_tests_properties(test1 PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/b6038386/Documents/GitHub/weird-golf-game/CMakeLists.txt;84;add_test;C:/Users/b6038386/Documents/GitHub/weird-golf-game/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(test1 "test1.exe")
  set_tests_properties(test1 PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/b6038386/Documents/GitHub/weird-golf-game/CMakeLists.txt;84;add_test;C:/Users/b6038386/Documents/GitHub/weird-golf-game/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(test1 "test1.exe")
  set_tests_properties(test1 PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/b6038386/Documents/GitHub/weird-golf-game/CMakeLists.txt;84;add_test;C:/Users/b6038386/Documents/GitHub/weird-golf-game/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(test1 "test1.exe")
  set_tests_properties(test1 PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/b6038386/Documents/GitHub/weird-golf-game/CMakeLists.txt;84;add_test;C:/Users/b6038386/Documents/GitHub/weird-golf-game/CMakeLists.txt;0;")
else()
  add_test(test1 NOT_AVAILABLE)
endif()
subdirs("submodules/spdlog")
subdirs("submodules/enet")
