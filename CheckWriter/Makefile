#-------------------------
# Makefile for checkwriter
#-------------------------

JAVASRC = CheckWriter.java
SOURCES = README Makefile $(JAVASRC)
MAINCLASS = CheckWriter
CLASSES = CheckWriter.class
JARFILE = CheckWriter

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