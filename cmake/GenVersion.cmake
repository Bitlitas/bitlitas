# Copyright (c) 2018, Bitlitas
# All rights reserved. Based on Cryptonote and Monero.

# Check what commit we're on
execute_process(COMMAND "${GIT}" rev-parse --short HEAD RESULT_VARIABLE RET OUTPUT_VARIABLE COMMIT OUTPUT_STRIP_TRAILING_WHITESPACE)

if(RET)
	# Something went wrong, set the version tag to -unknown
	
    message(WARNING "Cannot determine current commit. Make sure that you are building either from a Git working tree or from a source archive.")
    set(VERSIONTAG "unknown")
    configure_file("src/version.cpp.in" "${TO}")
else()
	message(STATUS "You are currently on commit ${COMMIT}")
	
	# Get all the tags
	execute_process(COMMAND "${GIT}" rev-list --tags --max-count=1 --abbrev-commit RESULT_VARIABLE RET OUTPUT_VARIABLE TAGGEDCOMMIT OUTPUT_STRIP_TRAILING_WHITESPACE)
	
    if(NOT TAGGEDCOMMIT)
        message(WARNING "Cannot determine most recent tag. Make sure that you are building either from a Git working tree or from a source archive.")
        set(VERSIONTAG "${COMMIT}")
    else()
        message(STATUS "The most recent tag was at ${TAGGEDCOMMIT}")
        
        # Check if we're building that tagged commit or a different one
        if(COMMIT STREQUAL TAGGEDCOMMIT)
            message(STATUS "You are building a tagged release")
            set(VERSIONTAG "release")
        else()
            message(STATUS "You are ahead of or behind a tagged release")
            set(VERSIONTAG "${COMMIT}")
        endif()
    endif()	    

    configure_file("src/version.cpp.in" "${TO}")
endif()
