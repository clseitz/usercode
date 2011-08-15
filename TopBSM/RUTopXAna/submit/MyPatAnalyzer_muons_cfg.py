import FWCore.ParameterSet.Config as cms

import string
import os,sys

print sys.argv[2]


this_fin  = "TopBSM.TopXana.DataSingleMuv1v2v4_"+sys.argv[2]+"_cfi"

this_fout0 = "/cms/data21/clseitz/CMS_leptons/Muons/NewCode4/Muon_"+sys.argv[2]+".root"
this_fout1 = "/cms/data21/clseitz/CMS_leptons/Muons/NewCode4/Muons_tree_"+sys.argv[2]+".root"

print "Muonss_"+sys.argv[2]+"file"
process = cms.Process("data2")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000


process.maxEvents = cms.untracked.PSet( 
  #input = cms.untracked.int32(2000)
 input = cms.untracked.int32(-1) 
)
process.load(this_fin);

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
  PatJetType     = cms.untracked.string('selectedPatJetsAK5PF'),
  htTrigger      = cms.untracked.string('HLT_HT360_v2'),
  IsoMu12_v1     = cms.untracked.string('HLT_IsoMu12_v1'),
  IsoMu17_v6     = cms.untracked.string('HLT_IsoMu17_v6'),
  NjetsMin       = cms.untracked.int32(3),
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
  JSONFilename = cms.untracked.string('/users/h2/duggan/Common/Data/Current/JSON/June27thGoldJSON.txt'),                             
)                               

process.p = cms.Path(process.data2)
