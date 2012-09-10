#!/bin/bash

cluster=$1
process=$2

#off=5
#num=$(($process+$off))

# CMSSW setup etc
export SCRAM_ARCH="slc5_amd64_gcc462" 
export VO_CMS_SW_DIR="/cms/base/cmssoft"
export COIN_FULL_INDIRECT_RENDERING=1
source $VO_CMS_SW_DIR/cmsset_default.sh

#export MYSCRIPT=/home/clseitz/MyCMS/RU/CMSSW_4_2_4/src/RUAnalysis/Ntupler/submit/ntupler_Data2011Dan_cfg.py

export MYSCRIPT=/users/h2/clseitz/MyCMS/RU/CMSSW_5_3_2_patch4/src/RUAnalysis/Ntupler/submit/ntupler_MC2012_cfg.py
#export MYSCRIPT=/users/h2/clseitz/MyCMS/RU/CMSSW_5_3_2_patch4/src/RUAnalysis/Ntupler/submit/ntupler_data2012_cfg.py
#export MYSCRIPT=/home/clseitz/MyCMS/RU/CMSSW_4_2_4/src/RUAnalysis/Ntupler/submit/ntupler_Includes_cfg.py
OUTDIR=/cms/clseitz/ThreeJet/TLBSM/TLBSM52xv5/QCD_HT250-500/RU_PileUp
DIR=/users/h2/clseitz/MyCMS/RU/CMSSW_5_3_2_patch4/src
cd $DIR
eval `scramv1 runtime -sh`
#---------------------------------------------------------------

echo "Running script " $MYSCRIPT 

cd $DIR
cp $MYSCRIPT $OUTDIR/.
cmsRun $MYSCRIPT $process  >& $OUTDIR/Log/MC_${process}.log
#cmsRun $MYSCRIPT $process >& /cms/data23/evah/2011Data/Muons_anaPlots_mFO_${process}.log

