library ieee;

use ieee.std_logic_1164.all;

package utils is
	function invert(input: std_logic) return std_logic;
	function invert(input: std_logic_vector) return std_logic_vector;
end package utils;

package body utils is
	function invert(input: std_logic) return std_logic is
	begin
		return not input;
	end function;
	
	function invert(input: std_logic_vector) return std_logic_vector is
	begin
		return not input;
	end function;
end package body utils;
