#
# This is GNU makefile for Linux OS and GCC/Clang compiler
#

# C++ compiler
CXX = g++ -std=c++11

# C++ compiler flags
CXXFLAGS = -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -I ../include -I include -g -O0

# Valgrind command
VALGRIND = valgrind --leak-check=full --error-exitcode=1

# Set to 1 to execute (run) tests silently
SILENT = 0

ifeq ($(SILENT),0)
	TO_NULL_IF_SILENT =
else
	TO_NULL_IF_SILENT = > /dev/null 2>&1
endif

# Function: Resursive wildcard
# Usage: $(call rwildcard,dir,pattern)
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# Source directory
SRC_DIR := ./src

# List of all source files that must be compiled and tested
SRCS := $(call rwildcard,$(SRC_DIR),*.cpp)

# Build directory
BUILD_DIR := ./build

# First rule
.PHONY: check
check:

# This function generates "check" and "clean" rules for given source file.
# Usage: $(call generate_rules,source_file)
define generate_rules

.PHONY: check_$(basename $(1))
check:  check_$(basename $(1))
check_$(basename $(1)):
	mkdir -p $(dir $(BUILD_DIR)/$(basename $(1)).out)
	$(CXX) $(CXXFLAGS) $(1) -o $(BUILD_DIR)/$(basename $(1)).out
	$(VALGRIND) $(BUILD_DIR)/$(basename $(1)).out $(TO_NULL_IF_SILENT)

endef

# Generate rules for all source files
$(foreach file,$(SRCS),$(eval $(call generate_rules,$(file))))

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
