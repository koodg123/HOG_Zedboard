-- ==============================================================
-- File generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
-- Version: 2016.4
-- Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
-- 
-- ==============================================================

library ieee; 
use ieee.std_logic_1164.all; 
use ieee.std_logic_unsigned.all;

entity computeHistogram0eOg_rom is 
    generic(
             dwidth     : integer := 11; 
             awidth     : integer := 8; 
             mem_size    : integer := 256
    ); 
    port (
          addr0      : in std_logic_vector(awidth-1 downto 0); 
          ce0       : in std_logic; 
          q0         : out std_logic_vector(dwidth-1 downto 0);
          clk       : in std_logic
    ); 
end entity; 


architecture rtl of computeHistogram0eOg_rom is 

signal addr0_tmp : std_logic_vector(awidth-1 downto 0); 
type mem_array is array (0 to mem_size-1) of std_logic_vector (dwidth-1 downto 0); 
signal mem : mem_array := (
    0 => "00000000000", 1 => "00000000101", 2 => "00000001011", 
    3 => "00000010001", 4 => "00000010110", 5 => "00000011100", 
    6 => "00000100010", 7 => "00000100111", 8 => "00000101101", 
    9 => "00000110011", 10 => "00000111000", 11 => "00000111110", 
    12 => "00001000100", 13 => "00001001001", 14 => "00001001111", 
    15 => "00001010101", 16 => "00001011010", 17 => "00001100000", 
    18 => "00001100110", 19 => "00001101011", 20 => "00001110001", 
    21 => "00001110111", 22 => "00001111100", 23 => "00010000010", 
    24 => "00010001000", 25 => "00010001101", 26 => "00010010011", 
    27 => "00010011001", 28 => "00010011110", 29 => "00010100100", 
    30 => "00010101010", 31 => "00010101111", 32 => "00010110101", 
    33 => "00010111011", 34 => "00011000000", 35 => "00011000110", 
    36 => "00011001100", 37 => "00011010001", 38 => "00011010111", 
    39 => "00011011101", 40 => "00011100010", 41 => "00011101000", 
    42 => "00011101110", 43 => "00011110011", 44 => "00011111001", 
    45 => "00011111111", 46 => "00100000100", 47 => "00100001010", 
    48 => "00100010000", 49 => "00100010101", 50 => "00100011011", 
    51 => "00100100001", 52 => "00100100110", 53 => "00100101100", 
    54 => "00100110010", 55 => "00100110111", 56 => "00100111101", 
    57 => "00101000011", 58 => "00101001000", 59 => "00101001110", 
    60 => "00101010100", 61 => "00101011001", 62 => "00101011111", 
    63 => "00101100101", 64 => "00101101010", 65 => "00101110000", 
    66 => "00101110110", 67 => "00101111011", 68 => "00110000001", 
    69 => "00110000111", 70 => "00110001100", 71 => "00110010010", 
    72 => "00110011000", 73 => "00110011101", 74 => "00110100011", 
    75 => "00110101001", 76 => "00110101110", 77 => "00110110100", 
    78 => "00110111010", 79 => "00110111111", 80 => "00111000101", 
    81 => "00111001011", 82 => "00111010000", 83 => "00111010110", 
    84 => "00111011100", 85 => "00111100001", 86 => "00111100111", 
    87 => "00111101101", 88 => "00111110010", 89 => "00111111000", 
    90 => "00111111110", 91 => "01000000011", 92 => "01000001001", 
    93 => "01000001111", 94 => "01000010100", 95 => "01000011010", 
    96 => "01000100000", 97 => "01000100101", 98 => "01000101011", 
    99 => "01000110001", 100 => "01000110110", 101 => "01000111100", 
    102 => "01001000010", 103 => "01001001000", 104 => "01001001101", 
    105 => "01001010011", 106 => "01001011001", 107 => "01001011110", 
    108 => "01001100100", 109 => "01001101010", 110 => "01001101111", 
    111 => "01001110101", 112 => "01001111011", 113 => "01010000000", 
    114 => "01010000110", 115 => "01010001100", 116 => "01010010001", 
    117 => "01010010111", 118 => "01010011101", 119 => "01010100010", 
    120 => "01010101000", 121 => "01010101110", 122 => "01010110011", 
    123 => "01010111001", 124 => "01010111111", 125 => "01011000100", 
    126 => "01011001010", 127 => "01011010000", 128 => "01011010101", 
    129 => "01011011011", 130 => "01011100001", 131 => "01011100110", 
    132 => "01011101100", 133 => "01011110010", 134 => "01011110111", 
    135 => "01011111101", 136 => "01100000011", 137 => "01100001000", 
    138 => "01100001110", 139 => "01100010100", 140 => "01100011001", 
    141 => "01100011111", 142 => "01100100101", 143 => "01100101010", 
    144 => "01100110000", 145 => "01100110110", 146 => "01100111011", 
    147 => "01101000001", 148 => "01101000111", 149 => "01101001100", 
    150 => "01101010010", 151 => "01101011000", 152 => "01101011101", 
    153 => "01101100011", 154 => "01101101001", 155 => "01101101110", 
    156 => "01101110100", 157 => "01101111010", 158 => "01101111111", 
    159 => "01110000101", 160 => "01110001011", 161 => "01110010000", 
    162 => "01110010110", 163 => "01110011100", 164 => "01110100001", 
    165 => "01110100111", 166 => "01110101101", 167 => "01110110010", 
    168 => "01110111000", 169 => "01110111110", 170 => "01111000011", 
    171 => "01111001001", 172 => "01111001111", 173 => "01111010100", 
    174 => "01111011010", 175 => "01111100000", 176 => "01111100101", 
    177 => "01111101011", 178 => "01111110001", 179 => "01111110110", 
    180 => "01111111100", 181 => "10000000010", 182 => "10000000111", 
    183 => "10000001101", 184 => "10000010011", 185 => "10000011000", 
    186 => "10000011110", 187 => "10000100100", 188 => "10000101001", 
    189 => "10000101111", 190 => "10000110101", 191 => "10000111010", 
    192 => "10001000000", 193 => "10001000110", 194 => "10001001011", 
    195 => "10001010001", 196 => "10001010111", 197 => "10001011100", 
    198 => "10001100010", 199 => "10001101000", 200 => "10001101101", 
    201 => "10001110011", 202 => "10001111001", 203 => "10001111110", 
    204 => "10010000100", 205 => "10010001010", 206 => "10010010000", 
    207 => "10010010101", 208 => "10010011011", 209 => "10010100001", 
    210 => "10010100110", 211 => "10010101100", 212 => "10010110010", 
    213 => "10010110111", 214 => "10010111101", 215 => "10011000011", 
    216 => "10011001000", 217 => "10011001110", 218 => "10011010100", 
    219 => "10011011001", 220 => "10011011111", 221 => "10011100101", 
    222 => "10011101010", 223 => "10011110000", 224 => "10011110110", 
    225 => "10011111011", 226 => "10100000001", 227 => "10100000111", 
    228 => "10100001100", 229 => "10100010010", 230 => "10100011000", 
    231 => "10100011101", 232 => "10100100011", 233 => "10100101001", 
    234 => "10100101110", 235 => "10100110100", 236 => "10100111010", 
    237 => "10100111111", 238 => "10101000101", 239 => "10101001011", 
    240 => "10101010000", 241 => "10101010110", 242 => "10101011100", 
    243 => "10101100001", 244 => "10101100111", 245 => "10101101101", 
    246 => "10101110010", 247 => "10101111000", 248 => "10101111110", 
    249 => "10110000011", 250 => "10110001001", 251 => "10110001111", 
    252 => "10110010100", 253 => "10110011010", 254 => "10110100000", 
    255 => "10110100101" );

