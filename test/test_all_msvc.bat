@echo off

setlocal EnableDelayedExpansion

:: List of commands to execute
set commands[0]=make CXX="cl /std:c++14" -f makefile.msvc
set commands[1]=make CXX="cl /std:c++17" -f makefile.msvc
set commands[2]=make CXX="cl /std:c++20" -f makefile.msvc
set commands[2]=make CXX="cl /std:c++latest" -f makefile.msvc

:: Number of commands in the list above. It is calculated in the loop below.
set /a num_of_commands=0

:: Calculate number of commands in the following loop.
:loop_calculate_num_of_command

if defined commands[%num_of_commands%] (
    set /a num_of_commands+=1
    goto :loop_calculate_num_of_command
)

:: Loop counter.
set /a i=0

:: Execute all commands in the following loop
:loop_execute_commands

echo :::: Starting test [!commands[%i%]!]

:: Execute command
!commands[%i%]!

:: Stop everything if command failed
if %errorlevel% NEQ 0 (
    echo :::: ERROR. Test failed [!commands[%i%]!]
    exit /b 1
)

echo :::: Finished test [!commands[%i%]!]

:: Increment loop variable
set /a i+=1

:: Repeat if not finished
if %i% LSS %num_of_commands% (
    goto :loop_execute_commands
)

echo :::: Finished all tests.
echo :::: THE END.

exit /b 0
