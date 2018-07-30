from basf2 import *
from generators import add_aafh_generator
from ROOT import Belle2
import os
import glob


# background (collision) files
bg = glob.glob('/group/belle2/BGFile/OfficialBKG/15thCampaign/bgoverlay_phase3/*.root')

# number of events to generate, can be overriden with -n
num_events = 10
# output filename, can be overriden with -o
output_filename = "test_generation.root"

# create path
main = create_path()

# specify number of events to be generated
main.add_module("EventInfoSetter", expList=0, runList=0, evtNumList=num_events)

# generate events
add_aafh_generator(main, finalstate='e+e-mu+mu-', preselection=False)

#process events and print call statistics
process(main)
print(statistics)
