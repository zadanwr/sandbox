cmake_minimum_required(VERSION 2.8)

project(sandbox)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SRC
	${SRC_DIR}/main.cpp
)

set(INCLUDE
	${PROJECT_SOURCE_DIR}/../ce/modules/ce_base/include
	${PROJECT_SOURCE_DIR}/../ce/modules/ce_frontend/include
	${PROJECT_SOURCE_DIR}/../ce/modules/ce_game2d/include
	${PROJECT_SOURCE_DIR}/../ce/modules/ce_ui/include
	${PROJECT_SOURCE_DIR}/include
)

set(LIB "")

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(LIB ${LIB}
		${PROJECT_SOURCE_DIR}/../ce/modules/ce_base/libce_base.a
		${PROJECT_SOURCE_DIR}/../ce/modules/ce_frontend/libce_frontend.a
		${PROJECT_SOURCE_DIR}/../ce/modules/ce_game2d/libce_game2d.a
		${PROJECT_SOURCE_DIR}/../ce/modules/ce_ui/libce_ui.a
	)
	find_package(X11 REQUIRED)
	set(LIB ${LIB} ${X11_LIBRARIES})
	set(INCLUDE ${INCLUDE} ${X11_INCLUDE_DIR})
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(LIB ${LIB}
		optimized ${PROJECT_SOURCE_DIR}/../ce/modules/ce_base/Release/ce_base.lib
		debug ${PROJECT_SOURCE_DIR}/../ce/modules/ce_base/Debug/ce_base.lib

		optimized ${PROJECT_SOURCE_DIR}/../ce/modules/ce_frontend/Release/ce_frontend.lib
		debug ${PROJECT_SOURCE_DIR}/../ce/modules/ce_frontend/Debug/ce_frontend.lib

		optimized ${PROJECT_SOURCE_DIR}/../ce/modules/ce_game2d/Release/ce_game2d.lib
		debug ${PROJECT_SOURCE_DIR}/../ce/modules/ce_game2d/Debug/ce_game2d.lib

		optimized ${PROJECT_SOURCE_DIR}/../ce/modules/ce_ui/Release/ce_ui.lib
		debug ${PROJECT_SOURCE_DIR}/../ce/modules/ce_ui/Debug/ce_ui.lib
	)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

find_package(OpenGL REQUIRED)
set(LIB ${LIB}
	${OPENGL_LIBRARIES}
)

include_directories(${INCLUDE})

set(NAME "sandbox")
add_executable(${NAME} ${SRC})
set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
target_link_libraries(${NAME} ${LIB})
