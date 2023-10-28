library ieee;

use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- CPU Address to DRAM Address Mux Mapping Table
--
-- Common for all memory bank capacity:
--  SA  11  10   9   8   7   6   5   4   3   2   1   0
-- CAS A25 Axx Axx A10  A9  A8  A7  A6  A5  A4  A2  A3
-- RAS A24 Axx Axx Axx A19 A18 A17 A16 A15 A14 A12 A13
--
-- 256k / 512k:
--  SA  10   9   8
-- CAS A23 A21 A10
-- RAS A22 A20 A11
--
-- 1M / 2M:
--  SA  10   9   8
-- CAS A23 A11 A10
-- RAS A22 A21 A20
--
-- 4M / 8M / 16M:
--  SA  10   9   8
-- CAS A12 A11 A10
-- RAS A23 A21 A20
--
-- CAS/RAS Connection Diagram
--      +----+ +----+ +----+ +----+
-- nCAS0|    | |    | |    | |    |
-- -----|    | |    | |    | |    |
-- nCAS1|    | |    | |    | |    |
-- -----|CONN| |CONN| |CONN| |CONN|
-- nCAS2| 01 | | 02 | | 03 | | 04 |
-- -----|    | |    | |    | |    |
-- nCAS3|    | |    | |    | |    |
-- -----|    | |    | |    | |    |
--      +----+ +----+ +----+ +----+
-- nRAS0 |  |   |  |   |  |   |  |
-- ------+  |   |  |   |  |   |  |
-- nRAS1    |   |  |   |  |   |  |
-- ---------+   |  |   |  |   |  |
-- nRAS2        |  |   |  |   |  |
-- -------------+  |   |  |   |  |
-- nRAS3           |   |  |   |  |
-- ----------------+   |  |   |  |
-- nRAS4               |  |   |  |
-- --------------------+  |   |  |
-- nRAS5                  |   |  |
-- -----------------------+   |  |
-- nRAS6                      |  |
-- ---------------------------+  |
-- nRAS7                         |
-- ------------------------------+
--
-- CPU Address to nRAS Encoded Signal Mapping Table
-- Bank Size Address Lines 
--      256k      A<19:17>
--      512k      A<20:18>
--        1M      A<21:19>
--        2M      A<22:20>
--        4M      A<23:21>
--        8M      A<24:22>
--       16M      A<25:23>
--       32M      A<26:24>
--       64M      A<27:25>
--      128M      A<28:26>
--
-- Memory Module Size Regsiter / MMSR
-- MMSR Field Table
-- 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
-- |---BSZ---| BC MMCNT |-------Reserved------| FE
--
-- BSZ: Size per Memory Bank
-- Bank Size BSZ<3:0>
--       N/A  0 0 0 0
--      256k  0 0 0 1
--      512k  0 0 1 0
--        1M  0 0 1 1
--        2M  0 1 0 0
--        4M  0 1 0 1
--        8M  0 1 1 0
--       16M  0 1 1 1
--       32M  1 0 0 0
--       64M  1 0 0 1
--      128M  1 0 1 0
--  Reserved  1 0 1 1
--  Reserved  1 1 0 0
--  Reserved  1 1 0 1
--  Reserved  1 1 1 0
--  Reserved  1 1 1 1
-- Formula: log_{2}{SIZE}-17
--          Where SIZE is Bank Size
--
-- BC: Bank Count per Memory Module (decreased by 1)
--
-- MMCNT: Memory Module Count (decreased by 1)
-- Filled from Connector 1 to 4
--
-- FE: FPM / EDO Select
-- 0: FPM, 1: EDO
--
-- Total DRAM Size Calculation:
-- Formula: 2^{<BSZ> + 17} * (<BC> + 1) * (<MMCNT> + 1)  # from register
--
--
-- Memory Module Timing Regsiter (Rising Edge) / MMTRR
-- MMTRR Field Table
-- 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16
-- 
-- 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
-- 
--
-- Memory Module Timing Regsiter (Falling Edge) / MMTRF
-- MMTRF Field Table
-- 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16
-- 
-- 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
-- 
--
-- Memory Refresh Timing Register / MRTR
-- MRTR Field Table
-- 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16
-- |--------CBR Refresh Period-------| |----------
-- 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
-- ---------Cell Discharge Threshold-------------|
--
-- Each field of the MRTR, MMTRR and MMTRF is coefficient of whole-cycle period
-- decreased by 1. (ex: 20ns for 50MHz clock)
--
--  Mixed combination of the critical parameter(Capacity, Timing) is not allowed
-- unless the configuration which is compatible to every single memory module
-- installed.
--
-- Cycle 1. Single Read
-- - 1 
-- Cycle 2. Single Write
-- Cycle 3. Single Read-Modify-Write
-- Cycle 4. Burst Read
-- Cycle 5. Burst Write
-- Cycle 6. Burst Read-Modify-Write
--
-- Note: Some timing-related procedures are omitted.
-- Method 1. Read
-- - 1 Check if row address of previous and current are equal or the nRAS hold
--     time has reached its limit.
-- - 2 If row addresses are not equal or hold time has exceeded the limit,
-- - 2.1 Negate nRAS.
-- - 2.2 Set SA<11:0> to corrosponding row address value.
-- - 2.3 Assert nRAS.
-- - 3 Set SA<11:0> to corrosponding column address value.
-- - 4 Assert nCAS.
-- - 5 Wait tCAC.
-- - 6 Send valid signal.
-- - 7 Negate nCAS.
--
-- Method 2. Write
-- Method 3. Refresh
--
-- Every transfer cycle starts at rising edge.

