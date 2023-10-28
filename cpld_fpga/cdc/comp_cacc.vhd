library ieee;

use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- 20-bit Address Direct-Mapped Cache with flexible 128-bit block
-- Fixed 4MiB(data) + 512kiB(tag) Cache Size
-- 32-bit Cache Data Bus Width + 16-bit Cache Tag Data Bus Width
-- Effective address of cache data SRAM: A<21:2> -> CA<19:0>
-- Effective address of tag data SRAM:   A<21:4> -> CA<19:2>
--
-- 10b(TAG) + 20b(DATA) + 2b(32b Data Bus Offset) = 32bit Address Bus
--
-- Tag Data Bus Field Map:
-- TD  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1   0
--    |----VALID----| |DIRTY| |-----------------TAG-----------------|
-- TD15 -> VALID3: Valid bit of upper-upper 32bit cache data block
-- TD14 -> VALID2: Valid bit of upper-middle 32bit cache data block
-- TD13 -> VALID1: Valid bit of lower-middle 32bit cache data block
-- TD12 -> VALID0: Valid bit of lower-lower 32bit cache data block
-- TD11 -> DIRTY1: Dirty bit of upper 64bit cache data block
-- TD10 -> DIRTY0: Dirty bit of lower 64bit cache data block
--
-- Boundary of nCOE transition effect:
--  Transition of nCOE only affects to cache data RAM. That means the data bus
-- of the tag data RAM always gives data to cache controller unless the contr-
-- oller asserts the nCWE signal. So the cache controller can always monitor
-- the data flow of the tag data RAM. This feature can increase the cache tag
-- response speed due to the asynchronous detection of the cache validity.
--
-- Boundary of nCWE transition effect:
--  Unlike nCOE, nCWE signal affects to entire cache module when asserted or
-- negated.
--
-- Cache write policy consideration:
--  Cache controller follows write-back cache policy.
--
-- Method 1. Cache hit validation method:
-- - 1 Check if A<31:22> and TD<9:0> equal.
-- - 2 Check if TD<15:12> equals to data decoded from A<4:3>.
-- - 3 If both conditions are satisfied, the cache block is validated.
--
-- Method 2. Cached memory read method(cache miss):
-- - 1 Store TD<15:0>.
-- - 2 Assert nCWE.
-- - 3 Check if A<31:22> and TD<9:0> equal.
-- - 4 If equal, assert appropriate bit of TD<15:12>.
-- - 5 If not,
-- - 5.1 If one or both of the TD<11:10> bits are asserted, run write-back met-
--       hod(Method 8).
-- - 5.2 Set TD<9:0> to A<31:22>,
--           TD<15:12> to decoded A<4:3>, and
--           clear TD<11:10>.
-- - 6 Wait until DRAM controller signal which indicates D<31:0> is valid.
-- - 7 Negate nCWE
--
-- Method 3. Cached memory read method(cache hit):
-- - 1 Send cancellation signal of read operation to DRAM Controller.
--
-- Method 4. Cached memory write method(cache miss):
-- - 1 Store TD<15:0>
-- - 2 Assert nCWE.
-- - 3 Check if A<31:22> and TD<9:0> equal.
-- - 4 If equal, assert appropriate bit of TD<15:12> and TD<11:10>.
-- - 5 if not,
-- - 5.1 If one or both of the TD<11:10> bits are asserted, run write-back met-
--       hod(Method 6).
-- - 5.2 Set TD<9:0> to A<31:22>,
--           TD<15:12> to decoded A<4:3>, and
--           TD<11:10> to decoded A4.
-- - 6 Negate nCWE
--
-- Method 5. Cached memory write method(cache hit):
-- - 1 Store TD<15:0>.
-- - 2 Assert nCWE.
-- - 3 Assert appropriate bits of TD<15:10>.
-- - 4 Negate nCWE.
--
-- Method 6. Cached memory read-modify-write cycle method(cache miss):
-- - 1 Store TD<15:0>.
-- - 2 Assert nCWE.
-- - 3 Check if A<31:22> and TD<9:0> equal.
-- - 4 If equal, assert appropriate bit of TD<15:10>.
-- - 5 If not,
-- - 5.1 If one or both of the TD<11:10> bits are asserted, run write-back met-
--       hod(Method 8).
-- - 5.2 Set TD<9:0> to A<31:22>,
--           TD<15:12> to decoded A<4:3>, and
--           TD<11:10> to decoded A4.
-- - 6 Wait for the transmission of the modified data. 
-- - 7 Negate nCWE.
--
-- Method 7. Cached memory read-modify-write cycle method(cache hit):
-- - 1 Send cancellation signal of read operation to DRAM Controller.
-- - 2 Store TD<15:0>.
-- - 3 Assert nCWE.
-- - 4 Assert appropriate bits of TD<11:10>.
-- - 5 Wait for the transmission of the modified data. 
-- - 6 Negate nCWE.
--
-- Method 8. Cache write-back method from cache to DRAM:
-- - 1 TBD
--
-- TD<15:10>(VALID/DIRTY) bit behavior table when write-back operation:
-- TD 15 14 13 12 11 10 Behavior
--     x  x  x  x  0  0 Skip operation.
--     x  x  0  0  0  1 Negate TD10 and skip operation.
--     x  x  0  1  0  1 Write lword to BASE*.
--     x  x  1  0  0  1 Write lword to BASE* + 1.
--     x  x  1  1  0  1 Write lwords to BASE* + 0 and 1.
--     0  0  x  x  1  0 Negate TD11 and skip operation.
--     0  1  x  x  1  0 Write lword to BASE* + 2.
--     1  0  x  x  1  0 Write lword to BASE* + 3.
--     1  1  x  x  1  0 Write lwords to BASE* + 2 and 3.
--     0  0  0  0  1  1 Negate TD11 and TD10 and skip operation.
--     0  0  0  1  1  1 Negate TD11 and write lword to BASE*.
--     0  0  1  0  1  1 Negate TD11 and write lword to BASE* + 1.
--     0  0  1  1  1  1 Negate TD11 and write lwords to BASE* + 0 and 1.
--     0  1  0  0  1  1 Negate TD10 and write lword to BASE* + 2.
--     0  1  0  1  1  1 Write lwords to DRAM Address BASE* + 0 and 2.
--     0  1  1  0  1  1 Write lwords to DRAM Address BASE* + 1 and 2.
--     0  1  1  1  1  1 Write lwords to DRAM Address BASE* + 0, 1, and 2.
--     1  0  0  0  1  1 Negate TD10 and write lword to BASE* + 3.
--     1  0  0  1  1  1 Write lwords to DRAM Address BASE* + 0 and 3.
--     1  0  1  0  1  1 Write lwords to DRAM Address BASE* + 1 and 3.
--     1  0  1  1  1  1 Write lwords to DRAM Address BASE* + 0, 1, and 3.
--     1  1  0  0  1  1 Negate TD10 and write lwords to BASE* + 2 and 3.
--     1  1  0  1  1  1 Write lwords to DRAM Address BASE* + 0, 2, and 3.
--     1  1  1  0  1  1 Write lwords to DRAM Address BASE* + 1, 2, and 3.
--     1  1  1  1  1  1 Write entire cache block to DRAM Address BASE* + n.
-- *BASE: [TD<9:0>] * 2^{20} + [A<21:2>] * 2^{2}
--

