library ieee;

use ieee.std_logic_1164.all;

entity comp_reg is
	generic (
		DATAW: integer);
	port (
		CLK: in std_logic;
		RST: in std_logic;
		
		WREN: in std_logic;
	
		DATAIN: in std_logic_vector(DATAW-1 downto 0);
		DATAOUT: out std_logic_vector(DATAW-1 downto 0));
end comp_reg;

architecture behavioral of comp_reg is
begin
	process(CLK) is
	begin
		if rising_edge(CLK) then
			if (WREN = '1') then
				DATAOUT <= DATAIN;
			elsif (RST = '1') then
				DATAOUT <= (others => '0');
			end if;
		end if;
	end process;
end behavioral;
