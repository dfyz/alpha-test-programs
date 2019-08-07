SUBDIRS := $(wildcard */.)

.PHONY: main $(SUBDIRS)
main: $(SUBDIRS)

$(SUBDIRS) :
	$(MAKE) -C $@ clean main
