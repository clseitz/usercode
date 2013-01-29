#!/bin/bash

INDIR=$1
OUTDIR=$2
OUTFILE=$3

#off=5
#num=$(($process+$off))

# CMSSW setup etc
export SCRAM_ARCH="slc5_amd64_gcc462" 
export VO_CMS_SW_DIR="/cms/base/cmssoft"
export COIN_FULL_INDIRECT_RENDERING=1
source $VO_CMS_SW_DIR/cmsset_default.sh


export MYSCRIPT=RunThreeJet
DIR=/users/h2/clseitz/MyCMS/RU/CMSSW_5_3_2_patch4/src
cd $DIR
eval `scramv1 runtime -sh`
#---------------------------------------------------------------

echo "Running script " $MYSCRIPT 

cd $DIR/RUAnalysis/Analysis
cp $MYSCRIPT $OUTDIR/.
./$MYSCRIPT PUHistoUpTo206940_208551.root $OUTDIR/${OUTFILE}.root ${INDIR}/*tree*.root > $OUTDIR/Log/Log_${OUTFILE}.log
#./$MYSCRIPT $OUTDIR/${OUTFILE}.root ${INDIR}/*tree*.root > $OUTDIR/Log/Log_${OUTFILE}.log




#cmsRun $MYSCRIPT $process >& /cms/data23/evah/2011Data/Muons_anaPlots_mFO_${process}.log

