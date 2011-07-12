import FWCore.ParameterSet.Config as cms



source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
                             'file:/cms/dan/Data/Collisions11/PDs/ReReco/42X/SingleElv1v2May10/trigVal_patTuple_100_0_OwZ.root'
                                                      
                                                             )
                              )
