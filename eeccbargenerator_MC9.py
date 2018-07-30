#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Descriptor: ee->eeccbar

########################################################
# Steering file for official MC production of 'ee->eeccbar' samples
# with beam backgrounds (BGx1)
#
# July 2018 - Belle II Collaboration
########################################################

from basf2 import *
from simulation import add_simulation
from reconstruction import add_reconstruction, add_mdst_output
from L1trigger import add_tsim
from ROOT import Belle2
import os
import glob

# background (collision) files
bg = glob.glob('/group/belle2/BGFile/OfficialBKG/15thCampaign/phase3/set1/*.root')

# number of events to generate, can be overriden with -n
num_events = 6000

# output filename, can be overriden with -o
output_filename = "test_generation.root"

# create path
main = create_path()

# specify number of events to be generated
main.add_module("EventInfoSetter", expList=0, runList=0, evtNumList=num_events)

# generate events
aafh = main.add_module(
  'AafhInput',
  mode=4,
  particle='c',
  rejection=2,
  maxFinalWeight=3.0,
  maxSubgeneratorWeight=1.5,
  subgeneratorWeights=[1.000e+00, 1.353e+00, 3.049e+00, 1.864e+01, 1.000e+00, 1.336e+00, 1.219e+01, 5.854e+00],
  suppressionLimits=[1e100] * 4,
  minMass=3.73
)

# add fragmentation module
fragmentation = register_module('MyFragmentation', shared_lib_path='/home/belle/ytchin/git/B-2mu-nu_mu/libmyModule_MC9.so')
fragmentation.param('ParameterFile', Belle2.FileSystem.findFile('data/generators/modules/fragmentation/pythia_belle2_charm.dat'))
fragmentation.param('ListPYTHIAEvent', 0)
fragmentation.param('UseEvtGen', 1)
fragmentation.param('DecFile', Belle2.FileSystem.findFile('data/generators/modules/fragmentation/dec_belle2_qqbar.dec'))
fragmentation.param('UserDecFile', os.path.expandvars('$BELLE2_EXTERNALS_DIR/share/evtgen/DECAY_2010.DEC'))
main.add_module(fragmentation)

# branch to an empty path if PYTHIA failed, this will change the number of events
# but the file meta data will contain the total number of generated events
generator_emptypath = create_path()
fragmentation.if_value('<1',generator_emptypath)

# detector simulation
add_simulation(main, bkgfiles=bg)

# remove the cache for background files to reduce memory
set_module_parameters(main, "BeamBkgMixer", cacheSize=0)

# trigger simulation
add_tsim(main)

# reconstruction
add_reconstruction(main)

# Finally add mdst output
add_mdst_output(main, filename=output_filename, additionalBranches=['KlIds', 'KLMClustersToKlIds'])

#process events and print call statistics
process(main)
print(statistics)
