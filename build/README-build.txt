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
  build/qhulltest/*vcxproj // 32-bit and 64-bit DevStudio project files for building qhulltest
  build/qhulltest/qhulltest*.vc*proj  // DevStudio project files for building qhulltest (2005 and 2009)
  build/CMakeModules/CheckLFS.cmake // enables Large File Support in CMake

CMake writes intermediate files into these directories
  build/CMakeFiles/	// Intermediate files produced by CMake
  build/QhullExport/	// CMake exports configs and targets for Qhull
  build/Testing/Temporary/LastTest.log // Output from CMake's ctest of Qhull
  build/install_manifest.txt // Installed files
  build/Makefile	// Generated Makefile