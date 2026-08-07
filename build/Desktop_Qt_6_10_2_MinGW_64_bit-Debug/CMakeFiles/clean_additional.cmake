# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appEQ_Art_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appEQ_Art_autogen.dir\\ParseCache.txt"
  "appEQ_Art_autogen"
  )
endif()
