`include "parameter.v"


module Classfication()
    reg ofmap_img_opt[4:0][10]
    reg max_val_s[3:0];
    reg data_index[15:0];
    reg estimated_label[15:0];
    reg ofmap[3:0][9:0];
    integer n,m,e,f;

    max_val_s = ofmap[0];
    data_index = 0;
    for (n = 0; n<1; n++) begin
        for (m = 0; m<10; m++) begin
            for (e = 0; e<1; e++) begin
                for (f = 0; f<1; f++) begin
                    ofmap_img_opt[data_index] = ofmap[((n + m) + f) + e];
                    if (ofmap[((n + m) + f) + e] >= max_val_s) begin
                        max_val_s = ofmap[((n + m) + f) + e];
                        estimated_label = m;
                    end
                    data_index <= data_index + 1;;
                end
            end
        end
    end
endmodule