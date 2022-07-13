	component proj_qsys is
		port (
			clk_clk : in std_logic := 'X'  -- clk
		);
	end component proj_qsys;

	u0 : component proj_qsys
		port map (
			clk_clk => CONNECTED_TO_clk_clk  -- clk.clk
		);

