set(INCROOT ${PROJECT_SOURCE_DIR}/include/GameEngine)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/GameEngine)

add_subdirectory(asset_manager)
add_subdirectory(audio_manager)
add_subdirectory(game)
add_subdirectory(particle_manager)
add_subdirectory(settings)
add_subdirectory(state)

set(SRC
    ${SRC}
    ${INCROOT}/game_head.h
    ${INCROOT}/types.h
    ${SRCROOT}/run.c
    PARENT_SCOPE
)

