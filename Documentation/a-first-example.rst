.. _a_first_example:

A first example
===============

This tutorial will guide you through the steps of your first SeisSol
simulation. We will use the `SCEC TPV33
benchmark <http://scecdata.usc.edu/cvws/tpv33docs.html>`__ as an example
in this tutorial. We assume that you have successfully :ref:`compiled SeisSol 
<Compiling_and_running_seissol>`.

This tutorial is targeted to people who have compiled SeisSol and want 
to test their installation for the first time. If you are completely new
to SeisSol and want to explore its features, we recommend our `training 
material <https://github.com/SeisSol/Training>`__, which bundles a pre-compiled
version of SeisSol and some scenarios.


Setup
-----

*  Clone our examples repository: https://github.com/SeisSol/Examples/.

*  Navigate to the folder ``Examples/tpv33``. We will refer to this directory as 
   `working directory` in the following.

*  Download the mesh files from `<https://zenodo.org/record/8042664>`__ and
   store them in the working directory.

*  You can visualize the mesh file with `paraview <https://www.paraview.org/>`__,
   using e.g. ``paraview tpv33_half_sym.xdmf``. The mesh 
   is described by two files: ``tpv33_half_sym`` and ``tpv33_half_sym.xdmf``.
   The first one is a binary file, which contains all the data (e.g. 
   coordinates, connectivity) and the ``xdmf`` file contains information 
   on how to read that data for visualization software such as Paraview.
   You can read more about this mesh format here: :ref:`PUML_mesh_format`.

*  Create the output directory: ``mkdir output``. 

*  **Optional** To create the mesh on your own, execute ``./generating_the_mesh.sh``. 
   To do so, you need to install `gmsh <https://gmsh.info>`__, `PUMGen 
   <https://github.com/SeisSol/PUMGen>`__ and `mirrorMesh 
   <https://github.com/SeisSol/Meshing/tree/master/mirrorMesh>`__.    

*  **Optional:** For performance reasons, we suggest that you store large
   files (mesh, output) in a scratch file system (if one is available at your cluster) 
   and create symbolic links in your working directory:

   .. code-block:: bash

     ln -s <path/to/tpv33_half_sym> tpv33_half_sym
     ln -s <path/to/output/directory> output

   You may not see a huge difference in this small test case but for larger
   meshes, this is the recommended strategy. 

Execution
---------

*  Link the SeisSol binary to your working directory (``Examples/tpv33``).

*  Now run: ``export OMP_NUM_THREADS=<threads>``, where ``<threads>`` is the
   number of threads. If you are on a single node machine, you should 
   compile SeisSol with ``-DCOMMTHREAD=OFF`` and use the maximum number of threads
   available. If you run SeisSol on a cluster, you should compile it with ``-DCOMMTHREAD=ON``.
   Then you should set the number of OMP threads to the number of available threads
   minus 1.

*  Now run: ``mpiexec -np <n> ./SeisSol_<configuration> parameters.par``, where:

   *  ``<n>`` is the number of MPI ranks / the number of compute nodes used.

   *  ``<configuration>`` depends on your compilation setting (e.g. SeisSol_Release_dhsw_4_elastic for a Haswell architecture and order 4 accuracy in space and time).

**Hint:** Depending on the system you are using, the MPI launcher might
be different from ``mpiexec`` (e.g. ``mpiexec.hydra``, ``mpirun``, ``srun``).
For more infos about how to get optimal performance, have a look at the :ref:`optimal_environment_variables_on_supermuc_ng`.

Result verification
-------------------

SeisSol produces various output files:

* :ref:`3D wave field output <wave_field_output>` (:code:`.xdmf`)
* :ref:`2D free surface output <free_surface_output>` (:code:`-surface.xdmf`)
* :ref:`2D fault output <paraview_output>` (:code:`-fault.xdmf`)
* :ref:`off_fault_receivers` (:code:`-receiver-<id>.dat`)
* :ref:`Fault receivers <fault_receivers>` (:code:`-faultreceiver-<id>.dat`)
* :ref:`energy_output` (:code:`-energy.csv`)

The :code:`xdmf` files can be visualized with `Paraview <https://www.paraview.org/>`__.
For the :code:`dat` files, you can use `viewrec <https://github.com/SeisSol/SeisSol/blob/master/postprocessing/visualization/receiver/bin/viewrec>`__.

The outputs of your simulation can be compared with our outputs (using SeisSol) and the outputs of other codes by checking out the uploaded files for this SCEC benchmark on the SCEC Code Verification Project `website <http://scecdata.usc.edu/cvws/cgi-bin/cvws.cgi>`__.
