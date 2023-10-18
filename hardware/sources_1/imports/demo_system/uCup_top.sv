//////////////////////////////////////////////////////////////////////////
//																		//
//	Engineer:       Stefano Mercogliano, stefano.mercogliano@unina.it	//
//																		//
//////////////////////////////////////////////////////////////////////////

// uCup TOP instantiates cv32e41s demo systems
// 1 - Without memories for the Verilated TB
// 2 - With memories for the FPGA synthesis


module uCup_top #(
  parameter int Verilated    = 1,
  parameter int GpiWidth     = 8,
  parameter int GpoWidth     = 16,
  parameter int PwmWidth     = 12,
	parameter int ExtMemPorts  = 2,
  parameter     SRAMInitFile = ""

) (
  input logic                 clk_sys_i,
  input logic                 rst_sys_ni,

  // Basic Peripherals IO
  input  logic [GpiWidth-1:0] gp_i,
  output logic [GpoWidth-1:0] gp_o,
  output logic [PwmWidth-1:0] pwm_o,
  input  logic                uart_rx_i,
  output logic                uart_tx_o,
  input  logic                spi_rx_i,
  output logic                spi_tx_o,
  output logic                spi_sck_o,

	// Memory Interfaces for uCup Verilated TB
  output logic        mem_req_o 		[ExtMemPorts-1:0],
  output logic        mem_we_o 			[ExtMemPorts-1:0],
  output logic [ 3:0] mem_be_o 			[ExtMemPorts-1:0],
  output logic [31:0] mem_addr_o 		[ExtMemPorts-1:0],
  output logic [31:0] mem_wdata_o 	[ExtMemPorts-1:0],
  input  logic        mem_rvalid_i 	[ExtMemPorts-1:0],
  input  logic [31:0] mem_rdata_i 	[ExtMemPorts-1:0]

);

	if(Verilated) begin

		cv32e41s_demo_system_memless #(
			.GpiWidth 				( GpiWidth 			),
			.GpoWidth 				( GpoWidth 			),
			.PwmWidth 				( PwmWidth 			),
			.SRAMInitFile 			( SRAMInitFile 		),

			.CoreBootAddr   		( 32'h00100080 		),
			.CoreMtvecAddr  		( 32'h00100000		),
			.CoreHartid     		( 0					),
			.CoreMimpid     		( 0 				),
			.CoreDbgNumTriggers		( 1 				),
			.CorePmaNumRegions		( 0 				),
			.CorePmpGranularity 	( 0 				),
			.CorePmpNumRegions		( 16 				),
			.CoreClicEn         	( 0 				),
			.CoreClicIdWidth    	( 5 				),
			.CoreClicIntthreshbits	( 8					)

		) u_soc (
			.clk_sys_i		( clk_sys_i 		),
			.rst_sys_ni		( rst_sys_ni 		),

			.gp_i			( gp_i 				),
			.gp_o			( gp_o 				),
			.pwm_o			( pwm_o 			),
			.uart_rx_i		( uart_rx_i 		),
			.uart_tx_o		( uart_tx_o 		),
			.spi_rx_i		( spi_rx_i 			),
			.spi_tx_o		( spi_tx_o 			),
			.spi_sck_o		( spi_sck_o 		),
			.mem_req_o 		( mem_req_o 		),
  			.mem_we_o 		( mem_we_o 			),
  			.mem_be_o 		( mem_be_o 			),
  			.mem_addr_o 	( mem_addr_o		),
  			.mem_wdata_o 	( mem_wdata_o 		),
  			.mem_rvalid_i 	( mem_rvalid_i 		),
  			.mem_rdata_i 	( mem_rdata_i 		)

	);

	end else begin

		cv32e41s_demo_system #(
			.GpiWidth 				( GpiWidth 			),
			.GpoWidth 				( GpoWidth 			),
			.PwmWidth 				( PwmWidth 			),
			.SRAMInitFile 			( SRAMInitFile 		),

			.CoreBootAddr   		( 32'h70000000 		),
			.CoreMtvecAddr  		( 32'h00100000		),
			.CoreHartid     		( 0					),
			.CoreMimpid     		( 0 				),
			.CoreDbgNumTriggers		( 1 				),
			.CorePmaNumRegions		( 0 				),
			.CorePmpGranularity 	( 0 				),
			.CorePmpNumRegions		( 16 				),
			.CoreClicEn         	( 0 				),
			.CoreClicIdWidth    	( 5 				),
			.CoreClicIntthreshbits	( 8					)

		) u_soc (
			.clk_sys_i		( clk_sys_i 		),
			.rst_sys_ni		( rst_sys_ni 		),

			.gp_i			( gp_i 				),
			.gp_o			( gp_o 				),
			.pwm_o			( pwm_o 			),
			.uart_rx_i		( uart_rx_i 		),
			.uart_tx_o		( uart_tx_o 		),
			.spi_rx_i		( spi_rx_i 			),
			.spi_tx_o		( spi_tx_o 			),
			.spi_sck_o		( spi_sck_o 		)
		);

		for(genvar i = 0; i < ExtMemPorts; i++ ) begin
			assign mem_req_o[i] 	= '0;
			assign mem_we_o[i] 		= '0;
			assign mem_be_o[i] 		= '0;
			assign mem_addr_o[i] 	= '0;
			assign mem_wdata_o[i] 	= '0;
		end

	end




endmodule


