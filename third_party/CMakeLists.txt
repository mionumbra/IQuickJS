cmake_minimum_required(VERSION 3.18)

set(_QUICKJS_DIR "${CMAKE_CURRENT_LIST_DIR}/quickjs-ng")

if(NOT EXISTS "${_QUICKJS_DIR}/quickjs.c")
  message(FATAL_ERROR "[third_party] quickjs-ng source not found: ${_QUICKJS_DIR}")
endif()

# Match quickjs-ng's official core library target without emitting its CLI,
# test runners, examples, or quickjs-libc OS module.
add_library(ext_quickjs STATIC
  "${_QUICKJS_DIR}/dtoa.c"
  "${_QUICKJS_DIR}/libregexp.c"
  "${_QUICKJS_DIR}/libunicode.c"
  "${_QUICKJS_DIR}/quickjs.c"
)

set_target_properties(ext_quickjs PROPERTIES
  C_STANDARD 11
  C_STANDARD_REQUIRED ON
  C_EXTENSIONS ON
  POSITION_INDEPENDENT_CODE ON
)

target_include_directories(ext_quickjs PUBLIC "${_QUICKJS_DIR}")
target_compile_definitions(ext_quickjs PRIVATE
  QUICKJS_NG_BUILD
  _GNU_SOURCE
)

if(WIN32)
  target_compile_definitions(ext_quickjs PRIVATE
    WIN32_LEAN_AND_MEAN
    _WIN32_WINNT=0x0601
    _CRT_SECURE_NO_WARNINGS
  )
endif()

if(MSVC)
  # These are the MSVC options used by quickjs-ng's official CMake build.
  target_compile_options(ext_quickjs PRIVATE
    /experimental:c11atomics
    /wd4018 /wd4061 /wd4100 /wd4200 /wd4242 /wd4244 /wd4245
    /wd4267 /wd4388 /wd4389 /wd4456 /wd4457 /wd4710 /wd4711
    /wd4820 /wd4996 /wd5045
  )
else()
  target_compile_options(ext_quickjs PRIVATE
    -Wno-implicit-fallthrough
    -Wno-sign-compare
    -Wno-unused-parameter
    -Wno-unused-but-set-variable
  )
endif()

add_library(ext_third_party INTERFACE)
target_link_libraries(ext_third_party INTERFACE ext_quickjs)
target_include_directories(ext_third_party INTERFACE "${_QUICKJS_DIR}")

message(STATUS "[third_party] quickjs-ng core: ${_QUICKJS_DIR}")
