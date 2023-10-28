library ieee;

use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity comp_adec is
	port (
		------------------------------------------------------------------------
		-- Chip Control Input
		CLK: in std_logic;
		RST: in std_logic;

		------------------------------------------------------------------------
		-- Processor Local Bus Signals
		nAS: in std_logic;
		nECS: in std_logic;
		nOCS: in std_logic;
		FC: in std_logic_vector(2 downto 0);
		A: in std_logic_vector(31 downto 0);

		------------------------------------------------------------------------
		-- Address Decoder Output
		CPCS: out std_logic;  -- FPU Chip Select
		BCCS: out std_logic;  -- Bus Controller Chip Select
		BFCS: out std_logic;  -- Boot Flash Chip Select
		DRAM: out std_logic;  -- DRAM Space
		CDCC: out std_logic;  -- CDC Configuration Space
		IACK: out std_logic_vector(2 downto 0);  -- Interrupt Acknowledge
		BACK: out std_logic_vector(2 downto 0)  -- Breakpoint Acknowldge
		);
end comp_adec;

architecture behavioral of comp_adec is
begin
	process(RST, CLK) is
	begin
		if (RST = '1') then
			CPCS <= '0';
			BCCS <= '0';
			BFCS <= '0';
			DRAM <= '0';
			CDCC <= '0';
			IACK <= "000";
			BACK <= "000";
		elsif falling_edge(CLK) then
			if (nECS = '0' or nAS = '0') then
				if (FC = "111") then  -- CPU Address Space
					if (A(19 downto 16) = "0000") then  -- Breakpoint Acknowledge
						BACK <= A(4 downto 2);
					elsif (A(19 downto 16) = "0010") then -- Coprocessor Comm.
						if (A(15 downto 13) = "001") then
							CPCS <= '1';
						end if;
					elsif (A(19 downto 16) = "1111") then -- Interrupt Acknowledge
						IACK <= A(3 downto 1);
					else  -- Undefined
						-- TODO: Add behavior to handle the undefined access
					end if;
				elsif (FC = "101" or FC = "110") then  -- Supervisor Data/PGM Space
					if (A(31 downto 24) = x"00") then  -- Boot Flash Area (16MiB)
						BFCS <= '1';
					elsif (A(31 downto 24) = x"FF") then  -- MMIO Area (16MiB)
						-- TODO: MMIO
					else  -- DRAM Area
						DRAM <= '1';
					end if;
				else  -- User Data/Program Space or Reserved, DRAM Area
					DRAM <= '1';
				end if;
			else
				CPCS <= '0';
				BCCS <= '0';
				BFCS <= '0';
				DRAM <= '0';
				CDCC <= '0';
				IACK <= "000";
				BACK <= "000";
			end if;
		end if;
	end process;
end behavioral;
