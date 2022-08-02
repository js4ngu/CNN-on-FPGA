`include "parameter.v"

module relu(ofmap, ifmap, E, F, C);
	short *ofmap, short *ifmap, int E, int F, int C
	int c = 0, e = 0, f = 0;

	for (c = 0; c<C; c++) begin
		for (e = 0; e<E; e++) begin
			for (f = 0; f<F; f++) begin
				ofmap[((c)*E + e)*F + f] = (ifmap[((c)*E + e)*F + f] > 0) ? ifmap[((c)*E + e)*F + f] : 0;
			end
		end
	end
endmodule

module pool(ofmap, ifmap, E, F, C);
	short *ofmap, short *ifmap, int E, int F, int C
	int c = 0, e = 0, f = 0, k = 0, l = 0;
	short max = 0;
	int _E = 0, _F = 0;
	_E = E / 2;
	_F = F / 2;

	for (c = 0; c<C; c++) begin
		for (e = 0; e<_E; e++) begin
			for (f = 0; f<_F; f++) begin
				max = ifmap[(c*E + (2 * e))*F + (2 * f)];
				for (k = 0; k < 2; k++) begin
					for (l = 0; l < 2; l++) begin
						max = (max > ifmap[(c*E + 2 * e + k)*F + (2 * f) + l]) ? max : ifmap[(c*E + 2 * e + k)*F + (2 * f) + l];
					end
				end
				ofmap[((c)*_E + e)*_F + f] = max;
			end
		end
	end
endmodule

module convolution(ofmap, ifmap, fmap, N, C, M, E, F, R, S, H, 	W, U);
	short *ofmap, short *ifmap, short *fmap, unsigned int N, unsigned int C, unsigned int M, unsigned int E, unsigned int F, unsigned int R, unsigned int S, unsigned int H, unsigned int W, unsigned int U
	unsigned int n = 0, c = 0, m = 0, f = 0, e = 0, r = 0, s = 0;
	int buf = 0;

	// Convolution
	for (n = 0; n < N; n++) begin
		for (c = 0; c < C; c++) begin
			for (m = 0; m < M; m++) begin
				for (f = 0; f < F; f++) begin
					for (e = 0; e < E; e++) begin
						buf = (int)(ofmap[((n*M + m)*E + e)*F + f] * pow(2, SCALE));
						for (r = 0; r < R; r++) begin
							for (s = 0; s < S; s++) begin
								//ofmap[((n*M + m)*E + e)*F + f] += ifmap[((n*C + c)*H + e * U + r)*W + f * U + s] * fmap[((m*C + c)*R + r)*S + s];
								buf += ifmap[((n*C + c)*H + e * U + r)*W + f * U + s] * fmap[((m*C + c)*R + r)*S + s];
							end
						end
						ofmap[((n*M + m)*E + e)*F + f] = (short)(buf * pow(2, -SCALE));
					end
				end
			end
		end
	end
endmodule

module bias(\ofmap, ifmap, bias, N, M, E, F);
	short *ofmap, short *ifmap, short *bias, unsigned int N, unsigned int M, unsigned int E, unsigned int F
	unsigned int n = 0, m = 0, e = 0, f = 0;

	// +Bias
	for (n = 0; n<N; n++) begin
		for (m = 0; m<M; m++) begin
			for (e = 0; e<E; e++) begin
				for (f = 0; f<F; f++) begin
					ofmap[((n*M + m)*E + e)*F + f] = ifmap[((n*M + m)*E + e)*F + f] + bias[m];
endmodule