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
#suffix_list = os.popen('ls -1 /cms/karen/clseitz/ThreeJet/MultiJet/Run2012*-PromptReco-v1_Json0601/*.root').readlines()
#suffix_list = os.popen('ls -1 /cms/data27/clseitz/Wprime/test_TTJets_FastSim/MatchingPAT/*root').readlines()
#suffix_list = os.popen('ls -1 /cms/karen/clseitz/ThreeJet/MultiJet/Run2012B-PromptReco-v1_Json0601/ttbsm_52x_data_205_1_LJP.root').readlines()
suffix_list = os.popen('ls -1 /cms/clseitz/ThreeJet/TLBSM53xv1/MultiJet/Run2012C-PromptReco-v2/TLBSM/*root').readlines()
this_fin_nocfi  = "file:"+suffix_list[index]

#this_fin_nocfi  = "file:"+suffix_list[3*index]
#this_fin_nocfi2  = "file:"+suffix_list[3*index+1]
#this_fin_nocfi3  = "file:"+suffix_list[3*index+2]
#this_fout0 = "/cms/data27/clseitz/ThreeJet/RUNtuple_12.04/WprimeTToTTD_M1200_"+str(index)+"_FastSim425_TlBSMv9_RUNtuple_12.04_test_jetPATtest_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/RUNtuple_12.04/WprimeTToTTD_M1200_"+str(index)+"_FastSim425_TlBSMv9_RUNtuple_12.04_test_jetPATtest_tree.root"
#this_fout0 = "/cms/data27/clseitz/ThreeJet/RUNtuple_12.04/RPVgluino_M-200_7TeV-pythia6_"+str(index)+"_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/RUNtuple_12.04/RPVgluino_M-200_7TeV-pythia6_"+str(index)+"_tree.root"

#this_fout0 = "/cms/data27/clseitz/ThreeJet/RUNtuple/Sbottom/mb_250_mf_100_ms_90_"+str(index)+"_Allplots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/RUNtuple/Sbottom/mb_250_mf_100_ms_90_"+str(index)+"_Alltree.root"
#this_fout0 = "/cms/data27/clseitz/ThreeJet/DanNtupleTLBSMtest/TLBSMv9/Ntuple/RPVgluino_M-250_7TeV_TLBSM_Ntuple_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/DanNtupleTLBSMtest/TLBSMv9/Ntuple/RPVgluino_M-250_7TeV_TLBSM_Ntuple_tree.root"

#this_fout0 = "/cms/data27/clseitz/ThreeJet/RUNtuple/Data2012/MultiJet_BSix35_SSix45/MultiJet_Run2012-PromptReco-v1_BSix35_SSix45"+str(index)+"_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/RUNtuple/Data2012/MultiJet_BSix35_SSix45/MultiJet_Run2012-PromptReco-v1_BSix35_SSix45_"+str(index)+"_tree.root"

#this_fout0 = "/cms/data27/clseitz/ThreeJet/RUNtuple/Data2012/Run2012A-PromptReco-v1_Json0601/MultiJet_BQuad50_SQuad60_Di20_jun19/MultiJet_Run2012-PromptReco-v1_Json0601_BQuad50_SQuad60_Di20_"+str(index)+"_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/RUNtuple/Data2012/Run2012A-PromptReco-v1_Json0601/MultiJet_BQuad50_SQuad60_Di20_jun19/MultiJet_Run2012-PromptReco-v1_Json0601_BQuad50_SQuad60_Di20_"+str(index)+"_tree.root"

#this_fout0 = "/cms/data27/clseitz/ThreeJet/RUNtuple/Data2012/Run2012A-PromptReco-v1_Json0601/test/Test3_BQuad50_SQuad60_"+str(index)+"_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/RUNtuple/Data2012/Run2012A-PromptReco-v1_Json0601/test/Test3_BQuad50_SQuad60_"+str(index)+"_tree.root"

#this_fout0 = "/cms/data27/clseitz/ThreeJet/RUNtuple/Data2012/Run2012A-PromptReco-v1_Json0601/MultiJet_BQuad70_SQuad80/MultiJet_Run2012-PromptReco-v1_Json0601_BQuad70_SQuad80_"+str(index)+"_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/RUNtuple/Data2012/Run2012A-PromptReco-v1_Json0601/MultiJet_BQuad70_SQuad80/MultiJet_Run2012-PromptReco-v1_Json0601_BQuad70_SQuad80_"+str(index)+"_tree.root"

