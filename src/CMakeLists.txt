set(NAME woah)


file(GLOB_RECURSE SRC
	"*.c"
	"*.cpp"
	"*.hpp"
)
add_executable(${NAME}
	${SRC}
)

target_include_directories(${NAME}
	PRIVATE ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${NAME}
	${WOAH_LIBS}
)

install(TARGETS ${NAME} RUNTIME DESTINATION bin)
include(CPack)
