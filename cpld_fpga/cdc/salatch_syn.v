// Copyright (C) 1991-2009 Altera Corporation
// Your use of Altera Corporation's design tools, logic functions 
// and other software and tools, and its AMPP partner logic 
// functions, and any output files from any of the foregoing 
// (including device programming or simulation files), and any 
// associated documentation or information are expressly subject 
// to the terms and conditions of the Altera Program License 
// Subscription Agreement, Altera MegaCore Function License 
// Agreement, or other applicable license agreement, including, 
// without limitation, that your use is for the sole purpose of 
// programming logic devices manufactured by Altera and sold by 
// Altera or its authorized distributors.  Please refer to the 
// applicable agreement for further details.

// VENDOR "Altera"
// PROGRAM "Quartus II"
// VERSION "Version 9.0 Build 132 02/25/2009 SJ Web Edition"

// DATE "10/21/2023 22:50:14"

// 
// Device: Altera EPF6010ATC100-1 Package TQFP100
// 

// 
// This greybox netlist file is for third party Synthesis Tools
// for timing and resource estimation only.
// 


module salatch (
	data,
	gate,
	q)/* synthesis synthesis_greybox=0 */;
input 	[11:0] data;
input 	gate;
output 	[11:0] q;

wire gnd;
wire vcc;

assign gnd = 1'b0;
assign vcc = 1'b1;

wire \lpm_latch_component|latches[0]~combout ;
wire \lpm_latch_component|latches[1]~combout ;
wire \lpm_latch_component|latches[2]~combout ;
wire \lpm_latch_component|latches[3]~combout ;
wire \lpm_latch_component|latches[4]~combout ;
wire \lpm_latch_component|latches[5]~combout ;
wire \lpm_latch_component|latches[6]~combout ;
wire \lpm_latch_component|latches[7]~combout ;
wire \lpm_latch_component|latches[8]~combout ;
wire \lpm_latch_component|latches[9]~combout ;
wire \lpm_latch_component|latches[10]~combout ;
wire \lpm_latch_component|latches[11]~combout ;


salatch_lpm_latch_1 lpm_latch_component(
	.latches_0(\lpm_latch_component|latches[0]~combout ),
	.latches_1(\lpm_latch_component|latches[1]~combout ),
	.latches_2(\lpm_latch_component|latches[2]~combout ),
	.latches_3(\lpm_latch_component|latches[3]~combout ),
	.latches_4(\lpm_latch_component|latches[4]~combout ),
	.latches_5(\lpm_latch_component|latches[5]~combout ),
	.latches_6(\lpm_latch_component|latches[6]~combout ),
	.latches_7(\lpm_latch_component|latches[7]~combout ),
	.latches_8(\lpm_latch_component|latches[8]~combout ),
	.latches_9(\lpm_latch_component|latches[9]~combout ),
	.latches_10(\lpm_latch_component|latches[10]~combout ),
	.latches_11(\lpm_latch_component|latches[11]~combout ),
	.data_0(data[0]),
	.gate(gate),
	.data_1(data[1]),
	.data_2(data[2]),
	.data_3(data[3]),
	.data_4(data[4]),
	.data_5(data[5]),
	.data_6(data[6]),
	.data_7(data[7]),
	.data_8(data[8]),
	.data_9(data[9]),
	.data_10(data[10]),
	.data_11(data[11]));

assign q[0] = \lpm_latch_component|latches[0]~combout ;

assign q[1] = \lpm_latch_component|latches[1]~combout ;

assign q[2] = \lpm_latch_component|latches[2]~combout ;

assign q[3] = \lpm_latch_component|latches[3]~combout ;

assign q[4] = \lpm_latch_component|latches[4]~combout ;

assign q[5] = \lpm_latch_component|latches[5]~combout ;

assign q[6] = \lpm_latch_component|latches[6]~combout ;

assign q[7] = \lpm_latch_component|latches[7]~combout ;

assign q[8] = \lpm_latch_component|latches[8]~combout ;

