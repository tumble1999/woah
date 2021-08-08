set(NAME woah)


file(GLOB_RECURSE SRC
"*.c"
)

add_executable(${NAME}
${SRC}
)
