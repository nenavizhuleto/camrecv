cmake_minimum_required(VERSION 3.22.1)

project(camrecv)

# find_package(PkgConfig REQUIRED)
# pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
#     libavfilter
#     libavformat
#     libavcodec
#     libswresample
#     libswscale
#     libavutil
# )

add_executable(${PROJECT_NAME} src/main.c)

# target_link_libraries(${PROJECT_NAME}
# 	PkgConfig::LIBAV
# )
