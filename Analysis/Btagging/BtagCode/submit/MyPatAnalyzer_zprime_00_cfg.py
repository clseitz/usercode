import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet(
    #input = cms.untracked.int32(-1)
    input = cms.untracked.int32(2000) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
       # 'file:/cms/se/store/user/duggan/TopBSM_mc/TTJets/41X/trigVal_patTuple_10_5_jMw.root'
     #'file:/cms/data22/ssirisky/MCGen_Summer11/113/200/RPVM200Fastsim42x_6_15_11_0.root'
     'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_0.root'
    )
)

process.demo = cms.EDAnalyzer('BtagCode',
                     sumPtMin       = cms.untracked.double(0.0), 
debug          = cms.untracked.bool(False), 
outputFilename = cms.untracked.string('ttbar1.root'),
outputFilename2= cms.untracked.string('ttbar2.root'),
PatJetType     = cms.untracked.string('selectedPatJetsAK5PF'),
htTrigger      = cms.untracked.string('HLT_HT360_v2'),
NjetsMin       = cms.untracked.int32(4),
NjetsMax       = cms.untracked.int32(9),
jetptcut       = cms.untracked.double(20),
etacut         = cms.untracked.double(3.),
isdata = cms.untracked.bool(False),
#isdata = cms.untracked.bool(True),
nbTagsMin      = cms.untracked.int32(0),
 nbTagsMax      = cms.untracked.int32(1000),
 nTripletBtagsMin = cms.untracked.int32(0),
 nTripletBtagsMax = cms.untracked.int32(1000),
 doBtagEff       = cms.untracked.bool(True)
                              
)


process.p = cms.Path(process.demo)
