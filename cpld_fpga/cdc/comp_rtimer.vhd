library ieee;

use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity comp_rtimer is
	port (
		------------------------------------------------------------------------
		-- Component Control Signals
		CLK: in std_logic;
		RST: in std_logic;
		EN: in std_logic;
		
		------------------------------------------------------------------------
		-- Register Data Signals
		MMTRR: in std_logic_vector(31 downto 0);
		MMTRF: in std_logic_vector(31 downto 0);
		MRTR: in std_logic_vector(31 downto 0);

		------------------------------------------------------------------------
		-- Module Output Signals
		REFRESH: out std_logic);
end comp_rtimer;

architecture behavioral of comp_rtimer is
	signal cntval: std_logic_vector(19 downto 0) := x"00000";
begin
	process(RST, CLK) is
		variable refreshing: std_logic;
	begin
		if (RST = '1') then
			REFRESH <= '0';
			refreshing := '0';
			cntval <= x"00000";
		elsif rising_edge(CLK) then
			if (EN = '1') then
				cntval <= std_logic_vector(unsigned(cntval) + 1);
				
				if (refreshing = '1' and cntval(11 downto 0) = MRTR(31 downto 20)) then
					REFRESH <= '0';
					refreshing := '0';
					cntval <= x"00000";
				elsif (refreshing = '0' and cntval = MRTR(19 downto 0)) then
					REFRESH <= '1';
					refreshing := '1';
					cntval <= x"00000";
				end if;
			end if;
		end if;
	end process;
end behavioral;
