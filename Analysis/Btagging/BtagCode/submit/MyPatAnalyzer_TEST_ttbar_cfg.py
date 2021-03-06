import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet(
    #input = cms.untracked.int32(-1)
    input = cms.untracked.int32(2000)
    )
#process.load("Btagging.BtagCode.RPV_MC_113_223_200GeV_cfi");
process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
                               fileNames = cms.untracked.vstring(
           'file:/cms/data27/clseitz/ThreeJet/Ruderman_3b/428_patch7/PAT/mb_250_mf_100_ms_90_FAST_PUSumer11_428patch7_TLBSMPAT424_v9_0.root'
                #'file:/cms/data22/ssirisky/MCGen_Summer11/113/200/RPVM200Fastsim42x_6_15_11_0.root'

                #'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_0.root',
                #'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_1.root',
                #'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_2.root',
                #'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_3.root',
                #'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_4.root',
                #'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_5.root',
                #'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_6.root',
                #'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_7.root',
                #'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_8.root'

               )
                            )


process.demo = cms.EDAnalyzer('BtagCode',
                     sumPtMin       = cms.untracked.double(0.0), 
debug          = cms.untracked.bool(False), 
outputFilename = cms.untracked.string('test.root'),
outputFilename2= cms.untracked.string('ttbar2.root'),
PatJetType     = cms.untracked.string('goodPatJetsPFlow'),
htTrigger      = cms.untracked.string('HLT_HT360_v2'),
NjetsMin       = cms.untracked.int32(4),
NjetsMax       = cms.untracked.int32(9),
jetptcut       = cms.untracked.double(20),
etacut         = cms.untracked.double(2.4),
isData = cms.untracked.bool(False),
#isdata = cms.untracked.bool(True),
nbTagsMin      = cms.untracked.int32(0),
 nbTagsMax      = cms.untracked.int32(1000),
 nTripletBtagsMin = cms.untracked.int32(0),
 nTripletBtagsMax = cms.untracked.int32(1000),
 doBtagEff       = cms.untracked.bool(True)
                              
)


process.p = cms.Path(process.demo)
