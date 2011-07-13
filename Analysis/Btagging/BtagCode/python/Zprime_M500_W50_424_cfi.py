import FWCore.ParameterSet.Config as cms



source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( 
'file:/cms/data24/clseitz/MC_4_2_4/Zprime/Zprime_M500_W50_pat424.root'
                               )
                              )
