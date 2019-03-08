#ELEN4020 Laboratory 2
**Data Intensive Computing for Data Science**

***Tyson Cross      1239448*** <br>
***Michael Nortje   1389486*** <br>
**Joshua Isserow      675720** <br>


## Build and Run Instructions
The code requires the OpenMP and PThreads libraries, along with g++ to be installed. We suggest using [CMake](https://cmake.org/) to build the executable. Download the [latest release](https://cmake.org/download/).

Once CMake is installed, run the following from the location where the git repo was cloned to:
<pre><code>$ mkdir build
$ cd build
$ cmake ..
$ make
</code></pre>

To run the compiled executable run the following command from within the build folder:
<pre><code>./lab2 
</code></pre>
It will generate a file *timings.txt* with the results from the square matrix transpositions algorithms, for a range of [N_o x N_1] matrices, where N_o = N_1, and N_1 = [128, 1024, 2048, 4096].