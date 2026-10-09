cmake_minimum_required(VERSION 3.15)
project(BINDIS C)

include_directories(src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_compile_options(-Wall -Wextra)


add_executable(bindis-cli
    src/renderer/main.c
    src/renderer/renderer.c
    src/common/user.c
)

add_executable(client
    src/client/main.c
    src/common/user.c
)

add_executable(bindis-gui
    src/g-renderer/main.c
    src/g-renderer/gui.c
    src/g-renderer/renderer.c
    src/g-renderer/window.c
    src/common/user.c
)

target_link_libraries(bindis-gui PRIVATE raylib GL m pthread dl rt X11)
target_link_libraries(bindis-cli PRIVATE rt)

