from basf2 import *
register_module("EnableMyVariables", shared_lib_path='/home/belle/ytchin/git/B-2mu-nu_mu/libytchin.so')
from modularAnalysis import *
from stdCharged import *
from stdPi0s import *
from stdV0s import *
from stdCharm import *
from stdPhotons import *
from variables import variables
import sys
import argparse

#------------Parses the command line options of the fei and returns the corresponding arguments.--------
parser = argparse.ArgumentParser()
parser.add_argument('-train', '--train_data', dest='train_data', type=str, required=False, choices=['Ks','Gm'], action='append', nargs='+',
                    help='Create training data')
parser.add_argument('-out', '--outputfile', dest='outputfile', type=str, default='/home/belle/ytchin/B+2mu+nu_mu/temp/20181016_signalGm.root',
                    help='Name of the outputted file')
args = parser.parse_args()

#-------------------------------------------Input mdst file---------------------------------------------
inputMdstList('default',['/ghi/fs01/belle/bdata2/users/ytchin/MC9signal/20171025_4_B+2mu+nu_mu_Udst.root.udst.root'])

#--------------------------------------Particle identification------------------------------------------
#Kshorts identification
"""Load Kshorts"""
stdKshorts()
cutAndCopyList('K_S0:V0mass','K_S0:all','M<0.518 and M>0.478')
matchMCTruth('K_S0:V0mass')

"""Create file for training"""
toolsKstrain = ['MCTruth','^K_S0']
toolsKstrain += ['CustomFloats[isSignal]','^K_S0']
toolsKstrain += ['Kinematics','^K_S0']
toolsKstrain += ['CustomFloats[lambdaMass]','^K_S0']
toolsKstrain += ['CustomFloats[shorterdr]','^K_S0']
toolsKstrain += ['CustomFloats[longerdr]','^K_S0']
toolsKstrain += ['CustomFloats[M]','^K_S0']
toolsKstrain += ['CustomFloats[daughter(0,nCDCHits):daughter(1,nCDCHits)]','^K_S0']
toolsKstrain += ['CustomFloats[daughter(0,nSVDHits):daughter(1,nSVDHits)]','^K_S0']
toolsKstrain += ['CustomFloats[daughter(0,pionID):daughter(1,pionID)]','^K_S0']
toolsKstrain += ['CustomFloats[daughter(0,protonID):daughter(1,protonID)]','^K_S0']
toolsKstrain += ['CustomFloats[daughter(0,cosTheta):daughter(1,cosTheta)]','^K_S0']
toolsKstrain += ['CustomFloats[daughter(0,p):daughter(1,p)]','^K_S0']
toolsKstrain += ['CustomFloats[daughter(0,px):daughter(0,py):daughter(0,pz):daughter(1,px):daughter(1,py):daughter(1,pz)]','^K_S0']
toolsKstrain += ['CustomFloats[daughter(0,z0):daughter(1,z0)]','^K_S0']
toolsKstrain += ['CustomFloats[cosAngleBetweenMomentumAndVertexVector]','^K_S0']
toolsKstrain += ['CustomFloats[dr]','^K_S0']
toolsKstrain += ['CustomFloats[decayAngle(0):decayAngle(1)]','^K_S0']
toolsKstrain += ['CustomFloats[V0Deltad0]','^K_S0']
toolsKstrain += ['CustomFloats[V0Deltaz0]','^K_S0']
toolsKstrain += ['CustomFloats[d0]','^K_S0']
toolsKstrain += ['CustomFloats[dphi]','^K_S0']

"""Cut using FOM of training results"""
if args.train_data is None:
   analysis_main.add_module('MVAExpert',listNames=['K_S0:V0mass'],extraInfoName='KsFastBDT',identifier='KsIdentifier')   
   cutAndCopyList('K_S0:V0good','K_S0:V0mass','extraInfo(KsFastBDT)>0.38')
else:
   cutAndCopyList('K_S0:V0good','K_S0:V0mass','')

#Converted photons identification
"""Load gamma"""
fillConvertedPhotonsList('gamma:V0all','',True)
vertexKFit('gamma:V0all', 0.0, '', '')
cutAndCopyList('gamma:V0mass','gamma:V0all','M>-0.04 and M<0.25 and formula(daughter(0,electronID)+daughter(1,electronID))>=1.0')
matchMCTruth('gamma:V0mass')

