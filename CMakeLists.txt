cmake_minimum_required( VERSION 2.8.12 )
project( stack_vm_prj )

include( ExternalProject )

set( Boost_USE_STATIC_LIBS OFF )
set( Boost_USE_MULTITHREADED ON )
set( Boost_USE_STATIC_RUNTIME OFF )
find_package( Boost 1.59.0 REQUIRED COMPONENTS system filesystem unit_test_framework date_time )

IF( ${CMAKE_CXX_COMPILER_ID} STREQUAL 'MSVC' )
	add_compile_options( -D_WIN32_WINNT=0x0601 ) 
ELSE( )
	find_package( Threads REQUIRED )
	if( THREADS_HAVE_PTHREAD_ARG )
		set( COMPILER_SPECIFIC_LIBS, "-lpthread" )
	endif()

	IF( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" )
		add_compile_options(-std=c++14 -stdlib=libc++ -Weverything -Wno-c++98-compat -Wfatal-errors -Wno-covered-switch-default -Wno-padded -Wno-exit-time-destructors -Wno-c++98-compat-pedantic -Wno-unused-parameter -Wno-missing-noreturn -Wno-missing-prototypes -Wno-disabled-macro-expansion)		
	ELSEIF( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" )
		add_compile_options(-std=c++14 -Wall -Wno-deprecated-declarations)
	ENDIF()
ENDIF()

if( ${BINARY_DIR} MATCHES "/binary$" )
    set( DEP_BINARY_DIR "${CMAKE_BINARY_DIR}" )
else( )
    set( DEP_BINARY_DIR "${CMAKE_BINARY_DIR}/binary" )
endif( )

ExternalProject_Add( 
	headlibsprj
	GIT_REPOSITORY "https://github.com/beached/header_libraries.git"
	SOURCE_DIR "${DEP_BINARY_DIR}/deps/headlibs"
	BINARY_DIR "${DEP_BINARY_DIR}"
	INSTALL_DIR "${DEP_BINARY_DIR}/inst"
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_BINARY_DIR}/inst
	GIT_TAG "master"
	PATCH_COMMAND ""
	TEST_COMMAND ""
 )

include_directories( SYSTEM "${DEP_BINARY_DIR}/inst/include" )
include_directories( SYSTEM ${Boost_INCLUDE_DIRS} )

set( HEADER_FOLDER "include" )
include_directories( ${HEADER_FOLDER} )

set( HEADER_FILES
		#${HEADER_FOLDER}/variant.h
)

set( SOURCE_FILES
		stack_vm.cpp
)

#add_library( stack_vm STATIC ${HEADER_FILES} ${SOURCE_FILES} )

#add_dependencies( stack_vm headlibsprj )

add_executable( stack_vm ${SOURCE_FILES} )
target_link_libraries( stack_vm ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT} ${COMPILER_SPECIFIC_LIBS} )
add_dependencies( stack_vm headlibsprj )


#install( TARGETS stack_vm DESTINATION lib )
#install( DIRECTORY ${HEADER_FOLDER}/ DESTINATION include/daw/stack_vm )

