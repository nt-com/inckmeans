## incremental k-means

The incremental k-means clustering algorithm in C for 3 dimensions.

Features:

- extensive inline documentation
- outputs a data file for plotting after categorization
- supports euclidean and manhattan distance metrics
- operates on random data for testing the algorithm

Usage: cd src && make

- configuration is done in src/kmeans_cfg.h, including verbose output
- the number of points for the learning and categorization phases are set in src/main.c
- writes the categorized data to 
- "data/clustering.dat" contains an example file, showing the format the data is saved in
- compiled with gcc under Linux

#### nt-com