"""Create file for training"""
#analysis_main.add_module('ParticleMCDecayString',listName='gamma:V0mass')
toolsgmtrain = ['EventMetaData','^gamma']
toolsgmtrain += ['MCTruth','^gamma']
toolsgmtrain += ['CMSKinematics','^gamma']
toolsgmtrain += ['Kinematics','^gamma']
toolsgmtrain += ['CustomFloats[pxErr:pyErr:pzErr:ptErr]','^gamma']
toolsgmtrain += ['CustomFloats[M]','^gamma']
toolsgmtrain += ['CustomFloats[isSignal]','^gamma']
toolsgmtrain += ['CustomFloats[daughter(0,electronID):daughter(1,electronID)]','^gamma']
toolsgmtrain += ['CustomFloats[shorterdr]','^gamma']
toolsgmtrain += ['CustomFloats[longerdr]','^gamma']
toolsgmtrain += ['CustomFloats[daughter(0,nCDCHits):daughter(1,nCDCHits)]','^gamma']
toolsgmtrain += ['CustomFloats[daughter(0,z0):daughter(1,z0)]','^gamma']
toolsgmtrain += ['CustomFloats[daughter(0,nSVDHits):daughter(1,nSVDHits)]','^gamma']
toolsgmtrain += ['CustomFloats[daughter(0,cosTheta):daughter(1,cosTheta)]','^gamma']
toolsgmtrain += ['CustomFloats[daughter(0,p):daughter(1,p)]','^gamma']
toolsgmtrain += ['CustomFloats[cosAngleBetweenMomentumAndVertexVector]','^gamma']
toolsgmtrain += ['CustomFloats[dr:dx:dy:dz]','^gamma']
toolsgmtrain += ['CustomFloats[decayAngle(0):decayAngle(1)]','^gamma']
toolsgmtrain += ['CustomFloats[V0Deltad0]','^gamma']
toolsgmtrain += ['CustomFloats[V0Deltaz0]','^gamma']
toolsgmtrain += ['CustomFloats[dphi]','^gamma']


"""Cut using FOM of training results"""
if args.train_data is None:
   analysis_main.add_module('MVAExpert',listNames=['gamma:V0mass'],extraInfoName='GmFastBDT',identifier='GmIdentifier')
   cutAndCopyList('gamma:V0good','gamma:V0mass','extraInfo(GmFastBDT)>0.41')
else:
   cutAndCopyList('gamma:V0good','gamma:V0mass','')

#Photon identification
"""Load gamma"""
stdPhotons('tight')

"""Create gamma ntuple"""
toolsgmECL = ['EventMetaData','^gamma']
toolsgmECL += ['MCTruth','^gamma']
toolsgmECL += ['CustomFloats[E:cosTheta:isSignal]','^gamma']

#Charged particle identification
"""Load charged particle"""
fillParticleList('mu+:good','electronID<0.03 and kaonID<0.2 and muonID>0.625 and abs(d0)<0.08 and abs(z0)<0.3 and chiProb>0.001')
fillParticleList('e+:good','[electronID>0.03 or kaonID>0.2 or muonID<0.625] and kaonID<0.65 and electronID>0.75 and abs(d0)<0.08 and abs(z0)<0.3 and chiProb>0.001')
fillParticleList('K+:good','[electronID>0.03 or kaonID>0.2 or muonID<0.625] and [electronID<0.75 or kaonID>0.65] and protonID<0.14 and kaonID>0.048 and abs(d0)<0.08 and abs(z0)<0.3 and chiProb>0.001')
fillParticleList('p+:good','[electronID>0.03 or kaonID>0.2 or muonID<0.625] and [electronID<0.75 or kaonID>0.65] and [protonID>0.14 or kaonID<0.048] and protonID>0.97 and abs(d0)<0.08 and abs(z0)<0.3')
fillParticleList('pi+:good','[electronID>0.03 or kaonID>0.2 or muonID<0.625] and [electronID<0.75 or kaonID>0.65] and [protonID>0.14 or kaonID<0.048] and protonID<0.97 and abs(d0)<0.08 and abs(z0)<0.3 and chiProb>0.001')

#----------------------------------------multiple candidate selection of B-:good---------------------------
applyCuts('B-:good','countInList(B-:good,'')<2')

#------------------------------------------Mbc and deltaE cut----------------------------------------------
#reconstruct B:tag
#inclusiveBtagReconstruction('Upsilon(4S):lnuskim','B-:good','B-:tag',['K_S0:V0good','gamma:V0good','gamma:tight','mu+:good','e+:good','pi+:good','K+:good','p+:good'])
btag = register_module('MyInclusiveBtagReconstruction', shared_lib_path='/home/belle/ytchin/git/B-2mu-nu_mu/libytchin.so')
btag.set_name('MyInclusiveBtagReconstruction_' + 'B-:good')
btag.param('upsilonListName', 'Upsilon(4S):before')
btag.param('bsigListName', 'B-:good')
btag.param('btagListName', 'B+:tag')
btag.param('inputListsNames', ['K_S0:V0good','gamma:V0good','gamma:tight','pi+:good','p+:good','K+:good','mu+:good','e+:good'])
btag.logging.log_level = LogLevel.DEBUG
analysis_main.add_module(btag)

