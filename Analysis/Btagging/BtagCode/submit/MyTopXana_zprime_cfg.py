import FWCore.ParameterSet.Config as cms

import string
import os,sys

print sys.argv[2]

suffix_list=[]

suffix_list.append("Zprime_M1000_W100_424")
suffix_list.append("Zprime_M1500_W15_424")
suffix_list.append("Zprime_M500_W50_424")
suffix_list.append("Zprime_M500_W5_424")


this_fin  = "Btagging.BtagCode."+suffix_list[string.atoi(sys.argv[2])]+"_cfi"

this_fout0 = "/cms/data24/clseitz/BtaggEff/Zprime/"+suffix_list[string.atoi(sys.argv[2])]+"_raw.root"
this_fout1 = "dummy.root"



process = cms.Process("data2")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000


process.maxEvents = cms.untracked.PSet( 
  #input = cms.untracked.int32(2000)
 input = cms.untracked.int32(-1) 
)
process.load(this_fin);

#process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
 #                               fileNames = cms.untracked.vstring(this_fin)
  #                          )

##process.source = cms.Source("PoolSource",
##  skipEvents = cms.untracked.uint32(0), 
##  fileNames = cms.untracked.vstring(
##    '',
##    ''
##    ), 
##  duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
##)

process.data2 = cms.EDAnalyzer('BtagCode',
  sumPtMin       = cms.untracked.double(0.0), 
  debug          = cms.untracked.bool(False), 
  outputFilename = cms.untracked.string(this_fout0),
 
  PatJetType     = cms.untracked.string('selectedPatJetsAK5PF'),
  htTrigger      = cms.untracked.string('HLT_HT360_v2'),
  IsoMu12_v1     = cms.untracked.string('HLT_IsoMu12_v1'),
  IsoMu17_v6     = cms.untracked.string('HLT_IsoMu17_v6'),
  isData         =  cms.untracked.bool(False),
  NjetsMin       = cms.untracked.int32(3),
  NjetsMax       = cms.untracked.int32(1000),
  jetptcut       = cms.untracked.double(20),
  etacut         = cms.untracked.double(3.),
  doBtagEff       = cms.untracked.bool(True),                             
  JSONFilename = cms.untracked.string('/users/h1/clseitz/MyCMS/CMSSW_4_2_4/src/TopBSM/TopXana/submit/Cert_160404-166502_7TeV_PromptReco_Collisions11_JSON.txt'),                             
)                               

process.p = cms.Path(process.data2)
