import FWCore.ParameterSet.Config as cms
import string
import os,sys

print sys.argv[2]
index = int (sys.argv[2])
# mass = int (sys.argv[3])
# flavor = sys.argv[4]
# isr = sys.argv[5]
suffix_list=[]
output_list=[]
dir_list=[]

#suffix_list = os.popen("ls -1 /cms/clseitz/ThreeJet/TLBSM/TLBSM53xv2/PAT/RPV"+str(isr)+"/RPV_M"+str(mass)+"_"+str(flavor)+"/*root").readlines()

suffix_list = os.popen('ls -1 ptpl_link/*root').readlines()

# suffix_list = os.popen("ls -1 /cms/clseitz/ThreeJet/TLBSM/TLBSM53xv2/PAT/Stealth/StealthSbottomTo3b_MSb_"+str(mass)+"/*root").readlines()  

# newInd=index % 8
# this_fin_nocfi  = "file:"+suffix_list[newInd]
this_fin_nocfi  = "file:"+suffix_list[index]
# this_fout0 = "/cms/clseitz/ThreeJet/RUNtuple/Nov6ReRun_JES/Stealth/StealthSbottomTo3b_MSb_"+str(mass)+"/tealthSbottomTo3b_MSb_"+str(mass)+"_FullSimSummer12_TLBSM53xv5_"+str(newInd)+"_JESnone_plots.root"
# this_fout1 = "/cms/clseitz/ThreeJet/RUNtuple/Nov6ReRun_JES/Stealth/StealthSbottomTo3b_MSb_"+str(mass)+"/tealthSbottomTo3b_MSb_"+str(mass)+"_FullSimSummer12_TLBSM53xv5_"+str(newInd)+"_JESnone_tree.root"

#suffix_list = os.popen('ls -1 /cms/clseitz/ThreeJet/TLBSM/TLBSM52xv5/QCD_HT'+str(flavor)+'/TLBSM/*.root').readlines()
#suffix_list = os.popen('ls -1 /cms/dan/clseitz/ThreeJet/TLBSM53xv2/'+str(flavor)+'/TLBSM/*.root').readlines()
#suffix_list = os.popen('ls -1 /cms/clseitz/ThreeJet/TLBSM/TLBSM52xv5/'+str(flavor)+'/TLBSM/*.root').readlines()
#newInd=index % 20

#newInd=index % 500

#this_fout0 = "/cms/clseitz/ThreeJet/RUNtuple/Nov6ReRun_JES/RPV_ISR"+str(isr)+"/RPV_M"+str(mass)+"_"+str(flavor)+"/RPV_M"+str(mass)+"_"+str(flavor)+"_FullSimSummer12_TLBSM53xv2_"+str(newInd)+"_plots.root"
#this_fout1 = "/cms/clseitz/ThreeJet/RUNtuple/Nov6ReRun_JES/RPV_ISR"+str(isr)+"/RPV_M"+str(mass)+"_"+str(flavor)+"/RPV_M"+str(mass)+"_"+str(flavor)+"_FullSimSummer12_TLBSM53xv2_"+str(newInd)+"_tree.root"

#this_fout0 = "/cms/clseitz/ThreeJet/RUNtuple/Nov6ReRun_JES/QCDHTbinned/HT"+str(flavor)+"/QCD_"+str(flavor)+"_FullSimSummer12_TLBSM52xv5_"+str(newInd)+"_JESnone_plots.root"
#this_fout1 = "/cms/clseitz/ThreeJet/RUNtuple/Nov6ReRun_JES/QCDHTbinned/HT"+str(flavor)+"/QCD_"+str(flavor)+"_FullSimSummer12_TLBSM52xv5_"+str(newInd)+"_JESnone_tree.root"

#this_fout0 = "/cms/clseitz/ThreeJet/RUNtuple/Nov6ReRun_JES/"+str(flavor)+"/"+str(flavor)+"_FullSimSummer12_TLBSM53xv5_"+str(newInd)+"_JESnone_plots.root"
#this_fout1 = "/cms/clseitz/ThreeJet/RUNtuple/Nov6ReRun_JES/"+str(flavor)+"/"+str(flavor)+"_FullSimSummer12_TLBSM53xv5_"+str(newInd)+"_JESnone_tree.root"





#suffix_list = os.popen('ls -1 /cms/data27/clseitz/Wprime/WprimeOffFall11/PAT/Wprime*1200*_v9.root').readlines()
#gluinos
#suffix_list = os.popen('ls -1 /cms/clseitz/ThreeJet/TopBSMPATv9_RPVSummer11/*200*root').readlines()
#stealth sbottoms
#suffix_list = os.popen('ls -1 /cms/clseitz/ThreeJet/Ruderman_3b/CMSSW52x/ThreeB_2012_FastSim/TlbsmPAT/*.root').readlines()

