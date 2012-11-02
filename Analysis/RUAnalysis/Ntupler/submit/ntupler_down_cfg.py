import FWCore.ParameterSet.Config as cms
import string
import os,sys

# Starting with a skeleton process which gets imported with the following line
# from PhysicsTools.PatAlgos.patTemplate_cfg import *

from PhysicsTools.PatAlgos.tools.coreTools import *


print sys.argv[2]
index = int (sys.argv[2])
suffix_list=[]
output_list=[]
dir_list=[]

#suffix_list = os.popen('ls -1 /cms/data27/clseitz/Wprime/WprimeOffFall11/PAT/Wprime*1200*_v9.root').readlines()
#gluinos
#suffix_list = os.popen('ls -1 /cms/data27/clseitz/ThreeJet/TopBSMPATv9_RPVSummer11/*200*root').readlines()
#stealth sbottoms
#suffix_list = os.popen('ls -1 /cms/data27/clseitz/ThreeJet/Ruderman_3b/MCProdSLHA_428p7/PAT/*.root').readlines()

#suffix_list = os.popen('ls -1 /cms/data27/clseitz/Wprime/test_TTJets_FastSim/MatchingPAT/*root').readlines()
suffix_list = os.popen('ls -1 ptpl_link/*root').readlines()

this_fin_nocfi  = "file:"+suffix_list[index]

#this_fout0 = "/cms/data27/clseitz/ThreeJet/RUNtuple_12.04/WprimeTToTTD_M1200_"+str(index)+"_FastSim425_TlBSMv9_RUNtuple_12.04_test_jetPATtest_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/RUNtuple_12.04/WprimeTToTTD_M1200_"+str(index)+"_FastSim425_TlBSMv9_RUNtuple_12.04_test_jetPATtest_tree.root"

#this_fout0 = "/cms/data27/clseitz/ThreeJet/RUNtuple_12.04/RPVgluino_M-200_7TeV-pythia6_"+str(index)+"_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/RUNtuple_12.04/RPVgluino_M-200_7TeV-pythia6_"+str(index)+"_tree.root"
#this_fout0 = "RPVgluino_M-200_7TeV-pythia6_"+str(index)+"_Allplots.root"
#this_fout1 = "RPVgluino_M-200_7TeV-pythia6_"+str(index)+"_Alltree.root"

#this_fout0 = "/cms/data27/clseitz/ThreeJet/RUNtuple/Sbottom/mb_250_mf_100_ms_90_"+str(index)+"_Allplots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/RUNtuple/Sbottom/mb_250_mf_100_ms_90_"+str(index)+"_Alltree.root"
#this_fout0 = "/cms/data27/clseitz/ThreeJet/DanNtupleTLBSMtest/TLBSMv9/Ntuple/RPVgluino_M-250_7TeV_TLBSM_Ntuple_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/DanNtupleTLBSMtest/TLBSMv9/Ntuple/RPVgluino_M-250_7TeV_TLBSM_Ntuple_tree.root"


this_fout0 = "ntuples/ntpl_"+str(index)+"_Allplots.root"
this_fout1 = "ntuples/ntpl_"+str(index)+"_Alltree.root"
print this_fin_nocfi
print this_fout0
print this_fout1


process = cms.Process("data2")

# process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
# process.load("JetMETCorrections.Configuration.JetCorrectionServicesAllAlgos_cff")
# process.prefer("ak5CaloL2L3")

## Source
# from PhysicsTools.PatAlgos.tools.cmsswVersionTools import pickRelValInputFiles
# process.source = cms.Source("PoolSource",
    # fileNames = cms.untracked.vstring(
    # pickRelValInputFiles( cmsswVersion  = 'CMSSW_5_3_2_patch4'
                        # , relVal        = 'RelValTTbar'
                        # , globalTag     = 'START53_V7E::All'
                        # , numberOfFiles = 1
                        # )
    # )
# )

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( 'START53_V7E::All' )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 3000


process.maxEvents = cms.untracked.PSet(
      #input = cms.untracked.int32(200)
     input = cms.untracked.int32(-1)
     )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
														this_fin_nocfi  
                                                              ),
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

process.data2 = cms.EDAnalyzer('Ntupler',
                               sumPtMin       = cms.untracked.double(0.0),
                               debug          = cms.untracked.bool(False),
                               NtuplePlots = cms.untracked.string(this_fout0),
                               NtupleTree= cms.untracked.string(this_fout1),
                               #PatJetType     = cms.untracked.vstring('goodPatJetsCA8PF'),
                               #PatJetType     = cms.untracked.vstring('goodPatJetsPFlow'),
                               #PatJetType     = cms.untracked.vstring('goodPatJetsCA8PF'),
                               PatJetType = cms.untracked.vstring('goodPatJetsPFlow','goodPatJetsCA8PF','goodPatJetsCA8PrunedPF'),
                               PrimaryVertex = cms.untracked.string('goodOfflinePrimaryVertices'),
                               METtype = cms.untracked.string('patMETsPFlow'),
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
                               jecAdj 				= cms.untracked.string('down'), # Can also be "up" or "down"
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



