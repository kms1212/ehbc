#!/bin/bash

set -euo pipefail

ZIPFILE=$1
PARTNAME=$(basename "$ZIPFILE" .zip)

mkdir -p "./$PARTNAME"
unzip -u "$ZIPFILE" -d "./$PARTNAME"

echo Copying file: "$PARTNAME.kicad_sym" \-\> "ext_symbols/$PARTNAME/"
mkdir -p "ext_symbols/$PARTNAME"
cp "$PARTNAME/$PARTNAME.kicad_sym" "ext_symbols/$PARTNAME"

echo "Copying file: \*.kicad_mod \-\> ext_footprints/$PARTNAME.pretty/"
mkdir -p "ext_footprints/$PARTNAME.pretty"
cp "$PARTNAME/"*.kicad_mod "ext_footprints/$PARTNAME.pretty/"

rm -r "./$PARTNAME"
