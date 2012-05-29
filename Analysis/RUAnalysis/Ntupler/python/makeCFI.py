#! /bin/env python
import os
import sys


print len(sys.argv)
indcount=1;
for indexcount in range(1,len(sys.argv)):
    mass = sys.argv[indcount]
    indcount=indcount+1
    print "mass point",mass
    file_list = os.popen("ls -1 /cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m"+mass+"_FastSim425_PUFlat10_TLBSMPAT424_v9_*.root").readlines()
    nFiles = len(file_list)
    FILE = open("RPV"+mass+"_HeavyFlav_cfi.py","w")
    print nFiles
    FILE.write("import FWCore.ParameterSet.Config as cms \n")
    FILE.write('source = cms.Source("PoolSource", \n')
    FILE.write("fileNames = cms.untracked.vstring( \n ")
    
    for myfile in file_list:
        this_fout = "'file:"+myfile[0:-1]+"', \n"
        FILE.write(this_fout)
    FILE.write( "), \n")
    FILE.write( "duplicateCheckMode = cms.untracked.string('noDuplicateCheck') \n")
    FILE.write( ") \n")

    
    #FILE.write('this_fout0 = "RPV_m'+mass+'_113_223_plots.root" \n')
    #FILE.write('this_fout1 = "RPV_m'+mass+'_113_223_tree.root"')
        
    FILE.close()
        
