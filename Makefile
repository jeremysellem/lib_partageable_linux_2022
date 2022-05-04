# If the first argument is "all"...
ifeq (all,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
  COMPONENTS_NEEDED := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(COMPONENTS_NEEDED):;@:)
endif

all: test

test: install
	cd bin; \
	LD_LIBRARY_PATH=. ./main

install:
	cd main && ${MAKE} install $(COMPONENTS_NEEDED)

clean:
	cd main && ${MAKE} clean
