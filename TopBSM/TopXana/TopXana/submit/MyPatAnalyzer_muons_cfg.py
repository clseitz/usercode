import FWCore.ParameterSet.Config as cms

import string
import os,sys

print sys.argv[2]
suffix_list=[]
suffix_list.append("DataSingleMuv4_166554")
suffix_list.append("DataSingleMuv1v2_May10_42X")


this_fin  = "TopBSM.TopXana.DataSingleMuv1v2v4_"+sys.argv[2]+"_cfi"

this_fout0 = "/cms/data21/clseitz/CMS_leptons/Muons/NewCode2/Muon_"+sys.argv[2]+".root"
this_fout1 = "/cms/data21/clseitz/CMS_leptons/Muons/NewCode2/Muons_tree_"+sys.argv[2]+".root"

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
  eeta           = cms.untracked.double(2.1),  
  ept            = cms.untracked.double(20.0),    
  meta           =  cms.untracked.double(2.1),   
  mpt            = cms.untracked.double(20.0),  
  
  NjetsMin       = cms.untracked.int32(3),
  NjetsMax       = cms.untracked.int32(1000),
  jetptcut       = cms.untracked.double(20),
  etacut         = cms.untracked.double(3.),
                              
  JSONFilename = cms.untracked.string('/users/h1/clseitz/MyCMS/CMSSW_4_2_4/src/TopBSM/TopXana/submit/Cert_160404-166502_7TeV_PromptReco_Collisions11_JSON.txt'),                             
)                               

process.p = cms.Path(process.data2)
