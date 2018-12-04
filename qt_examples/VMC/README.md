# VMC

Here's different examples how you can perform VMC calculations. The examples found here also serves as examples to parallel processing.

### VMC in C++ with MPI
In the folder `cpp_mpi` there is a showcase of a VMC object-oriented code utilizing MPI.

### VMC in C++ with OpenMP
In the folder `cpp_openmp` there is a showcase of a VMC object-oriented code utilizing OpenMP.

### VMC in Python with Multiprocessing
In the folder `cpp_openmp` there is a showcase of a VMC object-oriented python code utilizing _Multiprocessing_.

Resources for Multiprocessing can be found at:
* [Official Python3.6 guide](https://docs.python.org/3.4/library/multiprocessing.html). A recommended reading is the part about _Shared Memory_
* https://sebastianraschka.com/Articles/2014_multiprocessing.html
* https://pymotw.com/2/multiprocessing/basics.html

### VMC in Python with mpi4py
In the folder `cpp_openmp` there is a showcase of a VMC object-oriented python code utilizing _mpi4py_.

In order to make mpi4py to work, you will need [Conda](https://conda.io/docs/user-guide/install/index.html#regular-installation). After conda is installed, I _highly_ recommend creating a Python environment as following,
```
$ conda create -n env-mpi4py python=3.6.0 
```
Then, to active your environment, type
```
$ source activate env-mpi4py
```
You can now safely install packages in this environment without having them interfere with the rest of your system.
```
$ conda install numpy mpi4py matplotlib
```
To deactivate your environment, type
```
$ source deactivate
```

Resources for mpi4py can be found at:
* [Official mpi4py tutorial](https://mpi4py.readthedocs.io/en/stable/tutorial.html)

### VMC in Python with Numba
In the folder `cpp_openmp` there is a showcase of a VMC object-oriented python code utilizing _Numba_.

Resources for Numba can be found at:
* [Official Numba Tutorial](http://numba.pydata.org/numba-doc/0.12.2/tutorial_firststeps.html)
* [Introduction to Jit from Computational Statistics at Duke University](http://people.duke.edu/~ccc14/sta-663-2016/18C_Numba.html#Pre-compilation-by-giving-specific-signature)


### Future improvements
- [ ] Implement numba for multiprocessing and mpi4py as well, as that should dramatically boost the run-times.