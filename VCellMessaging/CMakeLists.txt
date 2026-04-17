project(vcellmessaging LANGUAGES CXX)

configure_file(
		"${CMAKE_CURRENT_SOURCE_DIR}/src/GitDescribe.cpp.in"
		"${CMAKE_CURRENT_BINARY_DIR}/GitDescribe.cpp"
		@ONLY
)

set(HEADER_FILES
		include/VCELL/SimulationMessaging.h
		include/VCELL/GitDescribe.h
)

set(SRC_FILES
		src/SimulationMessaging.cpp
		"${CMAKE_CURRENT_BINARY_DIR}/GitDescribe.cpp"
)

add_library(vcellmessaging ${SRC_FILES} ${HEADER_FILES})

target_include_directories(vcellmessaging
		PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

if(OPTION_TARGET_MESSAGING)
	target_link_libraries(vcellmessaging
			PUBLIC
			CURL::libcurl
			Threads::Threads
	)
	target_compile_definitions(vcellmessaging PUBLIC USE_MESSAGING=1)
endif()

install(TARGETS vcellmessaging
		ARCHIVE DESTINATION lib
		RUNTIME DESTINATION bin
)