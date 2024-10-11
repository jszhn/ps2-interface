SUBDIRS = read

all:
	@for dir in $(SUBDIRS); do \
		[ -f $$dir/Makefile ] && $(MAKE) -C $$dir; \
	done

clean:
	@for dir in $(SUBDIRS); do \
		[ -f $$dir/Makefile ] && $(MAKE) -C $$dir clean; \
	done
