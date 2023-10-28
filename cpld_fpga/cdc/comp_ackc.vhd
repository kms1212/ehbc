library ieee;

use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity comp_ackc is
	port (
		------------------------------------------------------------------------
		-- Component Control Signals
		CLK: in std_logic;
		RST: in std_logic;
		EN: in std_logic;
		
		------------------------------------------------------------------------
		-- Processor Local Bus Signals
		nSTERM: out std_logic;
		nDSACK: out std_logic_vector(1 downto 0);
		
		------------------------------------------------------------------------
		-- Address Decoder Signals
		BFCS: in std_logic;  -- Boot Flash Chip Select
		DRAM: in std_logic;  -- DRAM Space
		CDCC: in std_logic   -- CDC Configuration Space
		);
end comp_ackc;

architecture behavioral of comp_ackc is
begin
	process(RST, BFCS, DRAM, CDCC) is
	begin
		if (RST = '1') then
			nSTERM <= '1';
			nDSACK <= "11";
		elsif rising_edge(BFCS) then
			if (EN = '1') then
				nSTERM <= '0';
			end if;
		elsif rising_edge(DRAM) then
			if (EN = '1') then
				nSTERM <= '0';
			end if;
		elsif rising_edge(CDCC) then
			if (EN = '1') then
				nSTERM <= '0';
			end if;
		end if;
	end process;
end behavioral;