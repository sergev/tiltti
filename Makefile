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
PROG    = build/tiltti

all $(PROG): build
	$(MAKE) -Cbuild all

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

MOO86   ?= $(PWD)/../8086/v1_binary
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

MOO88   ?= $(PWD)/../8088/v2_binary
run-moo88:
	for moo in $(MOO88)/*.gz; do \
	    ../build/moo_booth/moo-booth -run $$moo; \
        done

images/b.img:
	qemu-img create -f raw $@ 1440k

#
# Run MS-DOS
#
msdos1: $(PROG)
	$(PROG) images/msdos1.25-320k.img

msdos2: $(PROG)
	$(PROG) images/msdos2.12-360k.img

msdos3: $(PROG)
	$(PROG) images/msdos3.31-1.44m.img images/b.img

msdos6: $(PROG)
	$(PROG) images/msdos6.22-1.44m.img images/b.img

# Requires i386
msdos7: $(PROG)
	$(PROG) images/msdos7.1-1.44m.img

#
# Run PC-DOS
#
pcdos1: $(PROG)
	$(PROG) images/pcdos1.10-160k.img

pcdos2: $(PROG)
	$(PROG) images/pcdos2.10-180k.img

pcdos3: $(PROG)
	$(PROG) images/pcdos3.30-720k.img

pcdos4: $(PROG)
	$(PROG) images/pcdos4.01-720k.img

pcdos5: $(PROG)
	$(PROG) images/pcdos5.02-720k.img

# Cancels installation, then loops
pcdos6: $(PROG)
	$(PROG) images/pcdos6.30-1.44m.img

# Cancels installation, then loops
pcdos7: $(PROG)
	$(PROG) images/pcdos7.0-1.44m.img

# Cancels installation, then loops
pcdos7a: $(PROG)
	$(PROG) images/pcdos7.00r1-1.44m.img

# Loops after Int 1Ah AH=00h RTC Timer Request
pcdos7b: $(PROG)
	$(PROG) images/pcdos7.1-1.44m.img

#
# Run DR-DOS
#
drdos3: $(PROG)
	$(PROG) images/drdos3.41-720k.img

drdos5: $(PROG)
	$(PROG) images/drdos5.0-720k.img

drdos6: $(PROG)
	$(PROG) images/drdos6.0-720k.img

drdos7: $(PROG)
	$(PROG) images/drdos7.03-1.44m.img

drdos8: $(PROG)
	$(PROG) images/drdos8.0-1.44m.img

#
# Run CPM
#
cpm1:   $(PROG)
	$(PROG) images/cpm1.1-320k.img

# Loops after installing handler for Int e6
cpm3:   $(PROG)
	$(PROG) images/cpm3.1-320k.img
