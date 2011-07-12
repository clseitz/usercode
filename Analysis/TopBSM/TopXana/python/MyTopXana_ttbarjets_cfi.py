import FWCore.ParameterSet.Config as cms



source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( 
                             'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_0.root',
                             'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_1.root',
                             'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_2.root',
                             'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_3.root',
                             'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_4.root',
                             'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_5.root',
                             'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_6.root',
                             'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_7.root',
                             'file:/cms/data24/clseitz/MC_4_2_4/TTbarJets/TTbarJets_8.root'
                             
                                                             )
                              )
