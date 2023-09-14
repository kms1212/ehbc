#!/bin/bash

rm work*.cf

ghdl -a glue.vhd
ghdl -a glue_tb.vhd
ghdl -e glue_tb
ghdl -r glue_tb