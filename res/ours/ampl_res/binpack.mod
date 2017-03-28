var open{j in BINS} >=0, <=1;
var x{i in ITEMS, j in BINS} >=0, <=1, integer;

minimize Bins: sum {j in BINS} open[j];

subject to must_pack{i in ITEMS}: sum{j in BINS} x[i,j] = 1;

subject to Bin_size{j in BINS}: sum {i in ITEMS} x[i,j]*size[i] <= bin_size;
subject to open_bins {i in ITEMS, j in BINS}: x[i,j]<=open[j]