#suffix_list = os.popen('ls -1 /cms/data27/clseitz/ThreeJet/Ruderman_3b/CMSSW52x/ThreeB_2012_FullSim/TlbsmPAT/*.root').readlines()
#suffix_list = os.popen('ls -1 /cms/data27/clseitz/ThreeJet/Ruderman_3b/CMSSW52x/ThreeB_2012_FastSim_PF2Patpatch/TLBSMPAT/*.root').readlines()
#suffix_list = os.popen('ls -1 /cms/clseitz/ThreeJet/Ruderman_3b/CMSSW52x/ThreeB_2012_FastSim526/TLBSMPAT/*.root').readlines()
#suffix_list = os.popen('ls -1 /cms/clseitz/ThreeJet/TLBSM53xv1/PatTuple/*.root').readlines()

#suffix_list = os.popen('ls -1 /cms/clseitz/ThreeJet/TLBSM/TLBSM52xv5/QCD_HT500-1000/TLBSM/*.root').readlines()
#suffix_list = os.popen('ls -1 /cms/clseitz/ThreeJet/TLBSM/TLBSM52xv5/QCD_HT1000-Inf/TLBSM/*.root').readlines()
#suffix_list = os.popen('ls -1 /cms/clseitz/ThreeJet/TLBSM/TLBSM52xv5/QCD_HT250-500/TLBSM/*.root').readlines()

#this_fin_nocfi  = "file:"+suffix_list[index]
#
#this_fout0 = "/cms/data27/clseitz/ThreeJet/Ruderman_3b/CMSSW52x/ThreeB_2012_FastSim/RU/StealthSusy_8TeV_Sbottom250_Singlino100_Singlet90_53v003_FastSim_"+str(index)+"_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/Ruderman_3b/CMSSW52x/ThreeB_2012_FastSim/RU/StealthSusy_8TeV_Sbottom250_Singlino100_Singlet90_53v003_FastSim_"+str(index)+"_tree.root"

#this_fout0 = "/cms/data27/clseitz/ThreeJet/Ruderman_3b/CMSSW52x/ThreeB_2012_FullSim/RU/StealthSusy_8TeV_Sbottom250_Singlino100_Singlet90_53v003_FullSim_"+str(index)+"_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/Ruderman_3b/CMSSW52x/ThreeB_2012_FullSim/RU/StealthSusy_8TeV_Sbottom250_Singlino100_Singlet90_53v003_FullSim_"+str(index)+"_tree.root"


#this_fout0 = "/cms/data27/clseitz/ThreeJet/Ruderman_3b/CMSSW52x/ThreeB_2012_FastSim_PF2Patpatch/RU/StealthSusy_8TeV_Sbottom250_Singlino100_Singlet90_53v003_FastSim_PF2Patch_"+str(index)+"_plots.root"
#this_fout1 = "/cms/data27/clseitz/ThreeJet/Ruderman_3b/CMSSW52x/ThreeB_2012_FastSim_PF2Patpatch/RU/StealthSusy_8TeV_Sbottom250_Singlino100_Singlet90_53v003_FastSim_PF2Patch_"+str(index)+"_tree.root"


#this_fout0 = "/cms/data27/clseitz/ThreeJet/Ruderman_3b/CMSSW52x/ThreeB_2012_FastSim526/RU/StealthSusy_8TeV_Sbottom250_Singlino100_Singlet90_53v003_FastSim526_"+str(index)+"_plots.root"

#this_fout1 = "/cms/data27/clseitz/ThreeJet/Ruderman_3b/CMSSW52x/ThreeB_2012_FastSim526/RU/StealthSusy_8TeV_Sbottom250_Singlino100_Singlet90_53v003_FastSim526_"+str(index)+"_tree.root"

#this_fout0 = "/cms/clseitz/ThreeJet/TLBSM/TLBSM52xv5/QCD_HT500-1000/RU_PileUp/QCD_HT500-1000_Summer12_TLBSM52xv5_"+str(index)+"_plots.root"
#this_fout1 = "/cms/clseitz/ThreeJet/TLBSM/TLBSM52xv5/QCD_HT500-1000/RU_PileUp/QCD_HT500-1000_Summer12_TLBSM52xv5_"+str(index)+"_tree.root"

#this_fout0 = "/cms/clseitz/ThreeJet/TLBSM/TLBSM52xv5/QCD_HT250-500/RU_PileUp/QCD_HT250-500_Summer12_TLBSM52xv5_"+str(index)+"_plots.root"
#this_fout1 = "/cms/clseitz/ThreeJet/TLBSM/TLBSM52xv5/QCD_HT250-500/RU_PileUp/QCD_HT250-500_Summer12_TLBSM52xv5_"+str(index)+"_tree.root"

#this_fout0 = "/cms/clseitz/ThreeJet/TLBSM/TLBSM52xv5/QCD_HT1000-Inf/RU_PileUp/QCD_HT1000-Inf_Summer12_TLBSM52xv5_"+str(index)+"_plots.root"
#this_fout1 = "/cms/clseitz/ThreeJet/TLBSM/TLBSM52xv5/QCD_HT1000-Inf/RU_PileUp/QCD_HT1000-Inf_Summer12_TLBSM52xv5_"+str(index)+"_tree.root"