#Btag multiple candidate selection
#vertexKFit('B-:tag',-1)
#rankByLowest('B-:tag','chiProb',1)

#Another way to do Btag multiple candidate selection
rankByHighest('B-:tag','NV0gamma')
rankByHighest('B-:tag','NV0Lambda0')
rankByHighest('B-:tag','NV0K_S0',1)

#Cut on Mbc and deltaE
cutAndCopyList('B-:tagDeltaEMbc','B-:tag','Mbc>5.0 and deltaE>-3.6 and deltaE<0.1')
#
#------------------------------------continuum suppression-------------------------------------------------
#analysis_main.add_module('MyContinuumSuppressionBuilder', signalList='B-:good', tagList='B-:tag', shared_lib_path='/home/belle/ytchin/git/B-2mu-nu_mu/libmyModules.so')
buildRestOfEvent('B-:good', path=analysis_main)
cleanMask = ('cleanMask', 'useCMSFrame(p)<=3.2 and nCDCHits>0', 'p>=0.05 and useCMSFrame(p)<=3.2')
appendROEMasks('B-:good',[cleanMask],path=analysis_main)
analysis_main.add_module('ContinuumSuppressionBuilder', particleList='B-:good', ROEMask='cleanMask')

#event selection
cutAndCopyList('B-:evtslt','B-:good','daughter(0,kaonID)<0.04 and daughter(0,electronID)<0.1 and thrustOm<0.99 and useCMSFrame(p)>2.2 and useCMSFrame(p)<3.1 and daughter(0,nCDCHits)>0 and nROETracks(cleanMask)>3 and ROE_eextra(cleanMask)<4.1 and nROEKLMClusters<6 and daughter(0,pidDeltaLogLikelihoodValueExpert(13,211,ALL))>27.8 and daughter(0,chiProb)>0.001 and abs(daughter(0,d0))<0.08 and abs(daughter(0,z0))<0.3')
#

#------------------------------------reconstruct Y(4S)-----------------------------------------------------
reconstructDecay('Upsilon(4S):lnuskim -> B-:evtslt B+:tagDeltaEMbc','')

#----------------------------------------just for checking-------------------------------------------------
#matchMCTruth('B-:tag')
"""check charged particle PID performance"""
toolsmutag = ['EventMetaData','^mu-']
toolsmutag += ['MCTruth','^mu-']
toolsmutag += ['CustomFloats[isSignal:d0:z0:muonID:electronID:kaonID:pionID:protonID:nCDCHits]','^mu-']
toolsetag = ['EventMetaData','^e-']
toolsetag += ['MCTruth','^e-']
toolsetag += ['CustomFloats[isSignal:d0:z0:muonID:electronID:kaonID:pionID:protonID:nCDCHits]','^e-']
toolspitag = ['EventMetaData','^pi-']
toolspitag += ['MCTruth','^pi-']
toolspitag += ['CustomFloats[isSignal:d0:z0:muonID:electronID:kaonID:pionID:protonID:nCDCHits]','^pi-']
toolsKtag = ['EventMetaData','^K-']
toolsKtag += ['MCTruth','^K-']
toolsKtag += ['CustomFloats[isSignal:d0:z0:muonID:electronID:kaonID:pionID:protonID:nCDCHits]','^K-']
toolsptag = ['EventMetaData','^p+']
toolsptag += ['MCTruth','^p+']
toolsptag += ['CustomFloats[isSignal:d0:z0:muonID:electronID:kaonID:pionID:protonID:nCDCHits]','^p+']

