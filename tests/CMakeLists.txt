cmake_minimum_required(VERSION 3.18)
project(IQJSSmoke LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ROOT "${CMAKE_CURRENT_LIST_DIR}/..")
set(QJS "${ROOT}/third_party/quickjs-ng")

add_library(smoke_quickjs STATIC
  "${QJS}/dtoa.c"
  "${QJS}/libregexp.c"
  "${QJS}/libunicode.c"
  "${QJS}/quickjs.c"
)
target_include_directories(smoke_quickjs PUBLIC "${QJS}")
target_compile_definitions(smoke_quickjs PRIVATE
  QUICKJS_NG_BUILD _GNU_SOURCE
  $<$<BOOL:${WIN32}>:WIN32_LEAN_AND_MEAN;_WIN32_WINNT=0x0601;_CRT_SECURE_NO_WARNINGS>
)
if(MSVC)
  target_compile_options(smoke_quickjs PRIVATE /experimental:c11atomics /wd4200 /wd4244 /wd4267 /wd4996)
endif()

file(GLOB NATIVE_SOURCES CONFIGURE_DEPENDS "${ROOT}/src/native/*.cpp")
add_executable(iqjs_smoke
  iqjs_smoke.cpp
  ${NATIVE_SOURCES}
  "${ROOT}/code_gen/core/GMExtUtils.cpp"
  "${ROOT}/code_gen/core/GMExtWire.cpp"
)
target_include_directories(iqjs_smoke PRIVATE
  "${ROOT}/src"
  "${ROOT}/src/native"
  "${ROOT}/code_gen"
  "${ROOT}/code_gen/core"
  "${QJS}"
)
target_compile_definitions(iqjs_smoke PRIVATE OS_WINDOWS EXTGEN_HAS_JNI=0 _CRT_SECURE_NO_WARNINGS WIN32_LEAN_AND_MEAN NOMINMAX)
if(MSVC)
  target_compile_options(iqjs_smoke PRIVATE /W4 /utf-8 /wd4576 /wd4819)
endif()
target_link_libraries(iqjs_smoke PRIVATE smoke_quickjs)

add_test(NAME iqjs_smoke COMMAND iqjs_smoke)
