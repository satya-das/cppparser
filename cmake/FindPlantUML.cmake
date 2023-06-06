# Input variable:
#   PLANTUML_DIR_HINTS: The list of possible paths of the directories that might hold `plantuml.jar`.
# Output variables:
#   PLANT_UML_PATH: The path of `plantuml.jar`

find_file(PLANT_UML_PATH NAMES plantuml.jar HINTS ${PLANTUML_DIR_HINTS})
if(NOT PLANT_UML_PATH)
    message(FATAL_ERROR "Looking for plantuml.jar - not found.")
else()
    message(STATUS "Found PlantUML jar file at ${PLANT_UML_PATH}")
endif()
