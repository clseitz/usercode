import FWCore.ParameterSet.Config as cms
import string
import os,sys

print sys.argv[2]
index = int (sys.argv[2])
suffix_list=[]
output_list=[]
dir_list=[]
#CS this is the input cfi file that contains all the files to run over (we have 3 different samples)
thisFin_cfi = "RUAnalysis.Ntupler.SingleMu_Run2012_TLBSM522v003_"+str(index)+"_cfi"
#CS output directory change here where you want to put it please keep the last two folders the same for bookeeping
outdir = "/uscms_data/d3/clseitz/ThreeJet/RUNtuple/SingleMuDataset/BMu40_SHT750/"
#CS filename adjust here the Trigger selection you are running Bblabla and Sblabla (match folder name above)
thisFout = outdir+"SingleMu_Run2012_8TeV_BMu40_SHT750"+str(index)
this_fout0 = thisFout+"_plots.root"
this_fout1 = thisFout+"_tree.root"


print thisFin_cfi
print this_fout0
print this_fout1

process = cms.Process("data2")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 3000


process.maxEvents = cms.untracked.PSet(
     #input = cms.untracked.int32(200)
     input = cms.untracked.int32(-1)
     )
process.load(thisFin_cfi)

#process.source = cms.Source("PoolSource",
#                            fileNames = cms.untracked.vstring(this_fin_nocif    ))
#)
#,
# duplicateCheckMode = cms.untracked.string('noDuplicateCheck')



##process.source = cms.Source("PoolSource",
##  skipEvents = cms.untracked.uint32(0),
##  fileNames = cms.untracked.vstring(
##    '',
##    ''
##    ),
##  duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
##)

