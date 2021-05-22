if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wextra -ggdb -lm")
endif()
if ( MSVC )
    set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} /W3")
endif()

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC_PIC ON CACHE BOOL "" FORCE)

include_directories(include)
include_directories(include/ct)
include_directories(include/ct/compiler)
include_directories(include/ct/game)
include_directories(lib/stb/include)

add_subdirectory(lib/SDL2-2.0.12)

set(SDL2_LIBRARIES ${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY} ${SDL2_IMAGE_LIBRARIES})

set(STB 
   "${CMAKE_SOURCE_DIR}/lib/stb/src/stb_image.c"
   "${CMAKE_SOURCE_DIR}/lib/stb/src/stb_truetype.c"
   "${CMAKE_SOURCE_DIR}/lib/stb/src/stb_image_write.c"
   "${CMAKE_SOURCE_DIR}/lib/stb/src/stb_ds.c"
)


set(SOURCE_FILES
   # py and ct compiler
   src/ct/game/stbttf_sdl.c
   src/ct/game/mtwister.c
   src/ct/compiler/ct_compiler.cpp
   src/ct/compiler/py_compiler.cpp
   # stack trace
   src/ct/game/ct_stacktrace.c
   # generated c files
   src/ct/game/shared_unit.c
   src/ct/game/game_object.c
   src/ct/game/components.c
   src/ct/game/game_database.c
   src/ct/game/scene_map.c
   src/ct/game/game_data.c
   src/ct/game/ui_containers.c
   src/ct/game/ui_sprite.c
   src/ct/game/ui.c
   src/ct/game/path_finder.c
   src/ct/game/input_events.c
   src/ct/game/building.c
   src/ct/game/warp_point.c
   src/ct/game/shared_sprite.c
   src/ct/game/render.c
   src/ct/game/audio.c
   src/ct/game/map.c
   src/ct/game/ai.c
   src/ct/game/shared_ability.c
   src/ct/game/inventory.c
   src/ct/game/item.c
   src/ct/game/shared_item.c
   src/ct/game/stats.c
   src/ct/game/ability.c
   src/ct/game/text.c
   src/ct/game/tween.c
   src/ct/game/unit_sprite.c
   src/ct/game/guild.c
   src/ct/game/unit.c
   src/ct/game/world.c
   src/ct/game/game.c
   src/ct/game/sprite.c
   src/ct/game/utils.c
   src/ct/game/image.c
   src/ct/game/tile.c
   src/ct/game/ct_array.c
   src/ct/game/font.c
   src/ct/game/constants.c
   src/ct/game/engine.c
)

set(EXAMPLE_SOURCE_FILES
    src/ct/compiler/ct_compiler.cpp
    src/ct/compiler/py_compiler.cpp
    # stack trace
    src/ct/game/ct_stacktrace.c
)

#add_compile_options(-std=c++17)

# ct
add_executable(ctmain src/ct/ctmain.cpp ${SOURCE_FILES} ${STB})
set_property(TARGET ctmain PROPERTY CMAKE_CXX_STANDARD 17)

# ttf / image are not statically linked right now
target_link_libraries(ctmain SDL2-static SDL2main -lSDL2_ttf -lSDL2_image -lSDL2_mixer -ldwarf)
target_include_directories(ctmain PUBLIC lib/SDL2/include)

add_executable(ctrun src/ct/ctrun.cpp ${SOURCE_FILES} ${STB})
set_property(TARGET ctrun PROPERTY CMAKE_CXX_STANDARD 17)

# ttf / image are not statically linked right now
target_link_libraries(ctrun SDL2-static SDL2main -lSDL2_ttf -lSDL2_image -lSDL2_mixer)
target_include_directories(ctrun PUBLIC lib/SDL2/include)

# game
add_executable(game_main src/ct/game/game_main.c ${SOURCE_FILES} ${STB})
set_property(TARGET game_main PROPERTY CMAKE_C_STANDARD 99)

# ttf / image are not statically linked right now
target_link_libraries(game_main SDL2-static SDL2main -lSDL2_ttf -lSDL2_image -lSDL2_mixer)
target_include_directories(game_main PUBLIC lib/SDL2/include)

# example
add_executable(example example/example.cpp ${EXAMPLE_SOURCE_FILES})
set_property(TARGET example PROPERTY CMAKE_CXX_STANDARD 17)

# ttf / image are not statically linked right now
target_link_libraries(example)
target_include_directories(example PUBLIC)



if (WIN32)
add_custom_target(res 
    COMMAND "7z" a "-uq0" "${CMAKE_BINARY_DIR}/res.zip" "res" WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
else()
add_custom_target(res COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_BINARY_DIR}/res.zip" --format=zip
       "res/*"
       WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
endif()
