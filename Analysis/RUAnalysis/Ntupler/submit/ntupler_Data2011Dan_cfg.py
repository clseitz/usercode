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
#suffix_list = os.popen('ls -1 /cms/data27/clseitz/ThreeJet/Ruderman_3b/428_patch7/PAT/mb_250_mf_100_ms_90_FAST_PUSumer11_428patch7_TLBSMPAT424_v9_0.root').readlines()


#suffix_list = os.popen('ls -1 /cms/data27/clseitz/Wprime/test_TTJets_FastSim/MatchingPAT/*root').readlines()
suffix_list = os.popen('ls -1 /cms/dan/Data/Collisions11/PDs/Prompt/HT2011Bv1_6JetSel/*root').readlines()
#suffix_list = os.popen('ls -1 /cms/dan/Data/Collisions11/PDs/Prompt/HT2011Bv1_6JetSel/*root').readlines()

#QCD MC Dan
#suffix_list = os.popen('ls -1 /cms/dan/QCDmc/HTBinned/HT250-500/HT250/*root').readlines()
#suffix_list = os.popen('ls -1  /cms/dan/QCDmc/HTBinned/HT500-1000/HT500TryTwo/*root').readlines()
#suffix_list = os.popen('ls -1   /cms/dan/QCDmc/HTBinned/HT1000/HT1000/*root').readlines()


#suffix_list = os.popen('ls -1 /cms/dan/RPV/Patuples425/RPV*root').readlines()

this_fin_nocfi  = "file:"+suffix_list[index]

#this_fout0 = "/cms/data27/clseitz/ThreeJet/RUNtuple_12.04/WprimeTToTTD_M1200_"+str(index)+"_FastSim425_TlBSMv9_RUNtuple_12.04_test_jetPATtest_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/RUNtuple_12.04/WprimeTToTTD_M1200_"+str(index)+"_FastSim425_TlBSMv9_RUNtuple_12.04_test_jetPATtest_tree.root"

#this_fout0 = "/cms/data27/clseitz/ThreeJet/RUNtuple_12.04/RPVgluino_M-200_7TeV-pythia6_"+str(index)+"_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/RUNtuple_12.04/RPVgluino_M-200_7TeV-pythia6_"+str(index)+"_tree.root"
this_fout0 = "/cms/data27/clseitz/ThreeJet/DanNtupleTLBSMtest/Dan/RPVgluino_M250_PAT_v17_plots.root"
this_fout1 = "/cms/data27/clseitz/ThreeJet/DanNtupleTLBSMtest/Dan/RPVgluino_M250_PAT_v17_tree.root"

#this_fout0 = "mb_250_mf_100_ms_90_"+str(index)+"_Allplots.root"
#this_fout1 = "mb_250_mf_100_ms_90_"+str(index)+"_Alltree.root"

#this_fout0 = "TTJets_FASTSim_"+str(index)+"_Allplots.root"
#this_fout1 = "TTJets_FastSim_"+str(index)+"_Alltree.root"

#this_fout0 = "/cms/data27/clseitz/ThreeJet/RUNtuple/16May2012/data/Data2011B_"+str(index)+"_Allplots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/RUNtuple/16May2012/data/Data2011B_"+str(index)+"_Alltree.root"

#this_fout0 = "/cms/data27/clseitz/ThreeJet/RUNtuple/16May2012/QCDmcHTbinned/HT250-500/QCD_HT250-500_offSummer11_Dan"+str(index)+"_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/RUNtuple/16May2012/QCDmcHTbinned/HT250-500/QCD_HT250-500_offSummer11_Dan_"+str(index)+"_tree.root"

#this_fout0 = "/cms/data27/clseitz/ThreeJet/RUNtuple/16May2012/QCDmcHTbinned/HT500-1000/QCD_HT500-1000_offSummer11_Dan"+str(index)+"_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/RUNtuple/16May2012/QCDmcHTbinned/HT500-1000/QCD_HT500-1000_offSummer11_Dan_"+str(index)+"_tree.root"

#this_fout0 = "/cms/data27/clseitz/ThreeJet/RUNtuple/16May2012/QCDmcHTbinned/HT1000/QCD_HT1000_offSummer11_Dan"+str(index)+"_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/RUNtuple/16May2012/QCDmcHTbinned/HT1000/QCD_HT1000_offSummer11_Dan_"+str(index)+"_tree.root"

print this_fin_nocfi
print this_fout0
print this_fout1

process = cms.Process("data2")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000


process.maxEvents = cms.untracked.PSet(
      #input = cms.untracked.int32(200)
     input = cms.untracked.int32(-1)
     )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring("file:/cms/data27/clseitz/ThreeJet/DanNtupleTLBSMtest/Dan/RPVgluino_M250_PAT_v17.root"
    #this_fin_nocfi
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
                               PatJetType = cms.untracked.vstring('selectedPatJetsAK5PF','selectedPatJetsAK5PF','selectedPatJetsAK5PF'),
                               PrimaryVertex = cms.untracked.string('offlinePrimaryVertices'),
                               METtype = cms.untracked.string('patMETsPF'),
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
                               TriggerNames = cms.untracked.vstring('HLT_HT350_v2','HLT_HT360_v2','HLT_HT500_v3','HLT_HT500_v4',
                                                                    'HLT_HT550_v5','HLT_HT550_v6','HLT_HT550_v7','HLT_HT550_v8',
                                                                    'HLT_HT600_v1','HLT_HT650_v1','HLT_HT750_v3'),
                               
                               JSONFilename = cms.untracked.string('/home/clseitz/MyCMS/RU/CMSSW_4_2_4/src/RUAnalysis/Ntupler/JSON/AllJSON_Golden_2011.txt'),
                               )


process.p = cms.Path(process.data2)



