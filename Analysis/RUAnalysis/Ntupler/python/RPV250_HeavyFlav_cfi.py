import FWCore.ParameterSet.Config as cms 
source = cms.Source("PoolSource", 
fileNames = cms.untracked.vstring( 
 'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m250_FastSim425_PUFlat10_TLBSMPAT424_v9_10.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m250_FastSim425_PUFlat10_TLBSMPAT424_v9_11.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m250_FastSim425_PUFlat10_TLBSMPAT424_v9_12.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m250_FastSim425_PUFlat10_TLBSMPAT424_v9_13.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m250_FastSim425_PUFlat10_TLBSMPAT424_v9_14.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m250_FastSim425_PUFlat10_TLBSMPAT424_v9_15.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m250_FastSim425_PUFlat10_TLBSMPAT424_v9_16.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m250_FastSim425_PUFlat10_TLBSMPAT424_v9_17.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m250_FastSim425_PUFlat10_TLBSMPAT424_v9_18.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m250_FastSim425_PUFlat10_TLBSMPAT424_v9_19.root', 
), 
duplicateCheckMode = cms.untracked.string('noDuplicateCheck') 
) 