entity comp_cacc is
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
		-- Cache Module Control Signals
		CA: out std_logic_vector(19 downto 0);
		TD: inout std_logic_vector(15 downto 0);
		nCOE: out std_logic := '1';
		nCWE: out std_logic := '1';
		HIT: out std_logic := '0');
end comp_cacc;

architecture behavioral of comp_cacc is
begin
	CA <= A(21 downto 2);
	
	process(RST, CLK) is
		type state_t is (state_idle, state_miss, state_finished);
		
		variable state: state_t := state_idle;
		variable step: std_logic_vector(3 downto 0) := x"0";
	begin
		if (RST = '1') then
			nCOE <= '1';
			nCWE <= '1';
		elsif rising_edge(CLK) then
			if (EN = '1') then
				case state is
					when state_idle =>
						-- Check if cache hit
						if (A(31 downto 22) = TD(9 downto 0)) then  -- Tag Hit
							if (TD(to_integer(unsigned(A(3 downto 2))) + 12) = '1') then
								-- Cache Hit
								nCOE <= '0';
								nSTERM <= '0';
								HIT <= '1';
								
								state := state_finished;
							else
								state := state_miss;  -- Cache Miss (TD<9:0> OK)
							end if;
							state := state_miss;  -- Cache Miss
						end if;
					when state_miss =>
						-- Flush and refill the cache block
						case step is
							when x"0" =>
							when x"1" =>
							when x"2" =>
							when x"3" =>
							when others =>
								null;
						end case;
					when others =>
						null;
				end case;
			else
				state := state_idle;
				nCOE <= '1';
				nSTERM <= '1';
				HIT <= '0';
			end if;
		elsif falling_edge(CLK) then
			if (EN = '1') then
				case state is
					when state_miss =>
						-- Flush and refill the cache block
						case step is
							when x"0" =>
							when x"1" =>
							when x"2" =>
							when x"3" =>
							when others =>
								null;
						end case;
					when others =>
						null;
				end case;
			end if;
		end if;
	end process;
end behavioral;
