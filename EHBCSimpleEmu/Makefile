################################################################################
# Executables
################################################################################
# CC Configurations
CC?=cc
CFLAGS?=-Wall -Werror -std=c99 -I$(INCDIR) -fshort-wchar -DNO_STDIO_REDIRECT -g \
	$(shell pkg-config --cflags sdl2_ttf) \
	$(shell pkg-config --cflags sdl2_image) \
	$(shell sdl2-config --cflags)

# LD Configurations
LD?=ld
LDFLAGS?= \
	$(shell sdl2-config --libs) \
	$(shell pkg-config --libs sdl2_image) \
	$(shell pkg-config --libs sdl2_ttf) \
	$(shell pkg-config --libs harfbuzz) \
	$(shell pkg-config --libs freetype2) \


################################################################################
# Directory / File Structure
################################################################################
# Source Directories
SRCDIR=src
RSRCDIR=rsrc
INCDIR=include

# Build Directories
BUILDDIR?=build
OBJDIR=$(BUILDDIR)/obj

# File List
SOURCES=$(wildcard $(SRCDIR)/*.c $(SRCDIR)/**/*.c $(SRCDIR)/**/**/*.c)
RESOURCES=$(wildcard $(RSRCDIR)/* $(RSRCDIR)/**/*)

OUT_NOEXT=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%, $(SOURCES))
OBJECTS=$(addsuffix .o, $(OUT_NOEXT))
DEPS=$(addsuffix .d, $(OUT_NOEXT))
RSRCOUTS=$(patsubst $(RSRCDIR)/%, $(BUILDDIR)/%, $(RESOURCES))

# Target Files
TARGET=$(BUILDDIR)/ehbcemu

################################################################################
# Makefile Commands
################################################################################
.PHONY: all clean build prepdir

# Subcommands
all: prepdir build
 
clean:
	rm -rf $(BUILDDIR)

build: $(TARGET) $(RSRCOUTS)

prepdir:
	mkdir -p $(BUILDDIR)
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/gui
	mkdir -p $(OBJDIR)/memory
	mkdir -p $(OBJDIR)/posix
	mkdir -p $(OBJDIR)/cpu
	mkdir -p $(OBJDIR)/cpu/mc68030

# Dependencies
-include %(DEPS)

# Targets
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -MMD -MP -c -o $@ $<

$(BUILDDIR)/%: $(RSRCDIR)/%
	cp $< $@