entity comp_dramc is
	port (
		------------------------------------------------------------------------
		-- Component Control Signals
		CLK: in std_logic;
		RST: in std_logic;
		EN: in std_logic;

		------------------------------------------------------------------------
		-- Processor Local Bus Signals
		nAS: in std_logic;
		nDS: in std_logic;
		R_nW: in std_logic;
		nRMC: in std_logic;
		nSTERM: out std_logic;
		A: in std_logic_vector(31 downto 0);

		------------------------------------------------------------------------
		-- 72pin 5V SIMM DRAM Control Signals
		SA: out std_logic_vector(11 downto 0);
		nCAS: out std_logic_vector(3 downto 0) := x"F";
		nRAS: out std_logic_vector(7 downto 0) := x"FF";
		nMOE: out std_logic;
		nMWE: out std_logic;
		nPD: in std_logic_vector(3 downto 0);
		
		------------------------------------------------------------------------
		-- Refresh Signal
		REFRESH: in std_logic;
		
		------------------------------------------------------------------------
		-- Register Data Signals
		MMTRR: in std_logic_vector(31 downto 0);
		MMTRF: in std_logic_vector(31 downto 0);
		MMIR: in std_logic_vector(31 downto 0));
end comp_dramc;

architecture behavioral of comp_dramc is
begin
	process(RST, CLK, REFRESH) is
		type state_t is (state_idle, state_ras, state_cas, state_finished, state_refreshing);
		
		variable state: state_t := state_idle;
		variable rowaddr: std_logic_vector(11 downto 0) := x"000";
		variable rowvalid: std_logic := '0';
		variable rowholdtimer: unsigned(13 downto 0) := "00000000000000";
		variable step: std_logic_vector(3 downto 0) := x"0";
	begin
		if (RST = '1') then
			state := state_idle;
			rowaddr := x"000";
			rowvalid := '0';
			rowholdtimer := "00000000000000";
			step := x"0";
		elsif rising_edge(CLK) then
			if (EN = '1') then
				-- DRAM Transfer Cycle (Rising Edge)
				case state is
					when state_idle =>
					when state_ras =>
						case step is
							when x"1" =>
								nRAS <= x"00";
							when others =>
								null;
						end case;
					when state_cas =>
						case step is
							when x"1" =>
								nCAS <= x"0";
							when others =>
								null;
						end case;
					when others =>
						
				end case;
			else
				nCAS <= x"F";
			end if;
			if (rowaddr /= A(31 downto 20) or rowvalid /= '1') then
				nRAS <= x"FF";
			end if;
		elsif falling_edge(CLK) then
			if (EN = '1') then
				-- DRAM Transfer Cycle (Falling Edge)
				case state is
					when state_idle =>
						if (rowaddr = A(31 downto 20) and rowvalid = '1') then
							state := state_cas;
						else
							state := state_ras;
							rowaddr := A(31 downto 20);
							rowvalid := '1';
							rowholdtimer := "00000000000000";
						end if;
					when state_ras =>
						case step is
							when x"0" =>
								SA <= rowaddr;
								step := x"1";
							when x"1" =>  -- Finish Cycle
								state := state_cas;
								step := x"0";
							when others =>
								null;
						end case;
					when state_cas =>
						case step is
							when x"0" =>
								SA <= A(19 downto 8);
								step := x"1";
							when x"1" =>
								step := x"2";
							when x"2" =>  -- Finish Cycle
								nSTERM <= '0';
								state := state_idle;
								step := x"0";
							when others =>
								null;
						end case;
					when others =>
						SA <= x"000";
						step := x"0";
				end case;
			else
				nSTERM <= '1';
				SA <= x"000";
				step := x"0";
			end if;
			
			if (rowholdtimer /= "00000000100000") then
				rowholdtimer := rowholdtimer + 1;
			else
				rowholdtimer := "00000000000000";
				rowvalid := '0';
			end if;
		elsif rising_edge(REFRESH) then
			
		end if;
	end process;
	
end behavioral;