#-------------------------------------------------NTuple maker---------------------------------------------
toolsmu = ['EventMetaData','Upsilon(4S) -> [^B- -> ^mu-] ^B+']
toolsmu += ['MCTruth','Upsilon(4S) -> [^B- -> ^mu-] B+']
toolsmu += ['Kinematics','Upsilon(4S) -> [^B- -> ^mu-] B+']
toolsmu += ['MCKinematics','Upsilon(4S) -> [^B- -> ^mu-] B+']
toolsmu += ['DeltaEMbc','Upsilon(4S) -> [B- -> mu-] ^B+']
toolsmu += ['CustomFloats[useCMSFrame(E):useCMSFrame(px):useCMSFrame(py):useCMSFrame(pz):useCMSFrame(p)]','^Upsilon(4S) -> [^B- -> mu-] ^B+']
toolsmu += ['CustomFloats[d0]','Upsilon(4S) -> [B- -> ^mu-] B+']
toolsmu += ['CustomFloats[z0]','Upsilon(4S) -> [B- -> ^mu-] B+']
toolsmu += ['CustomFloats[muonID]','Upsilon(4S) -> [B- -> ^mu-] B+']
toolsmu += ['CustomFloats[electronID]','Upsilon(4S) -> [B- -> ^mu-] B+']
toolsmu += ['CustomFloats[kaonID]','Upsilon(4S) -> [B- -> ^mu-] B+']
toolsmu += ['CustomFloats[pionID]','Upsilon(4S) -> [B- -> ^mu-] B+']
toolsmu += ['CustomFloats[protonID]','Upsilon(4S) -> [B- -> ^mu-] B+']
toolsmu += ['CustomFloats[nCDCHits]','Upsilon(4S) -> [B- -> ^mu-] B+']
toolsmu += ['CustomFloats[abs(useCMSFrame(cosTheta))]','^Upsilon(4S) -> [B- -> mu-] B+']
toolsmu += ['CustomFloats[NLep]','Upsilon(4S) -> [B- -> mu-] ^B+']
toolsmu += ['CustomFloats[nROETracks(cleanMask)]','Upsilon(4S) -> [^B- -> mu-] B+']
toolsmu += ['ContinuumSuppression[KsfwFS1CcROE]','Upsilon(4S) -> [^B- -> mu-] B+']
toolsmu += ['ContinuumSuppression','Upsilon(4S) -> [^B- -> mu-] B+']
toolsmu += ['CustomFloats[chiProb]','Upsilon(4S) -> [B- -> ^mu-] B+']
toolsmu += ['CustomFloats[nROEKLMClusters]','Upsilon(4S) -> [^B- -> mu-] B+']
toolsmu += ['CustomFloats[ROE_eextra(cleanMask)]','Upsilon(4S) -> [^B- -> mu-] B+']
toolsmu += ['CustomFloats[ROE_neextra(cleanMask):useCMSFrame(ROE_Px(cleanMask)):useCMSFrame(ROE_Py(cleanMask)):useCMSFrame(ROE_Pz(cleanMask))]','Upsilon(4S) -> [^B- -> mu-] B+']
toolsmu += ['CustomFloats[pidPairProbabilityExpert(13,211,ALL)]','Upsilon(4S) -> [B- -> ^mu-] B+']
toolsmu += ['CustomFloats[pidPairProbabilityExpert(13,211,KLM)]','Upsilon(4S) -> [B- -> ^mu-] B+']
toolsmu += ['CustomFloats[pidProbabilityExpert(13,ALL)]','Upsilon(4S) -> [B- -> ^mu-] B+']
toolsmu += ['CustomFloats[pidDeltaLogLikelihoodValueExpert(13,211,ALL)]','Upsilon(4S) -> [B- -> ^mu-] B+']
toolsmu += ['CustomFloats[pidLogLikelihoodValueExpert(13,ALL)]','Upsilon(4S) -> [B- -> ^mu-] B+']
toolsmu += ['CustomFloats[pidLogLikelihoodValueExpert(13,KLM)]','Upsilon(4S) -> [B- -> ^mu-] B+']
toolsmu += ['CustomFloats[pidDeltaLogLikelihoodValueExpert(13,211,KLM)]','Upsilon(4S) -> [B- -> ^mu-] B+']

ntupleFile(args.outputfile)
if args.train_data == [['Gm']]:
   ntupleTree('Gm','gamma:V0mass',toolsgmtrain)
elif args.train_data == [['Ks']]:
   ntupleTree('Ks','K_S0:V0mass',toolsKstrain)
elif args.train_data is None:
   #ntupleTree('Gm','gamma:tight',toolsgmECL)
   ntupleTree('y4s','Upsilon(4S):lnuskim',toolsmu)
   #ntupleTree('mutag','mu-:good',toolsmutag)
   #ntupleTree('etag','e-:good',toolsetag)
   #ntupleTree('pitag','pi-:good',toolspitag)
   #ntupleTree('Ktag','K-:good',toolsKtag)
   #ntupleTree('ptag','p+:good',toolsptag)


#processing
process(analysis_main)




#print out the summary
print(statistics)
