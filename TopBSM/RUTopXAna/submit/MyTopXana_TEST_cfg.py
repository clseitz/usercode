import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet(
    #input = cms.untracked.int32(-1)
    input = cms.untracked.int32(9000)
    )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
    #'file:/cms/dan/Data/Collisions11/PDs/ReReco/42X/SingleElv1v2May10/trigVal_patTuple_100_0_OwZ.root'
    #'file:/cms/dan/Data/Collisions11/PDs/ReReco/42X/SingleElv1v2May10/trigVal_patTuple_121_0_SjW.root'
    #'file:/cms/dan/Data/Collisions11/PDs/ReReco/42X/SingleElv1v2May10/trigVal_patTuple_143_0_W4u.root',
    #'file:/cms/data21/clseitz/MCgeneration/Wprime/Wprime_42X_PAT.root'
    #'file:/cms/data22/ssirisky/MCGen_Summer11/113/200/RPVM200Fastsim42x_6_15_11_0.root'
  #'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_0.root'
    '/store/user/lpctlbsm/srappocc/TTJets_TuneZ2_7TeV-madgraph-tauola/ttbsm_v8_Summer11-PU_S4_START42_V11-v1/5c91b0700768331a44f51c8a9892d391/ttbsm_42x_mc_9_1_59c.root'

    
    )
)

process.demo = cms.EDAnalyzer('TopXana',
                     sumPtMin       = cms.untracked.double(0.0), 
debug          = cms.untracked.bool(False), 
outputFilename = cms.untracked.string('test.root'),
outputFilename2= cms.untracked.string('test2.root'),
PatJetType     = cms.untracked.string('goodPatJetsPFlow'),
htTrigger      = cms.untracked.string('HLT_HT360_v2'),
NjetsMin       = cms.untracked.int32(3),
NjetsMax       = cms.untracked.int32(1000),
jetptcut       = cms.untracked.double(20),
etacut         = cms.untracked.double(3.),
#isData = cms.untracked.bool(True),
isData = cms.untracked.bool(False),
ept       = cms.untracked.double(45.0),
eeta         = cms.untracked.double(2.1),
mpt       = cms.untracked.double(30.0),
meta         = cms.untracked.double(2.1),

nbTagsMin      = cms.untracked.int32(0),
 nbTagsMax      = cms.untracked.int32(1000),
 nTripletBtagsMin = cms.untracked.int32(0),
 nTripletBtagsMax = cms.untracked.int32(1000),
 doBtagEff       = cms.untracked.bool(False),
JSONFilename = cms.untracked.string('/users/h1/clseitz/MyCMS/CMSSW_4_2_4/src/TopBSM/TopXana/submit/Cert_160404-166502_7TeV_PromptReco_Collisions11_JSON.txt'),

)


process.p = cms.Path(process.demo)
