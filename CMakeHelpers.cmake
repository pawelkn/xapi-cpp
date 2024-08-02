# Helper macro to find boost libraries
macro(helper_FIND_BOOST_LIBS)

    find_package(Boost ${BOOST_VERSION_REQUIRED} REQUIRED COMPONENTS system url)

    if(NOT Boost_FOUND)
        message(FATAL_ERROR "Boost not found. Please install Boost version ${BOOST_VERSION_REQUIRED} or set Boost_DIR variable.")
    elseif(NOT Boost_VERSION VERSION_GREATER_EQUAL ${BOOST_VERSION_REQUIRED})
        message(FATAL_ERROR "Boost version ${BOOST_VERSION_REQUIRED} or higher is required. Found version ${Boost_VERSION}.")
    else()
        include_directories(${Boost_INCLUDE_DIRS})
    endif()

endmacro()

#Helper macro to find json library
macro(helper_FIND_JSONCPP_LIB)
    find_package(jsoncpp REQUIRED)
    if(NOT jsoncpp_FOUND)
        message(FATAL_ERROR "jsoncpp not found. Please install or set jsoncpp variable.")
    endif()
endmacro()

# Helper macro to find google test library
macro(helper_FIND_GTEST_LIBS)
    find_package(GTest REQUIRED)
    if(NOT GTest_FOUND)
        message("Gtets not found. Tests won`t compile.")
    else()
        include_directories(${GTEST_INCLUDE_DIRS})
    endif()
endmacro()
