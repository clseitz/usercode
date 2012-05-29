import FWCore.ParameterSet.Config as cms 
source = cms.Source("PoolSource", 
fileNames = cms.untracked.vstring( 
 'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m350_FastSim425_PUFlat10_TLBSMPAT424_v9_30.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m350_FastSim425_PUFlat10_TLBSMPAT424_v9_31.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m350_FastSim425_PUFlat10_TLBSMPAT424_v9_32.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m350_FastSim425_PUFlat10_TLBSMPAT424_v9_33.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m350_FastSim425_PUFlat10_TLBSMPAT424_v9_34.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m350_FastSim425_PUFlat10_TLBSMPAT424_v9_35.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m350_FastSim425_PUFlat10_TLBSMPAT424_v9_36.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m350_FastSim425_PUFlat10_TLBSMPAT424_v9_37.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m350_FastSim425_PUFlat10_TLBSMPAT424_v9_38.root', 
'file:/cms/data27/clseitz/ThreeJet/RPV/GluinosHeavyFlav/TopBSM/RPV_m350_FastSim425_PUFlat10_TLBSMPAT424_v9_39.root', 
), 
duplicateCheckMode = cms.untracked.string('noDuplicateCheck') 
) 
