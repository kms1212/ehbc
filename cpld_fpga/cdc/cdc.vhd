library ieee;

use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

use work.all;
use work.utils.all;

entity cdc is
	port (
		------------------------------------------------------------------------
		-- Chip Control Input
		CLK: in std_logic;
		nRST: in std_logic;
		nCS: in std_logic;

		------------------------------------------------------------------------
		-- Processor Local Bus Signals
		nAS: in std_logic;
		nDS: in std_logic;
		nECS: in std_logic;
		nOCS: in std_logic;
		nDSACK: out std_logic_vector(1 downto 0) := "HH";
		SIZ: in std_logic_vector(1 downto 0);
		R_nW: in std_logic;
		nRMC: in std_logic;
		nSTERM: out std_logic := 'H';
		FC: in std_logic_vector(2 downto 0);
		A: in std_logic_vector(31 downto 0);
		D: inout std_logic_vector(31 downto 0);

		------------------------------------------------------------------------
		-- Bus Arbitation Signals
		nBR: out std_logic := 'H';
		nBG: in std_logic;
		nBGACK: out std_logic := 'H';

		------------------------------------------------------------------------
		-- Cache Control Signals
		nCBREQ: in std_logic;
		nCBACK: out std_logic := 'H';
		nCIIN: in std_logic;
		nCIOUT: out std_logic := 'H';

		------------------------------------------------------------------------
		-- 72pin 5V SIMM DRAM Control Signals
		SA: out std_logic_vector(11 downto 0);
		nCAS: out std_logic_vector(3 downto 0) := x"F";
		nRAS: out std_logic_vector(7 downto 0) := x"FF";
		nMWE: out std_logic := '1';
		nMOE: out std_logic := '1';
		nPD: in std_logic_vector(3 downto 0);

		------------------------------------------------------------------------
		-- Cache Module Control Signals
		CA: out std_logic_vector(19 downto 0) := x"00000";
		TD: inout std_logic_vector(15 downto 0);
		nCOE: out std_logic := '1';
		nCWE: out std_logic := '1';

		------------------------------------------------------------------------
		-- DMA Control Signals
		nDRQ: in std_logic_vector(7 downto 0);
		nDACK: out std_logic_vector(7 downto 0) := x"FF";
		PCL: out std_logic_vector(7 downto 0) := x"00";
		nDTC: in std_logic;
		nDONE: out std_logic := '1';
		
		------------------------------------------------------------------------
		-- Address Decoder Signals
		nCPCS: out std_logic := '1';  -- FPU Chip Select
		nBCCS: out std_logic := '1';  -- Bus Controller Chip Select
		nBFCS: out std_logic := '1';  -- Boot Flash Chip Select
		nIACK: out std_logic_vector(2 downto 0) := "111";  -- Interrupt Ack.
		nBACK: out std_logic_vector(2 downto 0) := "111"   -- Breakpoint Ack.
		);
end cdc;

architecture behavioral of cdc is
	signal regwbus: std_logic_vector(31 downto 0);
	
	signal csrd: std_logic_vector(31 downto 0);
	signal cmdrd: std_logic_vector(31 downto 0);
	signal mmird: std_logic_vector(31 downto 0);
	signal mmir_wr: std_logic;
	signal mrtrd: std_logic_vector(31 downto 0) := x"7800C350";
	signal mrtr_wr: std_logic;
	signal mmtrrd: std_logic_vector(31 downto 0) := x"00000000";
	signal mmtrr_wr: std_logic;
	signal mmtrfd: std_logic_vector(31 downto 0) := x"00000000";
	signal mmtrf_wr: std_logic;
	
	signal cfgsp: std_logic := '0';
	signal dramsp: std_logic := '0';
	signal flashsp: std_logic := '0';
	
	signal rtimeren: std_logic := '1';
	signal dramen: std_logic := '0';
	signal caccen: std_logic := '0';

	signal refresh: std_logic;
	
	signal dramc_nSTERM: std_logic := '1';
	signal cacc_nSTERM: std_logic := '1';
	
	signal cache_hit: std_logic := '0';
begin
	mmir: comp_reg
		generic map (DATAW => 32)
		port map (
			CLK => CLK,
			RST => invert(nRST),
			WREN => mmir_wr,
			DATAIN => regwbus,
			DATAOUT => mmird);
	mrtr: comp_reg
		generic map (DATAW => 32)
		port map (
			CLK => CLK,
			RST => invert(nRST),
			WREN => mrtr_wr,
			DATAIN => regwbus,
			DATAOUT => mrtrd);
	mmtrr: comp_reg
		generic map (DATAW => 32)
		port map (
			CLK => CLK,
			RST => invert(nRST),
			WREN => mmtrr_wr,
			DATAIN => regwbus,
			DATAOUT => mmtrrd);
	mmtrf: comp_reg
		generic map (DATAW => 32)
		port map (
			CLK => CLK,
			RST => invert(nRST),
			WREN => mmtrf_wr,
			DATAIN => regwbus,
			DATAOUT => mmtrfd);
			
	adec: comp_adec
		port map (
			CLK => CLK,
			RST => invert(nRST),
			nAS => nAS,
			nECS => nECS,
			nOCS => nOCS,
			FC => FC,
			A => A,
			CPCS => nCPCS,
			BCCS => nBCCS,
			BFCS => flashsp,
			DRAM => dramsp,
			CDCC => cfgsp,
			IACK => nIACK,
			BACK => nBACK);
			
	rtimer: comp_rtimer
		port map (
			CLK => CLK,
			RST => invert(nRST),
			EN => rtimeren,
			MMTRR => mmtrrd,
			MMTRF => mmtrfd,
			MRTR => mrtrd,
			REFRESH => refresh);
			
	dramc: comp_dramc
		port map (
			CLK => CLK,
			RST => invert(nRST),
			EN => dramen,
			nAS => nAS,
			nDS => nDS,
			R_nW => R_nW,
			nRMC => nRMC,
			nSTERM => dramc_nSTERM,
			A => A,
			SA => SA,
			nCAS => nCAS,
			nRAS => nRAS,
			nMOE => nMOE,
			nPD => nPD,
			REFRESH => refresh,
			MMTRR => mmtrrd,
			MMTRF => mmtrfd,
			MMIR => mmird);
			
	cacc: comp_cacc
		port map (
			CLK => CLK,
			RST => invert(nRST),
			EN => caccen,
			nAS => nAS,
			nDS => nDS,
			R_nW => R_nW,
			nRMC => nRMC,
			nSTERM => cacc_nSTERM,
			A => A,
			CA => CA,
			TD => TD,
			nCOE => nCOE,
			nCWE => nCWE,
			HIT => cache_hit);
			
	nSTERM <= dramc_nSTERM and cacc_nSTERM;
	dramen <= dramsp and not cache_hit;
	caccen <= dramsp and nCIIN;

	process(nRST, CLK) is
		variable atemp: std_logic_vector(2 downto 0);
	begin
		if (nRST = '0') then
			
		elsif rising_edge(CLK) then
			if (R_nW = '0') then
				D <= "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ";
				regwbus <= (others => '0');
			end if;
			if (nCS = '0') then
				if (nAS = '0') then
					atemp := A(2 downto 0);
				elsif (nDS = '0') then
					if (R_nW = '0') then  -- Write
						
					else  -- Read
						
					end if;
				end if;
			end if;
		end if;
	end process;
end behavioral;