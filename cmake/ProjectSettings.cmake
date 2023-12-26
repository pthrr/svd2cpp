message(STATUS "Build type is: ${CMAKE_BUILD_TYPE}")

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(CCACHE_PROGRAM ccache)

if(CCACHE_PROGRAM)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
  message(STATUS "Using ccache")
endif()

find_program(MOLD_LINKER mold)
find_program(GOLD_LINKER gold)

if(MOLD_LINKER)
  add_link_options("-fuse-ld=mold")
  message(STATUS "Using mold as linker")
elseif(GOLD_LINKER)
  add_link_options("-fuse-ld=gold")
  message(STATUS "Using gold as linker")
else()
  message(STATUS "Default linker will be used")
endif()

add_compile_options(-Wall -Wextra -pedantic)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_options(-g3 -O0 -gsplit-dwarf)
else()
  add_compile_options(-O3 -DNDEBUG)
  add_link_options(-flto)
endif()
