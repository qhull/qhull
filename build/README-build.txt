qhull/build/README-build.txt

See qhull/README.txt for building with CMake, DevStudio, make, and Qt

This directory contains 
  build/config.cmake.in // extract target variables for CMake
  build/qhull.pc.in    // pkg-config template for creating lib/pkgconfig/qhull*.pc
  build/qhull-32.sln   // 32-bit DevStudio solution and project files (2010 and later)
  build/*-32.vcxproj
  build/qhull-64.sln   // 64-bit DevStudio solution and project files (2010 and later)
  build/*-64.vcxproj
  build/qhull.sln      // DevStudio solution and project files (2005 and 2009)
  build/*.vcproj
  build/qhulltest/*vcxproj // 32-bit and 64-bit DevStudio project files for building qhulltest with Qt
  build/qhulltest/qhulltest*.vc*proj  // DevStudio 2005 and 2009 project files for building qhulltest with Qt
  build/CMakeModules/CheckLFS.cmake // enables Large File Support in CMake

The following build targets are _deprecated_ and are not included in the Qhull builds
  build/libqhull-??.vcxproj // Non-reentrant Qhull
  build/libqhull.vcproj     //   Replaced by qhullstatic
  src/libqhull/libqhull.pro
  CMakeLists.txt#libqhull
  build/qhull_p-??.vcxproj  // Pointer version of non-reentrant Qhull (qh_QHpointer).
  build/qhull_p.vcproj      //   Replaced by qhull_r
  CMakeLists.txt#qhull_p
  CMakeLists.txt#qhullp	    // 'qhull' linked with pointer version of non-reentrant Qhull
  CMakeLists.txt#user_egp   // 'user_eg' linked with pointer version of non-reentrant Qhull
  
CMake writes intermediate files into these directories
  build/CMakeFiles/	// Intermediate files produced by CMake
  build/QhullExport/	// CMake exports configs and targets for Qhull
  build/Testing/Temporary/LastTest.log // Output from CMake's ctest of Qhull
  build/install_manifest.txt // Installed files
  build/Makefile	// Generated Makefile