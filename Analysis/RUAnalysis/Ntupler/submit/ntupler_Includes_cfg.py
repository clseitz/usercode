import FWCore.ParameterSet.Config as cms

process = cms.Process("ModelFilter")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("UserCode.ModelFilter.modelfilter_cfi")
process.load("FastSimulation.Configuration.EventContent_cff")

readFiles = cms.untracked.vstring()

process.load("UserCode.ModelFilter.T2tt_7TeV_mstop225to1200_mLSP50to1025_7Tev_FNAL_Sal_0_cfi")


process.maxEvents = cms.untracked.PSet(
          #input = cms.untracked.int32(200)
         input = cms.untracked.int32(-1)
              )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

process.modelfilter.selectOnRange = cms.bool(True)
process.modelfilter.parameterMins = cms.vdouble(375, 75)
process.modelfilter.parameterMaxs = cms.vdouble(375, 75)

process.aod = cms.OutputModule("PoolOutputModule",
     process.AODSIMEventContent,
     fileName = cms.untracked.string('/uscms_data/d3/clseitz/T2tt_375_75/T2tt_stop375_lsp75_Sal.root'),
	 SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('modelfilter_step'))
 )

process.aod_step = cms.EndPath(process.aod)
process.modelfilter_step = cms.Path(process.modelfilter)

process.schedule =cms.Schedule(process.modelfilter_step, process.aod_step)
