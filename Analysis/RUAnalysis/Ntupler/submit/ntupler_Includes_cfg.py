import FWCore.ParameterSet.Config as cms
import string
import os,sys

print sys.argv[2]
index = int (sys.argv[2])

masslist = [200,250,300,350,400,450,500]
thisFin_cfi = "RUAnalysis.Ntupler.RPV"+str(masslist[index])+"_HeavyFlav_cfi"
outdir = "/cms/data27/clseitz/ThreeJet/RUNtuple/RPV/GluinoHeavyFlav/"
thisFout = outdir+"RPV_m"+str(masslist[index])+"_113_223_"
this_fout0 = thisFout+"plots.root"
this_fout1 = thisFout+"tree.root"

print thisFin_cfi
print this_fout0
print this_fout1

process = cms.Process("data2")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 3000


process.maxEvents = cms.untracked.PSet(
      #input = cms.untracked.int32(200)
     input = cms.untracked.int32(-1)
     )
process.load(thisFin_cfi)


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



