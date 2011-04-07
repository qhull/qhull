#!/bin/bash
#
# make-vcproj.sh -- Make sln and vcproj files from CMakeLists.txt and qhull-all.pro


if [[ ! -f CMakeLists.txt || ! -f src/qhull-all.pro ]]; then
    echo "Excute eg/make-vcproj.sh from qhull directory with CMakeLists.txt and src/qhull-all.pro"
    exit
fi

echo "Set up build directories..."
if [[ ! -d build-prev ]]; then
    echo "Backup previous build"
    cp -r build build-prev && rm -r build
fi
rm -r buildvc buildqt
mkdir -p build
mkdir -p buildvc
mkdir -p buildqt
echo "Create vcproj files with cmake and qmake..."
cd buildvc && cmake -G "Visual Studio 8 2005" .. && cmake ..
cd ..
cd buildqt && qmake -tp vc -r ../src/qhull-all.pro
cd ..
if [[ ! -f CMakeLists.txt || ! -f buildvc/qhull.vcproj || ! -f buildqt/qhulltest/qhulltest.vcproj ]]; then
    echo "qmake and cmake did not build vcproj files in buildvc/ and buildqt"
    exit
fi


for f in buildvc/*.vcproj buildqt/qhulltest/*.vcproj; do 
    echo $f
    if [[ ! ${f##*INSTALL*} || ! ${f##*ALL_BUILD*} || ! ${f##*ZERO_CHECK*}  ]]; then
	continue
    fi
    dest=build/${f##*\/}
    sed -r -e 's|[cC]:\\bash\\local\\qhull|..|g' \
    	-e 's|[cC]:/bash/local/qhull|..|g' \
    	-e '\|CMake| d' \
    	-e 's/;CMAKE_INTDIR=..quot;[A-Za-z]*..quot;//' \
    	-e 's/LinkIncremental="2"/LinkIncremental="1"/' \
    	-e 's/RuntimeLibrary[=]/RuntimeTypeInfo="false"  RuntimeLibrary=/' \
    	-e 's/.*RuntimeTypeInfo."TRUE".*\n//' \
    	-e 's/buildvc/build/g' \
    	-e 's/buildqt/build/g' \
    	-e 's/\.\.\\\.\./../g' \
    	-e 's|\.\./\.\.|..|g' \
    	-e 's/c:\\qt\\[0-9]\.[0-9]\.[0-9]/\$(QTDIR)/g' \
	$f > $dest
done
echo '*.vcproj: Delete empty File in Files section near end of vcproj'

# If need to rebuild sln
sed -e '\|Project.*ALL_BUILD|,\|EndProject$| d' \
    -e '\|Project.*INSTALL|,\|EndProject$| d' \
    -e '\|Project.*ZERO_CHECK|,\|EndProject$| d' \
    buildvc/qhull.sln >build/qhull.sln

echo
echo 'qhull.sln: Remove first line of each GUID list -- postProject\n.* > postProject'
echo 'qhull.sln: Remove four empty project sections'
echo 'qhull.sln: Remove first part of Global section.'
echo 'qhull.sln: Save as PC'
echo
echo 'Open qhull.sln with DevStudio and add qhulltest.vcproj'
echo 'Add dependencies on qhull6 and qhullcpp'
echo 'Change Linker>OutputFile to qhulltest.exe'
echo 'Remove qhulltest via Configuration Manager... from 6 configs'


