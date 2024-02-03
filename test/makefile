#
# This is GNU makefile for Linux OS and GCC/Clang compiler
#

# C++ compiler
CXX = g++ -std=c++11

# C++ compiler flags
CXXFLAGS = -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -I ../include -g -O0

# Valgrind command
VALGRIND = valgrind --leak-check=full --error-exitcode=1

# Command for removing all files and directories
RM_RF = rm -rf

# List of all source files that must be compiled and tested
SRCS := $(wildcard *.cpp)

# List of all executable files
EXES :=

# First rule
.PHONY: check
check:

.PHONY: clean
clean:

# This function generates "check" rule for given source file.
# Usage: $(call generate_rules,source_file)
define generate_rules

.PHONY: check_$(basename $(1))
check:  check_$(basename $(1))
check_$(basename $(1)):
	$(CXX) $(CXXFLAGS) $(1) -o $(basename $(1))
	$(VALGRIND) ./$(basename $(1))

.PHONY: clean_$(basename $(1))
clean:  clean_$(basename $(1))
clean_$(basename $(1)):
	$(RM_RF) $(basename $(1))

endef

# Generate rules for all source files
$(foreach file,$(SRCS),$(eval $(call generate_rules,$(file))))
