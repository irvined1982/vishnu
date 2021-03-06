if (BUILD_TESTING)
  add_subdirectory(tests)
endif()

include_directories(
  ${CONFIG_SOURCE_DIR}
  ${ZMQ_INCLUDE_DIR}
  ${UTILVISHNU_SOURCE_DIR}
  ${VISHNU_EXCEPTION_INCLUDE_DIR}
  ${EMF_DATA_DIR}
  ${TMS_EMF_DATA_DIR}
  ${EMF4CPP_INCLUDE_DIR}
  ${VISHNU_SOURCE_DIR}/communication/
  ${VISHNU_SOURCE_DIR}/communication/dispatcher
  ${Boost_INCLUDE_DIR}
)

add_library(zmq_helper
  DIET_client.cpp
  Annuary.cpp
  Server.cpp
  SeD.cpp
  utils.cpp
  ${utils_server_SRCS}
)

target_link_libraries (zmq_helper
  ${ZMQ_LIBRARIES}
  ${Boost_LIBRARIES}
  vishnu-core
)

# --------------------------------------------------------------------------
#add_subdirectory(ZMQHelper)
# --------------------------------------------------------------------------

if(COMPILE_SERVERS)
  add_executable(dispatcher dispatcher/main.cpp
    dispatcher/dispatcher.cpp)
  
  target_link_libraries(dispatcher
    ${ZMQ_LIBRARIES} 
    ${Boost_LIBRARIES}
    zmq_helper
    vishnu-core
    )
  
  install(TARGETS dispatcher DESTINATION ${SBIN_INSTALL_DIR})
endif()

set_target_properties(zmq_helper PROPERTIES VERSION ${VISHNU_VERSION})
install(TARGETS zmq_helper DESTINATION ${LIB_INSTALL_DIR})

