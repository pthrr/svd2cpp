add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADER} ${${PROJECT_NAME}_HEADER2})
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog tinyxml2::tinyxml2 cxxopts::cxxopts)
