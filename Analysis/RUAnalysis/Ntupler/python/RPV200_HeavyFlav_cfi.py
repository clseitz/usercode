import FWCore.ParameterSet.Config as cms 
source = cms.Source("PoolSource", 
fileNames = cms.untracked.vstring( 
 'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m200_FastSim425_PUFlat10_TLBSMPAT424_v9_0.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m200_FastSim425_PUFlat10_TLBSMPAT424_v9_1.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m200_FastSim425_PUFlat10_TLBSMPAT424_v9_2.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m200_FastSim425_PUFlat10_TLBSMPAT424_v9_3.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m200_FastSim425_PUFlat10_TLBSMPAT424_v9_4.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m200_FastSim425_PUFlat10_TLBSMPAT424_v9_5.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m200_FastSim425_PUFlat10_TLBSMPAT424_v9_6.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m200_FastSim425_PUFlat10_TLBSMPAT424_v9_7.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m200_FastSim425_PUFlat10_TLBSMPAT424_v9_8.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m200_FastSim425_PUFlat10_TLBSMPAT424_v9_9.root', 
), 
duplicateCheckMode = cms.untracked.string('noDuplicateCheck') 
) 
