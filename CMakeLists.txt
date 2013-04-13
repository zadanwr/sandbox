cmake_minimum_required(VERSION 2.8)

project(sandbox)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(INC
	${INC_DIR}/Sandbox/Entity.h
	${INC_DIR}/Sandbox/Image.h
	${INC_DIR}/Sandbox/Mod.h
	${INC_DIR}/Sandbox/Server.h
	${INC_DIR}/Sandbox/Sprite.h
)

set(SRC
	${SRC_DIR}/main.cpp
	${SRC_DIR}/Entity.cpp
	${SRC_DIR}/Image.cpp
	${SRC_DIR}/Mod.cpp
	${SRC_DIR}/Server.cpp
	${SRC_DIR}/Sprite.cpp
)

set(INCLUDE
	${PROJECT_SOURCE_DIR}/../ce/modules/ce_base/include
	${PROJECT_SOURCE_DIR}/../ce/modules/ce_frontend/include
	${PROJECT_SOURCE_DIR}/../ce/modules/ce_game2d/include
	${PROJECT_SOURCE_DIR}/../ce/modules/ce_ui/include
	${INC_DIR}
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

find_package(DevIL REQUIRED)
set(LIB ${LIB} ${IL_LIBRARIES} ${ILU_LIBRARIES})
set(INCLUDE ${INCLUDE} ${IL_INCLUDE_DIR}/..)

find_package(Freetype REQUIRED)
set(LIB ${LIB} ${FREETYPE_LIBRARIES})
set(INCLUDE ${INCLUDE} ${FREETYPE_INCLUDE_DIRS})

find_package(V8 REQUIRED)
set(LIB ${LIB}
	${V8_LIBRARIES}
)
set(INCLUDE ${INCLUDE}
	${V8_INCLUDE_DIR}
)

include_directories(${INCLUDE})

set(NAME "sandbox")
add_executable(${NAME} ${SRC} ${INC})
set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
target_link_libraries(${NAME} ${LIB})
