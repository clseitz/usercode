import FWCore.ParameterSet.Config as cms



source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( 
                             'file:/cms/data23/ssirisky/MCGen_Summer11/113_223/200/RPVMFastsim42x_6_15_11_0.root',
                             'file:/cms/data23/ssirisky/MCGen_Summer11/113_223/200/RPVMFastsim42x_6_15_11_1.root',
                             'file:/cms/data23/ssirisky/MCGen_Summer11/113_223/200/RPVMFastsim42x_6_15_11_2.root',
                             'file:/cms/data23/ssirisky/MCGen_Summer11/113_223/200/RPVMFastsim42x_6_15_11_3.root',
                             'file:/cms/data23/ssirisky/MCGen_Summer11/113_223/200/RPVMFastsim42x_6_15_11_4.root',
                             'file:/cms/data23/ssirisky/MCGen_Summer11/113_223/200/RPVMFastsim42x_6_15_11_5.root',
                             'file:/cms/data23/ssirisky/MCGen_Summer11/113_223/200/RPVMFastsim42x_6_15_11_6.root',
                             'file:/cms/data23/ssirisky/MCGen_Summer11/113_223/200/RPVMFastsim42x_6_15_11_7.root',
                             'file:/cms/data23/ssirisky/MCGen_Summer11/113_223/200/RPVMFastsim42x_6_15_11_8.root',
                             'file:/cms/data23/ssirisky/MCGen_Summer11/113_223/200/RPVMFastsim42x_6_15_11_9.root',
                             
                                                             ),
                    duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
                              )
