#!/bin/bash

cluster=$2
process=$1

# CMSSW setup etc
source /uscmst1/prod/sw/cms/shrc prod

export MYSCRIPT=/uscms/home/clseitz/MyCMS/RU/CMSSW_4_2_4/src/RUAnalysis/Ntupler/submit/ntupler_MCLPC_cfg.py
OUTDIR=/uscms_data/d3/clseitz/T2tt
DIR=/uscms/home/clseitz/MyCMS/RU/CMSSW_4_2_4/src/
cd $DIR
eval `scramv1 runtime -sh`
#---------------------------------------------------------------

echo "Running script " $MYSCRIPT 

cd $DIR
cp WpMass_process_GEN_FASTSIM_HLT_PU.py $OUTDIR.
cmsRun $MYSCRIPT $process  >& $OUTDIR/Log/MCProd_${process}.log


