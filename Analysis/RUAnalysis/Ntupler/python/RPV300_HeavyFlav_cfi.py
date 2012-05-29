import FWCore.ParameterSet.Config as cms 
source = cms.Source("PoolSource", 
fileNames = cms.untracked.vstring( 
 'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m300_FastSim425_PUFlat10_TLBSMPAT424_v9_20.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m300_FastSim425_PUFlat10_TLBSMPAT424_v9_21.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m300_FastSim425_PUFlat10_TLBSMPAT424_v9_22.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m300_FastSim425_PUFlat10_TLBSMPAT424_v9_23.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m300_FastSim425_PUFlat10_TLBSMPAT424_v9_24.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m300_FastSim425_PUFlat10_TLBSMPAT424_v9_25.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m300_FastSim425_PUFlat10_TLBSMPAT424_v9_26.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m300_FastSim425_PUFlat10_TLBSMPAT424_v9_27.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m300_FastSim425_PUFlat10_TLBSMPAT424_v9_28.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m300_FastSim425_PUFlat10_TLBSMPAT424_v9_29.root', 
), 
duplicateCheckMode = cms.untracked.string('noDuplicateCheck') 
) 