process.data2 = cms.EDAnalyzer('Ntupler',
                               sumPtMin       = cms.untracked.double(0.0),
                               debug          = cms.untracked.bool(False),
                               NtuplePlots = cms.untracked.string(this_fout0),
                               NtupleTree= cms.untracked.string(this_fout1),
                               #PatJetType     = cms.untracked.vstring('goodPatJetsCA8PF'),
                               #PatJetType     = cms.untracked.vstring('goodPatJetsPFlow'),
                               #PatJetType     = cms.untracked.vstring('goodPatJetsCA8PF'),
                               PatJetType = cms.untracked.vstring('goodPatJetsPFlow','goodPatJetsCA8PF','goodPatJetsCA8PrunedPF'),
                               PrimaryVertex = cms.untracked.string('goodOfflinePrimaryVertices'),
                               METtype = cms.untracked.string('patMETsPFlow'),
                               htTrigger      = cms.untracked.string('HLT_HT360_v2'),
                               IsoMu12_v1     = cms.untracked.string('HLT_IsoMu12_v1'),
                               IsoMu17_v6     = cms.untracked.string('HLT_IsoMu17_v6'),
                               eeta           = cms.untracked.double(2.1),
                               ept            = cms.untracked.double(20.0),
                               meta           =  cms.untracked.double(2.1),
                               mpt            = cms.untracked.double(20.0),
                               isData         =  cms.untracked.bool(True),
                               NjetsMin       = cms.untracked.int32(4),
                               NjetsMax       = cms.untracked.int32(1000),
                               jetptcut       = cms.untracked.double(20),
                               etacut         = cms.untracked.double(3.),
                               #CS for trigger efficienyc studies Base trigger is either Mu40 or another one whihc matches the given trigger we want to look at
                               #for exampel SelectionTrigger Quad80, BaseTrigger Quad70

                               #CS comment in wich trigger should be the Selection Trigger (match folder and filname above)
                               #selection trigger
                               #Qua60_Di20
                             # TriggerNamesSel = cms.untracked.vstring('HLT_QuadJet60_DiJet20_v1','HLT_QuadJet60_DiJet20_v2','HLT_QuadJet60_DiJet20_v3',
                             #  'HLT_QuadJet60_DiJet20_v4','HLT_QuadJet60_DiJet20_v5','HLT_QuadJet60_DiJet20_v6','HLT_QuadJet60_DiJet20_v7'),
                               #Quad80
                               #TriggerNamesSel = cms.untracked.vstring('HLT_QuadJet80_v1','HLT_QuadJet80_v2','HLT_QuadJet80_v3','HLT_QuadJet80_v4',
                               #'HLT_QuadJet80_v5','HLT_QuadJet80_v6','HLT_QuadJet80_v7'),

                              # TriggerNamesSel = cms.untracked.vstring('HLT_QuadJet50_v1','HLT_QuadJet50_v2','HLT_QuadJet50_v3','HLT_QuadJet50_v4',
                              # 'HLT_QuadJet50_v5','HLT_QuadJet50_v6','HLT_QuadJet50_v7'),

                              # TriggerNamesSel = cms.untracked.vstring('HLT_SixJet45_v1','HLT_SixJet45_v2','HLT_SixJet45_v3','HLT_SixJet45_v4'),
                               TriggerNamesSel = cms.untracked.vstring('HLT_HT750_v1','HLT_HT750_v2','HLT_HT750_v3','HLT_HT750_v4','HLT_HT750_v5','HLT_HT750_v6'),

                               #CS base trigger we keep Mu40 for now
                               #base trigger
                               #TriggerNamesBase = cms.untracked.vstring('HLT_QuadJet50_v9','HLT_QuadJet50_v8'),
                               #,'HLT_QuadJet50_v3','HLT_QuadJet50_v4',
                               #                                      'HLT_QuadJet50_v5','HLT_QuadJet50_v6','HLT_QuadJet50_v7'),
                               #TriggerNamesBase = cms.untracked.vstring('HLT_QuadJet70_v1','HLT_QuadJet70_v2','HLT_QuadJet70_v3','HLT_QuadJet70_v4',
                               #                                   'HLT_QuadJet70_v5','HLT_QuadJet70_v6','HLT_QuadJet70_v7'),
                              # TriggerNamesBase = cms.untracked.vstring('HLT_SixJet35_v1','HLT_SixJet35_v2','HLT_SixJet35_v3','HLT_SixJet35_v4'),
                               #SingleMu

                               #TriggerNamesBase = cms.untracked.vstring('HLT_Mu12_v1','HLT_Mu12_v2','HLT_Mu12_v3','HLT_Mu12_v4',
                               #'HLT_Mu12_v5','HLT_Mu12_v6','HLT_Mu12_v7','HLT_Mu12_v8',
                               #                                         'HLT_Mu12_v9','HLT_Mu12_v10','HLT_Mu12_v11','HLT_Mu12_v12',
                               #                                        'HLT_Mu12_v13','HLT_Mu12_v14','HLT_Mu12_v15','HLT_Mu12_v16',
                               #                                         'HLT_Mu12_v17','HLT_Mu12_v18','HLT_Mu12_v19','HLT_Mu12_v20',
                               #                                         ),
                               TriggerNamesBase = cms.untracked.vstring('HLT_Mu40_v1','HLT_Mu40_v2','HLT_Mu40_v3','HLT_Mu40_v4',
                                                                        'HLT_Mu40_v5','HLT_Mu40_v6','HLT_Mu40_v7','HLT_Mu40_v8',
                                                                        'HLT_Mu40_v9','HLT_Mu40_v10','HLT_Mu40_v11','HLT_Mu40_v12',
                                                                        'HLT_Mu40_v13','HLT_Mu40_v14','HLT_Mu40_v15','HLT_Mu40_v16',
                                                                        'HLT_Mu40_v17','HLT_Mu40_v18','HLT_Mu40_v19','HLT_Mu40_v20',
                                                                        ),
                               #JSON file 900/pb May18
                               #JSONFilename = cms.untracked.string('/home/clseitz/MyCMS/RU/CMSSW_5_2_2/src/RUAnalysis/Ntupler/submit/Cert_190456-194076_8TeV_PromptReco_Collisions12_JSON.txt'),
                               #JSON File 2.42/fb Jun01
                               #JSONFilename = cms.untracked.string('/uscms/home/clseitz/MyCMS/RU/CMSSW_5_2_2/src/RUAnalysis/Ntupler/JSON/Cert_190456-195016_8TeV_PromptReco_Collisions12_JSON.txt'),
                               #JSON file 5.1/fb Jun24
                               JSONFilename = cms.untracked.string('/uscms/home/clseitz/MyCMS/RU/CMSSW_5_2_2/src/RUAnalysis/Ntupler/JSON/Cert_190456-196531_8TeV_PromptReco_Collisions12_JSON.txt'),

                               )


process.p = cms.Path(process.data2)



