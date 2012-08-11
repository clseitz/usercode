import FWCore.ParameterSet.Config as cms
import string
import os,sys

print sys.argv[2]
index = int (sys.argv[2])
suffix_list=[]
output_list=[]
dir_list=[]

#suffix_list = os.popen('ls -1 /pnfs/cms/WAX/11/store/user/lpctlbsm/crsilk/SMS-T2tt_Mstop-225to1200_mLSP-50to1025_7TeV-Pythia6Z/ttbsm_v9_Summer11-PU_S4_START42_V11-v1/2f45e7f986681f9c0bbcc7cc31425dac/*root').readlines()



masslist = [200,250,300,350,400,450,500]
#thisFin_cfi = "RUAnalysis.Ntupler.T2tt_TLBSMv9_crsilk_FNAL_"+str(index)+"_cfi"
thisFin_cfi = "RUAnalysis.Ntupler.T1tttt_TLBSM52v003_LPC_"+str(index)+"_cfi"
#outdir = "/uscms_data/d3/clseitz/T2tt_375_75/"
#thisFout = outdir+"T2tt_7TeV_mstop375_mlsp75_7Tev_FastSim_RuNtuple"+str(index)
#this_fout0 = thisFout+"_plots.root"
#this_fout1 = thisFout+"_tree.root"


#this_fin_nocfi  =suffix_list[index]
#this_fout0 = "/uscms_data/d3/clseitz/T1tttt/T1tttt_8TeV_Mgluino-350to1200_mLSP-0to850_"+str(index)+"_plots.root"
#this_fout1 = "/uscms_data/d3/clseitz/T1tttt/T1tttt_8TeV_Mgluino-350to1200_mLSP-0to850_"+str(index)+"_tree.root"

this_fout0 = "QCD_ntuple_test_plots.root"
this_fout1 = "QCD_ntuple_test_tree.root"


print thisFin_cfi
print this_fout0
print this_fout1

process = cms.Process("data2")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 3000


process.maxEvents = cms.untracked.PSet(
      input = cms.untracked.int32(200)
     #input = cms.untracked.int32(-1)
     )
#process.load(thisFin_cfi)
process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring("file:/uscms/home/clseitz/MyCMS/TopBSMPat/52xv5/CMSSW_5_2_5/src/TopQuarkAnalysis/TopPairBSM/test/ttbsm_52x_mc.root"),
                                                        duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
                                                        )


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
                               isSUSY         =  cms.untracked.bool(False),
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



