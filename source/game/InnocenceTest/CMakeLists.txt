aux_source_directory(. DIR_SRCS)
add_library(InnoTest ${DIR_SRCS})

target_link_libraries(InnoTest InnoEntity)
target_link_libraries(InnoTest InnoComponent)
