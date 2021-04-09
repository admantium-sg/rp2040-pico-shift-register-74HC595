include(FetchContent)

FetchContent_Declare(
  cmocka
  GIT_REPOSITORY https://gitlab.com/cmocka/cmocka.git
  GIT_TAG        cmocka-1.1.5
  GIT_SHALLOW    1
)

set(BUILD_SHARED_LIBS ON)
set(WITH_STATIC_LIB ON)
set(WITH_EXAMPLES OFF)

FetchContent_MakeAvailable(cmocka)