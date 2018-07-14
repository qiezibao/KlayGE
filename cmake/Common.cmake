CMAKE_MINIMUM_REQUIRED(VERSION 3.9 FATAL_ERROR)

INCLUDE(${CMAKE_CURRENT_LIST_DIR}/DependenciesCommitId.cmake)

SET(CMAKE_DEBUG_POSTFIX "_d" CACHE STRING "Add a postfix, usually _d on windows")
SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "Add a postfix, usually empty on windows")
SET(CMAKE_RELWITHDEBINFO_POSTFIX "" CACHE STRING "Add a postfix, usually empty on windows")
SET(CMAKE_MINSIZEREL_POSTFIX "" CACHE STRING "Add a postfix, usually empty on windows")

FIND_PACKAGE(PythonInterp)
IF(PYTHONINTERP_FOUND)
	IF (${PYTHON_VERSION_STRING} VERSION_LESS "2.7.0")
		MESSAGE(FATAL_ERROR "Unsupported Python version. Please install Python 2.7.0 or up.")
	ENDIF()
ELSE()
	MESSAGE(FATAL_ERROR "Could NOT find Python. Please install Python 2.7.0 or up first.")
ENDIF()

FUNCTION(ADD_POST_BUILD TARGET_NAME SUBFOLDER)
	ADD_CUSTOM_COMMAND(TARGET ${TARGET_NAME}
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE_DIR:${TARGET_NAME}>/$<TARGET_FILE_NAME:${TARGET_NAME}> ${KLAYGE_BIN_DIR}/${SUBFOLDER})
ENDFUNCTION()

FUNCTION(DOWNLOAD_DEPENDENCY RELATIVE_PATH FILE_ID)
	SET(DEST ${KLAYGE_ROOT_DIR}/${RELATIVE_PATH})
	SET(REDOWNLOAD FALSE)
	IF(EXISTS ${DEST})
		FILE(SHA1 ${DEST} FILE_SHA1)
		IF(NOT "${FILE_SHA1}" STREQUAL ${FILE_ID})
			SET(REDOWNLOAD TRUE)
		ENDIF()
	ELSE()
		SET(REDOWNLOAD TRUE)
	ENDIF()
	IF(REDOWNLOAD)
		SET(URL "https://raw.githubusercontent.com/gongminmin/KlayGEDependencies/${DEPENDENCIES_COMMIT_ID}/${RELATIVE_PATH}")
		MESSAGE(STATUS "Downloading ${URL}...")
		FILE(DOWNLOAD ${URL} ${DEST} EXPECTED_HASH SHA1=${FILE_ID} STATUS ERR)
		LIST(GET ERR 0 ERR_CODE)
		IF(ERR_CODE)
			FILE(REMOVE ${DEST})
			LIST(GET ERR 1 ERR_MSG)
			MESSAGE(FATAL_ERROR "Failed to download file ${URL}: ${ERR_MSG}")
		ENDIF()
	ENDIF()
	SET(${ARGV3} ${REDOWNLOAD} PARENT_SCOPE)
ENDFUNCTION()