attribute syn_rom_style : string;
attribute syn_rom_style of mem : signal is "block_rom";
attribute ROM_STYLE : string;
attribute ROM_STYLE of mem : signal is "block";

attribute EQUIVALENT_REGISTER_REMOVAL : string;
begin 


memory_access_guard_0: process (addr0) 
begin
      addr0_tmp <= addr0;
--synthesis translate_off
      if (CONV_INTEGER(addr0) > mem_size-1) then
           addr0_tmp <= (others => '0');
      else 
           addr0_tmp <= addr0;
      end if;
--synthesis translate_on
end process;

p_rom_access: process (clk)  
begin 
    if (clk'event and clk = '1') then
        if (ce0 = '1') then 
            q0 <= mem(CONV_INTEGER(addr0_tmp)); 
        end if;
    end if;
end process;

end rtl;


Library IEEE;
use IEEE.std_logic_1164.all;

entity computeHistogram0eOg is
    generic (
        DataWidth : INTEGER := 11;
        AddressRange : INTEGER := 256;
        AddressWidth : INTEGER := 8);
    port (
        reset : IN STD_LOGIC;
        clk : IN STD_LOGIC;
        address0 : IN STD_LOGIC_VECTOR(AddressWidth - 1 DOWNTO 0);
        ce0 : IN STD_LOGIC;
        q0 : OUT STD_LOGIC_VECTOR(DataWidth - 1 DOWNTO 0));
end entity;

architecture arch of computeHistogram0eOg is
    component computeHistogram0eOg_rom is
        port (
            clk : IN STD_LOGIC;
            addr0 : IN STD_LOGIC_VECTOR;
            ce0 : IN STD_LOGIC;
            q0 : OUT STD_LOGIC_VECTOR);
    end component;



begin
    computeHistogram0eOg_rom_U :  component computeHistogram0eOg_rom
    port map (
        clk => clk,
        addr0 => address0,
        ce0 => ce0,
        q0 => q0);

end architecture;


