ARCHIVE=projet-2.tar.gz
SOURCES=$(wildcard src/*)

all: $(ARCHIVE)

$(ARCHIVE): $(SOURCES)
	cd src && tar -pczf ../$@ *

clean:
	rm -f $(ARCHIVE)

.PHONY: all clean

