#
# make
# make all      -- build everything
#
# make test     -- run unit tests
#
# make install  -- install binaries to /usr/local
#
# make clean    -- remove build files
#
# To reconfigure for Debug build:
#   make clean; make debug; make
#

all:    build
	$(MAKE) -Cbuild $@

test:   build
	$(MAKE) -Cbuild unit_tests
	ctest --test-dir build/tests

test-all: TEST_ALL="-DTEST_ALL:BOOL=ON"
test-all: build
	@if grep TEST_ALL:BOOL=ON build/CMakeCache.txt; \
        then \
            $(MAKE) test; \
        else \
            rm -rf build; \
            $(MAKE) $@; \
        fi

install: build
	$(MAKE) -Cbuild $@

clean:
	rm -rf build

build:
	mkdir $@
	cmake -B$@ -DCMAKE_BUILD_TYPE=RelWithDebInfo $(TEST_ALL)

debug:
	mkdir build
	cmake -Bbuild -DCMAKE_BUILD_TYPE=Debug

#
# Run 8086 test suite.
#
moo86:  all outdir
	$(MAKE) -Coutdir -f ../Makefile run-moo86

MOO86   ?= $(PWD)/../8086-tests/v1_binary
run-moo86:
	for moo in $(MOO86)/*.gz; do \
	    ../build/moo_booth/moo-booth -run $$moo; \
        done

outdir:
	mkdir $@

#
# Run 8088 test suite.
#
moo88:  all outdir
	$(MAKE) -Coutdir -f ../Makefile run-moo88

MOO88   ?= $(PWD)/../8088-tests/v2_binary
run-moo88:
	for moo in $(MOO88)/*.gz; do \
	    ../build/moo_booth/moo-booth -run $$moo; \
        done
