execute_process(COMMAND "cat /etc/os-release | grep -oP \"^ID=(\\K[a-zA-Z0-9]*)\"" OUTPUT_VARIABLE UNAME_RESULT OUTPUT_STRIP_TRAILING_WHITESPACE)
message(STATUS "Kernel version: " ${UNAME_RESULT})
