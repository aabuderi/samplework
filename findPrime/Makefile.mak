#-----------------------------------------------------------------------------
# Makefile for lab2
#-----------------------------------------------------------------------------

JAVASRC = FindPrime.java 
SOURCES = README Makefile $(JAVASRC)
MAINCLASS = FindPrime
CLASSES = FindPrime.class
JARFILE = FindPrime

all: $(JARFILE)

$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(CLASSES)
	rm Manifest
	chmod +x $(JAVASRC)

$(CLASSES): $(JAVASRC)
	javac -Xlint $(JAVASRC)

clean: 
	rm $(CLASSES) $(JARFILE)