assign q[9] = \lpm_latch_component|latches[9]~combout ;

assign q[10] = \lpm_latch_component|latches[10]~combout ;

assign q[11] = \lpm_latch_component|latches[11]~combout ;

endmodule

module salatch_lpm_latch_1 (
	latches_0,
	latches_1,
	latches_2,
	latches_3,
	latches_4,
	latches_5,
	latches_6,
	latches_7,
	latches_8,
	latches_9,
	latches_10,
	latches_11,
	data_0,
	gate,
	data_1,
	data_2,
	data_3,
	data_4,
	data_5,
	data_6,
	data_7,
	data_8,
	data_9,
	data_10,
	data_11)/* synthesis synthesis_greybox=0 */;
output 	latches_0;
output 	latches_1;
output 	latches_2;
output 	latches_3;
output 	latches_4;
output 	latches_5;
output 	latches_6;
output 	latches_7;
output 	latches_8;
output 	latches_9;
output 	latches_10;
output 	latches_11;
input 	data_0;
input 	gate;
input 	data_1;
input 	data_2;
input 	data_3;
input 	data_4;
input 	data_5;
input 	data_6;
input 	data_7;
input 	data_8;
input 	data_9;
input 	data_10;
input 	data_11;

wire gnd;
wire vcc;

assign gnd = 1'b0;
assign vcc = 1'b1;



flex6k_lcell \latches[0] (
	.dataa(vcc),
	.datab(data_0),
	.datac(latches_0),
	.datad(gate),
	.cin(gnd),
	.cascin(vcc),
	.clk(gnd),
	.aclr(gnd),
	.sclr(gnd),
	.sload(gnd),
	.combout(latches_0),
	.regout(),
	.cout(),
	.cascout());
defparam \latches[0] .lut_mask = "ccf0";
defparam \latches[0] .operation_mode = "normal";
defparam \latches[0] .output_mode = "comb_only";

flex6k_lcell \latches[1] (
	.dataa(vcc),
	.datab(data_1),
	.datac(latches_1),
	.datad(gate),
	.cin(gnd),
	.cascin(vcc),
	.clk(gnd),
	.aclr(gnd),
	.sclr(gnd),
	.sload(gnd),
	.combout(latches_1),
	.regout(),
	.cout(),
	.cascout());
defparam \latches[1] .lut_mask = "ccf0";
defparam \latches[1] .operation_mode = "normal";
defparam \latches[1] .output_mode = "comb_only";

flex6k_lcell \latches[2] (
	.dataa(vcc),
	.datab(data_2),
	.datac(latches_2),
	.datad(gate),
	.cin(gnd),
	.cascin(vcc),
	.clk(gnd),
	.aclr(gnd),
	.sclr(gnd),
	.sload(gnd),
	.combout(latches_2),
	.regout(),
	.cout(),
	.cascout());
defparam \latches[2] .lut_mask = "ccf0";
defparam \latches[2] .operation_mode = "normal";
defparam \latches[2] .output_mode = "comb_only";

flex6k_lcell \latches[3] (
	.dataa(vcc),
	.datab(data_3),
	.datac(latches_3),
	.datad(gate),
	.cin(gnd),
	.cascin(vcc),
	.clk(gnd),
	.aclr(gnd),
	.sclr(gnd),
	.sload(gnd),
	.combout(latches_3),
	.regout(),
	.cout(),
	.cascout());
defparam \latches[3] .lut_mask = "ccf0";
defparam \latches[3] .operation_mode = "normal";
defparam \latches[3] .output_mode = "comb_only";

flex6k_lcell \latches[4] (
	.dataa(vcc),
	.datab(data_4),
	.datac(latches_4),
	.datad(gate),
	.cin(gnd),
	.cascin(vcc),
	.clk(gnd),
	.aclr(gnd),
	.sclr(gnd),
	.sload(gnd),
	.combout(latches_4),
	.regout(),
	.cout(),
	.cascout());
