# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles/speckle_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/speckle_autogen.dir/ParseCache.txt"
  "speckle_autogen"
  )
endif()
