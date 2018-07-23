include_directories(${CMAKE_SOURCE_DIR}/inc)

include_directories(SYSTEM
		"${GLOG_INCLUDE_DIRS}"
		"${GTEST_INCLUDE_DIRS}"
		/usr/include/rapidxml
		"${LIBXML2_INCLUDE_DIRS}"
	)

# Add executable and list sources to the executable
add_executable(test_xml_parser test_xml_parser.cpp)

# Link test executable against gtest & gtest_main
target_link_libraries(test_xml_parser
		${GTEST_BOTH_LIBRARIES}
		${GLOG_LIBRARIES}
		${LIBXML2_LIBRARIES}
	)

add_test(test_xml_parser ${EXECUTABLE_OUTPUT_PATH})
