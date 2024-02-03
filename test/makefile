CXX      = g++ -std=c++11
CXXFLAGS = -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -I ../include -g -O0

VALGRIND = valgrind --leak-check=full

RM_RF    = rm -rf

# List of all source files that must be compiled and tested
SRCS := $(wildcard *.cpp)

# List of all executable files
EXES :=

# First rule
.PHONY: check
check:

# This function generates "check" rule for given source file.
# Usage: $(call generate_rules,source_file)
define generate_rules

.PHONY: check_$(basename $(1))
check:  check_$(basename $(1))
check_$(basename $(1)):
	$(CXX) $(CXXFLAGS) $(1) -o $(basename $(1))
	$(VALGRIND) ./$(basename $(1))

EXES += $(basename $(1))

endef

# Generate rules for all source files
$(foreach file,$(SRCS),$(eval $(call generate_rules,$(file))))

.PHONY: clean
clean:
	$(RM_RF) $(EXES)
