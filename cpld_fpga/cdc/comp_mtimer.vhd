library ieee;

use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity comp_mtimer is
	port (
		------------------------------------------------------------------------
		-- Component Control Signals
		CLK: in std_logic;
		RST: in std_logic;
		
		------------------------------------------------------------------------
		-- Register Data Signals
		MMTRR: in std_logic_vector(31 downto 0);
		MMTRF: in std_logic_vector(31 downto 0);

		------------------------------------------------------------------------
		-- Module IO Signals
		REFRESH: in std_logic;
		TCYCLE: in std_logic;
		ROWEQ: in std_logic;
		RAOUT: out std_logic;
		RASOUT: out std_logic;
		CAOUT: out std_logic;
		CASOUT: out std_logic;
		SDQOUT: out std_logic);
end comp_mtimer;

architecture behavioral of comp_mtimer is
	signal cntvalr: std_logic_vector(7 downto 0) := x"00";
	signal cntvalf: std_logic_vector(7 downto 0) := x"00";
begin
	process(RST, CLK) is
	begin
		if (RST = '1') then
			cntvalr <= x"00";
			cntvalf <= x"00";
		elsif rising_edge(CLK) then
			if (TCYCLE = '1') then
				cntvalr <= std_logic_vector(unsigned(cntvalr) + 1);
				
				if (ROWEQ = '1') then
					if (cntvalr = x"00") then
					elsif (cntval = x"01") then
					end if;
				else
				end if;
				
				if (cntvalr = x"FF") then
					cntvalr <= x"00";
					RASOK <= '1';
				end if;
			else
				cntvalr <= x"00";
				RASOK <= '0';
			end if;
		elsif falling_edge(CLK) then
			if (TCYCLE = '1') then
				cntvalf <= std_logic_vector(unsigned(cntvalf) + 1);
				
				if (cntvalf = x"FF") then
					cntvalf <= x"00";
					CASOK <= '1';
				end if;
			else
				cntvalr <= x"00";
				CASOK <= '0';
			end if;
		end if;
	end process;
end behavioral;
