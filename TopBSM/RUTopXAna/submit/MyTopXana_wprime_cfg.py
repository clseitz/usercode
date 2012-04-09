import FWCore.ParameterSet.Config as cms

import string
import os,sys

print sys.argv[2]
index = int (sys.argv[2])
                                                
#suffix_list.append("Wp600_CMS_1")
#suffix_list.append("Wp600_CMS_2")
#suffix_list.append("Wp1000_CMS_1")
#suffix_list.append("Wp1000_CMS_2")
#suffix_list.append("Wp400PU_1")
#suffix_list.append("Wp400PU_2")
#suffix_list.append("Wp800PU_1")
#suffix_list.append("Wp800PU_2")

suffix_list=[]
output_list=[]
dir_list=[]
#suffix_list.append("Wp800_2")



#suffix_list = os.popen('ls -1 /cms/data26/clseitz/Wp425/TEST/*v9*root').readlines()
#2012 restart with Wp PatTuples
suffix_list = os.popen('ls -1 /cms/data27/clseitz/WprimeOffFall11/PAT/WprimeTToTTD_M600_52_v9.root').readlines()


this_fin_nocfi  = "file:"+suffix_list[index]
this_fout0 = "/cms/data27/clseitz/RUNtuple_12.04/WprimeTToTTD_M600_"+str(index)+"_FastSim425_TlBSMv9_RUNtuple_12.04_plots.root"
this_fout1 = "/cms/data27/clseitz/RUNtuple_12.04/WprimeTToTTD_M600_"+str(index)+"_FastSim425_TlBSMv9_RUNtuple_12.04_tree.root"

print this_fin_nocfi
print this_fout0
print this_fout1

#this_fin_nocfi  = "file:/cms/data24/clseitz/MC_4_2_4/Wprime2/ttbsm_42x_mc"+suffix_list[string.atoi(sys.argv[2])]+".root"
#this_fin_nocfi  = "file:/cms/data24/clseitz/ttbsmPat4_2_4/ttbsm_42x_mc"+suffix_list[string.atoi(sys.argv[2])]+"_fat.root" 
#this_fout0 = "/cms/data24/clseitz/Ntuples/"+suffix_list[string.atoi(sys.argv[2])]+"_PFselect_plots_fat_20l.root"
#this_fout1 = "/cms/data24/clseitz/Ntuples/"+suffix_list[string.atoi(sys.argv[2])]+"_PFselect_tree_fat_20l.root"
#this_fout0 = "test_plots.root"
#this_fout1 = "test_tree.root"
process = cms.Process("data2")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000


process.maxEvents = cms.untracked.PSet( 
  #input = cms.untracked.int32(200)
 input = cms.untracked.int32(-1) 
)

process.source = cms.Source("PoolSource",
                    fileNames = cms.untracked.vstring(this_fin_nocfi),
                    duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
                    )

#process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
 #                               fileNames = cms.untracked.vstring(this_fin_nocfi)
  #                           duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
                                                         
   #                          )

##process.source = cms.Source("PoolSource",
##  skipEvents = cms.untracked.uint32(0), 
##  fileNames = cms.untracked.vstring(
##    '',
##    ''
##    ), 
##  duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
##)

process.data2 = cms.EDAnalyzer('TopXana',
  sumPtMin       = cms.untracked.double(0.0), 
  debug          = cms.untracked.bool(False), 
  outputFilename = cms.untracked.string(this_fout0),
  outputFilename2= cms.untracked.string(this_fout1),
  PatJetType     = cms.untracked.string('goodPatJetsPFlow'),
  htTrigger      = cms.untracked.string('HLT_HT360_v2'),
  IsoMu12_v1     = cms.untracked.string('HLT_IsoMu12_v1'),
  IsoMu17_v6     = cms.untracked.string('HLT_IsoMu17_v6'),
  eeta           = cms.untracked.double(2.1),  
  ept            = cms.untracked.double(20.0),    
  meta           =  cms.untracked.double(2.1),   
  mpt            = cms.untracked.double(20.0),  
  isData         =  cms.untracked.bool(False),
  NjetsMin       = cms.untracked.int32(4),
  NjetsMax       = cms.untracked.int32(1000),
  jetptcut       = cms.untracked.double(20),
  etacut         = cms.untracked.double(3.),
       TriggerNames = cms.untracked.vstring(
        'HLT_Mu12_v1','HLT_IsoMu12_v1','HLT_Mu15_v2','HLT_Mu24_v2','HLT_IsoMu17_v6',
            'HLT_Mu30_v3','HLT_IsoMu17_v8','HLT_IsoMu24_v5','HLT_IsoMu24_v6',
            'HLT_IsoMu24_v7','HLT_Mu40_v2',
            'HLT_Ele27_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v1',
            'HLT_Ele27_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v2',
            'HLT_Ele27_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v3',
            'HLT_Ele32_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v3',
            'HLT_Ele42_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v1',
            'HLT_Ele52_CaloIdVT_TrkIdT_v3'
            ),
                        
  JSONFilename = cms.untracked.string('/users/h1/clseitz/MyCMS/CMSSW_4_2_4/src/TopBSM/TopXana/submit/Cert_160404-166502_7TeV_PromptReco_Collisions11_JSON.txt'),                             
)                               


process.p = cms.Path(process.data2)
