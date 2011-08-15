#! /bin/bash

FILES=`cat DataSingleMuv1v2v4.txt`


n=0
FILE_LIST=""
for f in $FILES
do
echo $f
n=$n+1
#FILE_LIST=`echo $FILE_LIST"'file:"$f"',"`



done

NFILES=$n
N_PER_JOB=$((25))
NJOB=$(($NFILES/$N_PER_JOB))

echo $NJOB
k=$((0))
jobID=$((0))
for d in $FILES
do
template1="MyPatAnalyzer_quadjet_CONDOR_cfg.py"
run1=DataSingleMuv1v2v4_${jobID}_cfi.py

if [ $k -eq 0 ];then

#a=0
#rm $run1
#if [ $k -eq 0 ];then
#rm $run1
echo "import FWCore.ParameterSet.Config as cms">>$run1

echo '#Source'>> $run1
echo 'source = cms.Source("PoolSource",'>> $run1
echo ' fileNames = cms.untracked.vstring('>> $run1
fi
## Adding source files
if [ $k -eq 24 ]
then
echo $d >> $run1
else
echo $d>> $run1
fi
k=$(($k+1))
if [ $k -eq 25 ]
then
echo ')' >> $run1
echo ')' >> $run1
k=0
jobID=$(($jobID+1))
fi

done