defparam \latches[4] .lut_mask = "ccf0";
defparam \latches[4] .operation_mode = "normal";
defparam \latches[4] .output_mode = "comb_only";

flex6k_lcell \latches[5] (
	.dataa(vcc),
	.datab(data_5),
	.datac(latches_5),
	.datad(gate),
	.cin(gnd),
	.cascin(vcc),
	.clk(gnd),
	.aclr(gnd),
	.sclr(gnd),
	.sload(gnd),
	.combout(latches_5),
	.regout(),
	.cout(),
	.cascout());
defparam \latches[5] .lut_mask = "ccf0";
defparam \latches[5] .operation_mode = "normal";
defparam \latches[5] .output_mode = "comb_only";

flex6k_lcell \latches[6] (
	.dataa(vcc),
	.datab(data_6),
	.datac(latches_6),
	.datad(gate),
	.cin(gnd),
	.cascin(vcc),
	.clk(gnd),
	.aclr(gnd),
	.sclr(gnd),
	.sload(gnd),
	.combout(latches_6),
	.regout(),
	.cout(),
	.cascout());
defparam \latches[6] .lut_mask = "ccf0";
defparam \latches[6] .operation_mode = "normal";
defparam \latches[6] .output_mode = "comb_only";

flex6k_lcell \latches[7] (
	.dataa(vcc),
	.datab(data_7),
	.datac(latches_7),
	.datad(gate),
	.cin(gnd),
	.cascin(vcc),
	.clk(gnd),
	.aclr(gnd),
	.sclr(gnd),
	.sload(gnd),
	.combout(latches_7),
	.regout(),
	.cout(),
	.cascout());
defparam \latches[7] .lut_mask = "ccf0";
defparam \latches[7] .operation_mode = "normal";
defparam \latches[7] .output_mode = "comb_only";

flex6k_lcell \latches[8] (
	.dataa(vcc),
	.datab(data_8),
	.datac(latches_8),
	.datad(gate),
	.cin(gnd),
	.cascin(vcc),
	.clk(gnd),
	.aclr(gnd),
	.sclr(gnd),
	.sload(gnd),
	.combout(latches_8),
	.regout(),
	.cout(),
	.cascout());
defparam \latches[8] .lut_mask = "ccf0";
defparam \latches[8] .operation_mode = "normal";
defparam \latches[8] .output_mode = "comb_only";

flex6k_lcell \latches[9] (
	.dataa(vcc),
	.datab(data_9),
	.datac(latches_9),
	.datad(gate),
	.cin(gnd),
	.cascin(vcc),
	.clk(gnd),
	.aclr(gnd),
	.sclr(gnd),
	.sload(gnd),
	.combout(latches_9),
	.regout(),
	.cout(),
	.cascout());
defparam \latches[9] .lut_mask = "ccf0";
defparam \latches[9] .operation_mode = "normal";
defparam \latches[9] .output_mode = "comb_only";

flex6k_lcell \latches[10] (
	.dataa(vcc),
	.datab(data_10),
	.datac(latches_10),
	.datad(gate),
	.cin(gnd),
	.cascin(vcc),
	.clk(gnd),
	.aclr(gnd),
	.sclr(gnd),
	.sload(gnd),
	.combout(latches_10),
	.regout(),
	.cout(),
	.cascout());
defparam \latches[10] .lut_mask = "ccf0";
defparam \latches[10] .operation_mode = "normal";
defparam \latches[10] .output_mode = "comb_only";

flex6k_lcell \latches[11] (
	.dataa(vcc),
	.datab(data_11),
	.datac(latches_11),
	.datad(gate),
	.cin(gnd),
	.cascin(vcc),
	.clk(gnd),
	.aclr(gnd),
	.sclr(gnd),
	.sload(gnd),
	.combout(latches_11),
	.regout(),
	.cout(),
	.cascout());
defparam \latches[11] .lut_mask = "ccf0";
defparam \latches[11] .operation_mode = "normal";
defparam \latches[11] .output_mode = "comb_only";

endmodule