#this_fout0 = "/cms/data27/clseitz/ThreeJet/RUNtuple/Data2012/Run2012A-PromptReco-v1_Json0601/MultiJet_BSix35_SSix45/MultiJet_Run2012-PromptReco-v1_Json0601_BSix35_SSix45_"+str(index)+"_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/RUNtuple/Data2012/Run2012A-PromptReco-v1_Json0601/MultiJet_BSix35_SSix45/MultiJet_Run2012-PromptReco-v1_Json0601_BSix35_SSix45_"+str(index)+"_tree.root"



#this_fout0 = "/cms/clseitz/ThreeJet/TLBSM53xv1/MultiJet/Run2012C-PromptReco-v2/RU/MultiJet_BSix45_SQuad60_Di20_JSONAug17_"+str(index)+"_plots.root"
#this_fout1 = "/cms/clseitz/ThreeJet/TLBSM53xv1/MultiJet/Run2012C-PromptReco-v2/RU/MultiJet_BSix45_SQuad60_Di20_JSONAug17_"+str(index)+"_tree.root"

this_fout0 = "/cms/clseitz/ThreeJet/BtagSFtest/Data/MultiJet_BSix45_SQuad60_Di20_JSONAug17_"+str(index)+"_plots.root"
this_fout1 = "/cms/clseitz/ThreeJet/BtagSFtest/Data/MultiJet_BSix45_SQuad60_Di20_JSONAug17_"+str(index)+"_tree.root"





#this_fout0 = "TEST"+str(index)+"_Allplots.root"
#this_fout1 = "TEST"+str(index)+"_Alltree.root"

print this_fin_nocfi

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
    this_fin_nocfi,
#    this_fin_nocfi2,
#    this_fin_nocfi3
    ))
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
                               #selection trigger
                               #Qua60_Di20
                               TriggerNamesSel = cms.untracked.vstring('HLT_QuadJet60_DiJet20_v1','HLT_QuadJet60_DiJet20_v2','HLT_QuadJet60_DiJet20_v3',
                                                                       'HLT_QuadJet60_DiJet20_v4','HLT_QuadJet60_DiJet20_v5','HLT_QuadJet60_DiJet20_v6',
                                                                       'HLT_QuadJet60_DiJet20_v7','HLT_QuadJet60_DiJet20_v8','HLT_QuadJet60_DiJet20_v9'),
                               #Quad70
                               #TriggerNamesSel = cms.untracked.vstring('HLT_QuadJet80_v1','HLT_QuadJet80_v2','HLT_QuadJet80_v3','HLT_QuadJet80_v4',
                               #'HLT_QuadJet80_v5','HLT_QuadJet80_v6','HLT_QuadJet80_v7'),

                               #TriggerNamesSel = cms.untracked.vstring('HLT_SixJet45_v1','HLT_SixJet45_v2','HLT_SixJet45_v3','HLT_SixJet45_v4'),
                               
                               #base trigger
                               #TriggerNamesBase = cms.untracked.vstring('HLT_QuadJet50_v9','HLT_QuadJet50_v8'),
                               #,'HLT_QuadJet50_v3','HLT_QuadJet50_v4',
                               #                                      'HLT_QuadJet50_v5','HLT_QuadJet50_v6','HLT_QuadJet50_v7'),
                               TriggerNamesBase = cms.untracked.vstring('HLT_QuadJet70_v1','HLT_QuadJet70_v2','HLT_QuadJet70_v3','HLT_QuadJet70_v4',
                                                                  'HLT_QuadJet70_v5','HLT_QuadJet70_v6','HLT_QuadJet70_v7'),
                               #TriggerNamesBase = cms.untracked.vstring('HLT_SixJet35_v1','HLT_SixJet35_v2','HLT_SixJet35_v3','HLT_SixJet35_v4'),
                               #JSON file 900/pb May18
#                               JSONFilename = cms.untracked.string('/home/clseitz/MyCMS/RU/CMSSW_5_2_2/src/RUAnalysis/Ntupler/submit/Cert_190456-194076_8TeV_PromptReco_Collisions12_JSON.txt'),
                               #JSON File 2.42/fb Jun01
                               #JSONFilename = cms.untracked.string('/home/clseitz/MyCMS/RU/CMSSW_5_2_2/src/RUAnalysis/Ntupler/submit/Cert_190456-195016_8TeV_PromptReco_Collisions12_JSON.txt'),
                               #JSON 8/fb
                                JSONFilename = cms.untracked.string('/home/clseitz/MyCMS/RU/CMSSW_5_2_2/src/RUAnalysis/Ntupler/JSON/Cert_190456-200601_8TeV_PromptReco_Collisions12_JSON.txt'),
                               )


process.p = cms.Path(process.data2)



