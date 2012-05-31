import FWCore.ParameterSet.Config as cms
import string
import os,sys

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

#data2012
suffix_list = os.popen('ls -1 /cms/data27/clseitz/ThreeJet/Data2012/TLBSM/MultiJet/Run2012A-PromptReco-v1/*.root').readlines()
#suffix_list = os.popen('ls -1 /cms/data27/clseitz/Wprime/test_TTJets_FastSim/MatchingPAT/*root').readlines()

this_fin_nocfi  = "file:"+suffix_list[2*index]
this_fin_nocfi2  = "file:"+suffix_list[2*index+1]

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

#this_fout0 = "/cms/data27/clseitz/ThreeJet/RUNtuple/Data2012/MultiJet_Quad50/MultiJet_Run2012A-PromptReco-v1_Quad50_Quad60_Di20"+str(index)+"_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/RUNtuple/Data2012/MultiJet_Quad50/MultiJet_Run2012A-PromptReco-v1_Quad50_Quad60_Di20"+str(index)+"_tree.root"


this_fout0 = "TEST"+str(index)+"_Allplots.root"
this_fout1 = "TEST"+str(index)+"_Alltree.root"

print this_fin_nocfi
print this_fin_nocfi2
print this_fout0
print this_fout1

process = cms.Process("data2")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 3000


process.maxEvents = cms.untracked.PSet(
      #input = cms.untracked.int32(200)
     input = cms.untracked.int32(-1)
     )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    #    "file:/cms/data27/clseitz/ThreeJet/TopBSMPATv9_RPVSummer11/RPVgluino_M-250_7TeV-2subjet_pythia6_PU_S4_START42_V11-v1_0.root",
    #    "file:/cms/data27/clseitz/ThreeJet/TopBSMPATv9_RPVSummer11/RPVgluino_M-250_7TeV-2subjet_pythia6_PU_S4_START42_V11-v1_1.root",
    #   "file:/cms/data27/clseitz/ThreeJet/TopBSMPATv9_RPVSummer11/RPVgluino_M-250_7TeV-2subjet_pythia6_PU_S4_START42_V11-v1_2.root",
    #  "file:/cms/data27/clseitz/ThreeJet/TopBSMPATv9_RPVSummer11/RPVgluino_M-250_7TeV-2subjet_pythia6_PU_S4_START42_V11-v1_3.root",
    # "file:/cms/data27/clseitz/ThreeJet/TopBSMPATv9_RPVSummer11/RPVgluino_M-250_7TeV-2subjet_pythia6_PU_S4_START42_V11-v1_4.root",
    # "file:/cms/data27/clseitz/ThreeJet/TopBSMPATv9_RPVSummer11/RPVgluino_M-250_7TeV-2subjet_pythia6_PU_S4_START42_V11-v1_5.root",
    # "file:/cms/data27/clseitz/ThreeJet/TopBSMPATv9_RPVSummer11/RPVgluino_M-250_7TeV-2subjet_pythia6_PU_S4_START42_V11-v1_6.root",
    # "file:/cms/data27/clseitz/ThreeJet/TopBSMPATv9_RPVSummer11/RPVgluino_M-250_7TeV-2subjet_pythia6_PU_S4_START42_V11-v1_7.root"
    
    this_fin_nocfi,
    this_fin_nocfi2))
#)
#,
# duplicateCheckMode = cms.untracked.string('noDuplicateCheck')



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
                               isData         =  cms.untracked.bool(True),
                               NjetsMin       = cms.untracked.int32(4),
                               NjetsMax       = cms.untracked.int32(1000),
                               jetptcut       = cms.untracked.double(20),
                               etacut         = cms.untracked.double(3.),
                               TriggerNames = cms.untracked.vstring('HLT_QuadJet60_DiJet20_v1','HLT_QuadJet60_DiJet20_v2',
                                                                    'HLT_QuadJet60_DiJet20_v3','HLT_QuadJet60_DiJet20_v4',
                                                                    'HLT_QuadJet60_DiJet20_v5','HLT_QuadJet60_DiJet20_v6',
                                                                    'HLT_QuadJet60_DiJet20_v7'),
                               TriggerNames2 = cms.untracked.vstring('HLT_QuadJet50_v1','HLT_QuadJet50_v2',
                                                                     'HLT_QuadJet50_v3','HLT_QuadJet50_v4',
                                                                     'HLT_QuadJet50_v5','HLT_QuadJet50_v6',
                                                                     'HLT_QuadJet50_v7'),
                               
                               JSONFilename = cms.untracked.string('/home/clseitz/MyCMS/RU/CMSSW_5_2_2/src/RUAnalysis/Ntupler/submit/Cert_190456-194076_8TeV_PromptReco_Collisions12_JSON.txt'),
                               )


process.p = cms.Path(process.data2)



