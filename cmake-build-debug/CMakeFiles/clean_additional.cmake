# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ICMA_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ICMA_autogen.dir\\ParseCache.txt"
  "ICMA_autogen"
  )
endif()
