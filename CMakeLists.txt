cmake_minimum_required(VERSION 2.8.3)
project(v2I_communication)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  serial
  std_msgs
  message_generation
)

add_message_files(FILES
  read_vector.msg
)

generate_messages(DEPENDENCIES
  std_msgs
  v2I_communication
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS  roscpp std_msgs serial
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(serial_communication_node src/serial_communication_node.cpp)
target_link_libraries(serial_communication_node ${catkin_LIBRARIES})

add_executable(vector_conversion_node src/vector_conversion.cpp)
target_link_libraries(vector_conversion_node ${catkin_LIBRARIES})

add_executable(main_node src/main.cpp)
target_link_libraries(main_node ${catkin_LIBRARIES})

add_dependencies(serial_communication_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(vector_conversion_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(main_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

install(TARGETS serial_communication_node vector_conversion_node main_node
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include
   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
   FILES_MATCHING PATTERN "*.h"
)

#install(FILES
#something.launch
# DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
#)
