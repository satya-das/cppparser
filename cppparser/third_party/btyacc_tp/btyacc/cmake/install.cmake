get_filename_component(prefix "${CMAKE_INSTALL_PREFIX}" ABSOLUTE)

file(
    RELATIVE_PATH relative_path
    "/${btyacc_INSTALL_CMAKEDIR}" "/${CMAKE_INSTALL_BINDIR}/${btyacc_NAME}"
)

file(WRITE "${prefix}/${btyacc_INSTALL_CMAKEDIR}/btyaccConfig.cmake" "\
set(BTYACC_EXECUTABLE \"\${CMAKE_CURRENT_LIST_DIR}/${relative_path}\")

include(\"\${CMAKE_CURRENT_LIST_DIR}/btyaccTargets.cmake\")
")
