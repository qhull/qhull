#!/bin/sh
#
# qhull-zip.sh version -- Make zip and tgz files for Qhull release
#
# wzzip from http://www.winzip.com/wzcline.htm
#   can not use path with $zip_file 
#   odd error messages if can't locate directory
#
# $Id: //main/2015/qhull/eg/qhull-zip.sh#4 $$Change: 1995 $
# $DateTime: 2015/10/13 21:59:42 $$Author: bbarber $

if [[ $# -ne 3 ]]; then
        echo 'Missing date stamp, e.g., qhull-zip.sh 2015 2015.1 7.1.0.1940' 
        exit
fi
versionyear=$1
version=$2
versionunix=$3

err_program=qhull-zip
err_log=/var/tmp/qhull-zip.log
[[ -e $HOME/bash/etc/road-script.sh ]] && source $HOME/bash/etc/road-script.sh \
    || source /etc/road-script.sh

check_err_log $LINENO "$err_log"
check_err_log $LINENO "$err_step_log"
log_step $LINENO "Logging to $err_log\n... and $err_step_log"

log_note $LINENO "Find Qhull directory" 
if [[ ! -d qhull/eg && ! -d ../qhull/eg && -d ../../qhull/eg ]]; then
    exit_err $LINENO "qhull/eg directory not found at or above $PWD"
fi
if [[ ! -d qhull/eg ]]; then
    if [[ -d ../qhull/eg ]]; then
        cd ..
    else
        cd ../..  # Tested above
    fi
fi
root_dir=$(pwd)

TEMP_DIR="$TMP/qhull-zip-$(ro_today2)"
TEMP_FILE="$TMP/qhull-zip-$(ro_today2).txt"

qhull_zip_file=qhull-$version.zip # no path or spaces
qhull_tgz_file=qhull-$versionyear-src-$versionunix.tgz
qhullmd5_file=qhull-$version.md5sum

exit_if_fail $LINENO "rm -f $qhull_zip_file $qhull_tgz_file $qhullmd5_file"

#############################
log_step $LINENO "Check environment"
#############################

[[ $(type -p md5sum) ]] || exit_err $LINENO "md5sum is missing"
[[ $(cp --help || grep '[-]-parents') ]] ||  exit_err $LINENO "cp does not have --parents option"

#############################
log_step $LINENO "Define functions"
#############################

function check_zip_file #zip_file
{
    local zip_file=$1
    local HERE=$(ro_here)
    log_note $HERE "Check $zip_file"
    ls -l $zip_file >>$err_log
    exit_if_err $HERE "Did not create $zip_file"
    wzunzip -ybc -t $zip_file | grep -E -v -e '( OK|Zip)' >>$err_log
    exit_if_err $HERE "Error while checking $zip_file"
}

function check_tgz_file #tgz_file
{
    local tgz_file=$1
    local HERE=$(ro_here)
    log_note $HERE "Check $tgz_file"
    ls -l $tgz_file >>$err_log
    exit_if_err $HERE "Did not create $tgz_file"
    tar -tzf $tgz_file >/dev/null 2>>$err_log
    exit_if_err $HERE "Can not extract -- tar -tzf $tgz_file"
}

function convert_to_unix #dir $qhull_2ufiles -- convert files to Unix, preserving modtime from $root_dir
{
    local temp_dir=$1
    local HERE=$(ro_here)
    log_note $HERE "Convert files to unix format in $1"
    for f in $(find $temp_dir -type f | grep -E '^([^.]*|.*\.(ac|am|bashrc|c|cfg|cpp|css|d|dpatch|h|htm|html|man|pl|pri|pro|profile|sh|sql|termcap|txt|xml|xsd|xsl))$'); do
        exit_if_fail $HERE "d2u '$f' && touch -r '$root_dir/${f#$temp_dir/}' '$f'"
    done
    for f in $qhull_2ufiles; do
        exit_if_fail $HERE "d2u '$temp_dir/$f' && touch -r '$root_dir/$f' '$temp_dir/$f'"
    done
}

function create_md5sum #md5_file -- create md5sum of current directory
{
    local md5_file=$1
    local HERE=$(ro_here)
    log_step $HERE "Compute $md5_file"
    exit_if_fail $HERE "rm -f $md5_file"
    find . -type f | sed 's|^\./||' | sort | xargs md5sum >>$md5_file
    exit_if_err $HERE "md5sum failed"
    log_note $HERE "$(md5sum $md5_file)"
}

#############################
log_step $LINENO "Configure $0 for $(pwd)/qhull"
#############################

md5_zip_file=qhull-$version-zip.md5sum
md5_tgz_file=qhull-$versionyear-src-$versionunix-tgz.md5sum

# recursive 
qhull_dirs="qhull/eg qhull/html qhull/src"
qhull_files="qhull/build/*.sln qhull/build/*.vcproj qhull/build/qhulltest/*.vcproj \
    qhull/Announce.txt qhull/CMakeLists.txt qhull/COPYING.txt \
    qhull/File_id.diz qhull/QHULL-GO.lnk qhull/README.txt \
    qhull/REGISTER.txt qhull/index.htm qhull/Makefile  \
    qhull/bin/qconvex.exe qhull/bin/qdelaunay.exe qhull/bin/qhalf.exe \
    qhull/bin/qhull.exe qhull/bin/qhull_r.dll qhull/bin/qvoronoi.exe \
    qhull/bin/rbox.exe qhull/bin/user_eg.exe qhull/bin/user_eg2.exe \
    qhull/bin/testqset_r.exe \
    qhull/bin/user_eg3.exe qhull/bin/testqset.exe qhull/bin/msvcr80.dll"
qhull_ufiles="$qhull_dirs qhull/build/*.sln qhull/build/*.vcproj \
    qhull/Announce.txt qhull/CMakeLists.txt qhull/COPYING.txt \
    qhull/File_id.diz qhull/QHULL-GO.lnk qhull/README.txt \
    qhull/REGISTER.txt qhull/index.htm qhull/Makefile"
qhull_d2ufiles="Makefile src/libqhull/Makefile src/libqhull_r/Makefile \
    src/*/DEPRECATED.txt src/*/*.pro src/*/*.htm html/*.htm html/*.txt \
    src/libqhull/MBorland eg/q_eg eg/q_egtest eg/q_test "
    
#############################
log_step $LINENO "Clean distribution directories"
#############################

rm -r qhull/build/*
p4 sync -f qhull/build/...
exit_if_err $LINENO "Can not 'p4 sync -f qhull.sln *.vcproj'"
cd qhull && make clean
exit_if_err $LINENO "Can not 'make clean'"
cd ..
# Includes many files from 'cleanall' (Makefile)
rm -f qhull/src/qhull-all.pro.user* qhull/src/libqhull/BCC32tmp.cfg
rm -f qhull/eg/eg.* qhull/eg/*.x qhull/*.x qhull/x.* qhull/x qhull/eg/x
rm -f qhull/bin/qhulltest.exe qhull/bin/qhulltest
rm -f qhull/src/libqhull/*.exe qhull/src/libqhull/*.a
rm -f qhull/src/libqhull_r/*.exe qhull/src/libqhull_r/*.a
rm -f qhull/src/libqhull/qconvex.c qhull/src/libqhull/unix.c 
rm -f qhull/src/libqhull/qdelaun.c qhull/src/libqhull/qhalf.c
rm -f qhull/src/libqhull/qvoronoi.c qhull/src/libqhull/rbox.c
rm -f qhull/src/libqhull/user_eg.c qhull/src/libqhull/user_eg2.c  
rm -f qhull/src/libqhull/testqset.c 
rm -f qhull/src/libqhull_r/qconvex_r.c qhull/src/libqhull_r/unix_r.c 
rm -f qhull/src/libqhull_r/qdelaun_r.c qhull/src/libqhull_r/qhalf_r.c
rm -f qhull/src/libqhull_r/qvoronoi_r.c qhull/src/libqhull_r/rbox_r.c
rm -f qhull/src/libqhull_r/user_eg_r.c qhull/src/libqhull_r/user_eg2_r.c  
rm -f qhull/src/libqhull_r/testqset_r.c 
    
set noglob

if [[ -e /bin/msysinfo && $(type -p wzzip) && $(type -p wzunzip) ]]; then

    #############################
    log_step $LINENO "Build zip directory, $TEMP_DIR/qhull"
    #############################

    ls -l $qhull_files $qhull_dirs >>$err_log 
    exit_if_err $LINENO "Missing files for zip directory.  Release build only"

    log_note $LINENO "Copy \$qhull_files \$qhull_dirs to $TEMP_DIR/qhull"
    exit_if_fail $LINENO "rm -rf $TEMP_DIR && mkdir $TEMP_DIR"
    exit_if_fail $LINENO "cp -r -p --parents $qhull_files $qhull_dirs $TEMP_DIR"

    #############################
    log_step $LINENO "Write md5sum to $md5_tgz_file"
    #############################

    exit_if_fail $LINENO "pushd $TEMP_DIR/qhull"
    create_md5sum $md5_zip_file
    exit_if_fail $LINENO "cp -p $md5_zip_file $root_dir"
    
    #############################
    log_step $LINENO "Write $qhull_zip_file"
    #############################

    log_note $LINENO "Write \$qhull_files to $qhull_zip_file"
    exit_if_fail $LINENO "cd .. && mv qhull qhull-$version && md5sum qhull-$version/$md5_zip_file >>$root_dir/$qhullmd5_file"
    wzzip -P -r -u $qhull_zip_file qhull-$version >>$err_log
    exit_if_err $LINENO "wzzip does not exist or error while zipping files"
    check_zip_file $qhull_zip_file
    exit_if_fail $LINENO "popd"
    exit_if_fail $LINENO "mv $TEMP_DIR/$qhull_zip_file ."
fi

#############################
log_step $LINENO "Build tgz directory, $TEMP_DIR/qhull"
#############################

log_note $LINENO "Archive these files as $qhull_tgz_file"
ls -l $qhull_ufiles >>$err_log 
exit_if_err $LINENO "Missing files for tgz"

exit_if_fail $LINENO "rm -rf $TEMP_DIR && mkdir -p $TEMP_DIR"
exit_if_fail $LINENO "cp -r -p --parents $qhull_ufiles $TEMP_DIR"

if [[ $IS_WINDOWS && $(type -p d2u) ]]; then
    log_step $LINENO "Convert to Unix line endings"
    convert_to_unix "$TEMP_DIR"
fi

#############################
log_step $LINENO "Write md5sum to $md5_tgz_file"
#############################

exit_if_fail $LINENO "pushd $TEMP_DIR && cd qhull"
create_md5sum $md5_tgz_file
exit_if_fail $LINENO "cp -p $md5_tgz_file $root_dir"

exit_if_fail $LINENO "cd .. && mv qhull qhull-$version && md5sum qhull-$version/$md5_tgz_file >>$root_dir/$qhullmd5_file"

#############################
log_step $LINENO "Write $qhull_tgz_file"
#############################

exit_if_fail $LINENO "tar -zcf $root_dir/$qhull_tgz_file * && popd"
check_tgz_file $qhull_tgz_file

log_note $LINENO "md5sum of zip and tgz files"

for f in $qhull_zip_file $qhull_tgz_file; do
    if [[ -r $f ]]; then
        exit_if_fail $LINENO "md5sum $f >>$qhullmd5_file"
    fi
done

#############################
log_step $LINENO "Extract zip and tgz files to ($TEMP_DIR)"
#############################

exit_if_fail $LINENO "rm -rf $TEMP_DIR"
if [[ -r $root_dir/$qhull_zip_file ]]; then
    exit_if_fail $LINENO "mkdir -p $TEMP_DIR/zip && cd $TEMP_DIR/zip"
    exit_if_fail $LINENO "wzunzip -yb -d $root_dir/$qhull_zip_file"
    log_step $LINENO "Search for date stamps to zip/Dates.txt"
    find . -type f | grep -v '/bin/' | xargs grep '\-20' | grep -v -E '(page=|ISBN|sql-2005|utility-2000|written 2002-2003|tail -n -20|Spinellis|WEBSIDESTORY|D:06-5-2007|server-2005)' >Dates.txt
    find . -type f | grep -v '/bin/' | xargs grep -i 'qhull *20' >>Dates.txt
    find . -type f | grep -v '/bin/' | xargs grep -E 'SO=|SO |VERSION' >>Dates.txt
fi
if [[ -r $root_dir/$qhull_tgz_file ]]; then
    exit_if_fail $LINENO "mkdir -p $TEMP_DIR/tgz && cd $TEMP_DIR/tgz"
    exit_if_fail $LINENO "tar -zxf $root_dir/$qhull_tgz_file"
fi

#############################
log_step $LINENO "====================================================================="
log_step $LINENO "Test unix compile"
log_step $LINENO " cd .. && scp $qhull_tgz_file qhull@qhull.org:"
log_step $LINENO " tar zxf $qhull_tgz_file && cd qhull-$version && make >../make.x 2>&1"
log_step $LINENO "Build qhull"
log_step $LINENO " cd $TEMP_DIR/zip/qhull* && make SO=dll" 
log_step $LINENO "Test qhull"
log_step $LINENO " cp -p lib/libqhull*.dll bin && make testall >/c/bash/local/qhull/eg/q_test.x 2>&1"
log_step $LINENO "Build testqhull"
log_step $LINENO " cd /c/bash/local/qhull && bin/qhulltest --all >eg/qhulltest.x 2>&1"
log_step $LINENO "Compare eg/q_test-ok.txt to eg/q_test.x"
log_step $LINENO "Build and test libqhull and libqhull_r"
log_step $LINENO " cd /c/bash/local/qhull/src/libqhull && make && cp *.exe ../../bin && cd ../.. && make test && ls -l bin/qhull.exe"
log_step $LINENO " cd /c/bash/local/qhull/src/libqhull_r && make && cp *.exe ../../bin && cd ../.. && make test && ls -l bin/qhull.exe"
log_step $LINENO "Full test of libqhull_r"
log_step $LINENO " cd /c/bash/local/qhull/ && make testall >/c/bash/local/qhull/eg/q_test_r.x 2>&1"
log_step $LINENO "Compare previous zip release, Dates.txt, and md5sum.  Check for virus."
log_step $LINENO "Compare zip and tgz for CRLF vs LF"
log_step $LINENO "Search xml files for UNDEFINED. Check page links"
log_step $LINENO "Extract zip to Qhull/ and compare directories"
log_step $LINENO "Copy tarballs to qhull.org"
log_step $LINENO " scp qhull-2015*.0.5* qhull@qhull.org:web/download/"
log_step $LINENO "Finished successfully"
#############################