#this_fout0 = "test_QCD_"+str(index)+"_plots.root"
#this_fout1 = "test_QCD_"+str(index)+"_tree.root"
#this_fout0 = "TEST"+str(index)+"_Allplots.root"
#this_fout1 = "TEST"+str(index)+"_Alltree.root"
this_fout0 = "ntuples/ntpl_"+str(index)+"_Allplots.root"
this_fout1 = "ntuples/ntpl_"+str(index)+"_Alltree.root"


print this_fin_nocfi

print this_fout0
print this_fout1

process = cms.Process("data2")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( 'START53_V15::All' )

# START53_V7E is the old tag used by TLBSM53x
# process.GlobalTag.globaltag = cms.string( 'START53_V7E::All' )
# For data use an AN3 GT like the following
# process.GlobalTag.globaltag = cms.string( 'FT_53_V10_AN3::All' )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

# JetCorrectionService ak5PFLchs1FastL2L3 for MC
# JetCorrectionService ak5PFchsL1FastL2L3Residual  for data
# jetcorrserv = 'ak5PFchsL1FastL2L3Residual'
jetcorrserv = 'ak5PFchsL1FastL2L3'

## load jet corrections
# process.load("JetMETCorrections.Configuration.JetCorrectionServicesAllAlgos_cff")
process.load("RUAnalysis.Ntupler.ak5PFchsJetCorrectionServices_cff")
process.prefer(jetcorrserv)


process.maxEvents = cms.untracked.PSet(
#      input = cms.untracked.int32(200)
     input = cms.untracked.int32(-1)
     )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    this_fin_nocfi,
#    this_fin_nocfi2,
#    this_fin_nocfi3
#    ))
    )
                            ,
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
                            )



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
                               isData         =  cms.untracked.bool(False),
                               NjetsMin       = cms.untracked.int32(4),
                               NjetsMax       = cms.untracked.int32(1000),
                               jetptcut       = cms.untracked.double(20),
                               etacut         = cms.untracked.double(3.),
                               jecAdj = cms.untracked.string('jerdown'), # Can also be "up" or "down
															 jetCorrectionService = cms.untracked.string(jetcorrserv),
                               #selection trigger
                               #Qua60_Di20
                               #TriggerNamesSel = cms.untracked.vstring('HLT_QuadJet60_DiJet20_v1','HLT_QuadJet60_DiJet20_v2','HLT_QuadJet60_DiJet20_v3','HLT_QuadJet60_DiJet20_v4',
                               #                                     'HLT_QuadJet60_DiJet20_v5','HLT_QuadJet60_DiJet20_v6','HLT_QuadJet60_DiJet20_v7'),
                               #Quad70
                               #TriggerNamesSel = cms.untracked.vstring('HLT_QuadJet80_v1','HLT_QuadJet80_v2','HLT_QuadJet80_v3','HLT_QuadJet80_v4',
                               #'HLT_QuadJet80_v5','HLT_QuadJet80_v6','HLT_QuadJet80_v7'),

                               TriggerNamesSel = cms.untracked.vstring('HLT_SixJet45_v1','HLT_SixJet45_v2','HLT_SixJet45_v3','HLT_SixJet45_v4'),
                               
                               #base trigger
                               #TriggerNamesBase = cms.untracked.vstring('HLT_QuadJet50_v9','HLT_QuadJet50_v8'),
                               #,'HLT_QuadJet50_v3','HLT_QuadJet50_v4',
                               #                                      'HLT_QuadJet50_v5','HLT_QuadJet50_v6','HLT_QuadJet50_v7'),
                               #TriggerNamesBase = cms.untracked.vstring('HLT_QuadJet70_v1','HLT_QuadJet70_v2','HLT_QuadJet70_v3','HLT_QuadJet70_v4',
                               #                                   'HLT_QuadJet70_v5','HLT_QuadJet70_v6','HLT_QuadJet70_v7'),
                               TriggerNamesBase = cms.untracked.vstring('HLT_SixJet35_v1','HLT_SixJet35_v2','HLT_SixJet35_v3','HLT_SixJet35_v4'),
                               # TriggerNamesBase2 = cms.untracked.vstring('HLT_SixJet35_v1','HLT_SixJet35_v2','HLT_SixJet35_v3','HLT_SixJet35_v4'),
                               #JSON file 900/pb May18
#                               JSONFilename = cms.untracked.string('/home/clseitz/MyCMS/RU/CMSSW_5_2_2/src/RUAnalysis/Ntupler/submit/Cert_190456-194076_8TeV_PromptReco_Collisions12_JSON.txt'),
                               #JSON File 2.42/fb Jun01
                               JSONFilename = cms.untracked.string('/home/clseitz/MyCMS/RU/CMSSW_5_2_2/src/RUAnalysis/Ntupler/submit/Cert_190456-195016_8TeV_PromptReco_Collisions12_JSON.txt'),
                               )


process.p = cms.Path(process.data2)



