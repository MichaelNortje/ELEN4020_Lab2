#ELEN4020 Laboratory 2
**Data Intensive Computing for Data Science**

***Tyson Cross      1239448*** <br>
***Michael Nortje   1389486*** <br>
**Joshua Isserow      675720** <br>

Source repository: <i>https://github.com/MichaelNortje/ELEN4020_Lab2.git<i>
## Build and Run Instructions
The code requires the OpenMP and PThreads libraries, and the g++ compiler to be installed. We suggest using [CMake](https://cmake.org/) to build the executable. Download the [latest release](https://cmake.org/download/), or install with a package manager.

Once CMake is installed, run the following from the location where this git repo was cloned to:
<pre><code>$ mkdir build
$ cd build
$ cmake ..
$ make
</code></pre>

To run the compiled executable run the following command from within the build folder:
<pre><code>$ ./lab2
</code></pre>
It will generate a file *timings.txt* with the results from the square matrix transpositions algorithms, for a range of [N_0 x N_1] matrices, where N_0 = N_1 = [128, 1024, 2048, 4096]. 

### Code documentation
Doxygen documentation can be found under the **docs/html** folder, in the location where the git repo was cloned to. Use **docs/html/index.html** to access fully commented code listings along with function and class information.

### Additional Notes
Please make sure that your ENV variable OMP\_NUM\_THREADS is set to a sensible value (we suggest 8 for a 4-core machine with hyperthreading). You can check the value with
<pre><code>$ echo $OMP\_NUM\_THREADS</code></pre>
and set it with
<pre><code>$ export $OMP\_NUM\_THREADS=8</code></pre>

<br>
<i>Addtional commandline options:<i>
<pre><code>$ ./lab2 [-v][--verbose] [-l][--long]
</code></pre>
<pre><code>    -v, -- verbose  <br>
			Output additional timing information <br>
    -l, --long  <br>
			Use longer timing sequences for N_0 = N_1 = [64, 128, 256, 512, ... , 8192, 16384, 32768]
</code></pre>