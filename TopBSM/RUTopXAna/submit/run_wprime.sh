#!/bin/bash

cluster=$1
process=$2

#off=5
#num=$(($process+$off))

# CMSSW setup etc
export SCRAM_ARCH="slc5_amd64_gcc434" 
export VO_CMS_SW_DIR="/cms/base/cmssoft"
export COIN_FULL_INDIRECT_RENDERING=1
source $VO_CMS_SW_DIR/cmsset_default.sh

cd /users/h1/clseitz/MyCMS/DeanTest/CMSSW_4_2_4/src/TopBSM/RUTopXAna/submit

eval `scramv1 runtime -sh`

export MYSCRIPT=/users/h1/clseitz/MyCMS/DeanTest/CMSSW_4_2_4/src/TopBSM/RUTopXAna/submit/MyTopXana_wprime_cfg.py


#---------------------------------------------------------------

 echo "Running script " $MYSCRIPT 

 cd /users/h1/clseitz/MyCMS/DeanTest/CMSSW_4_2_4/src/TopBSM/RUTopXAna/submit

cmsRun $MYSCRIPT $process >& /cms/data24/clseitz/MCcomparison/Ntuplizer_${process}.log
#cmsRun $MYSCRIPT $process >& /cms/data23/evah/2011Data/Muons_anaPlots_mFO_${process}.log

