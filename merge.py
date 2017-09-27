#!/usr/bin/env python
# -*- coding: utf-8 -*-

from basf2 import *

main = create_path()

roinput = register_module('RootInput')
roinput.param('inputFileName', 'dummy.root')
main.add_module(roinput)

gearbox = register_module('Gearbox')
main.add_module(gearbox)
progress = register_module('Progress')
main.add_module(progress)

# output
output = register_module('RootOutput')
output.param('updateFileCatalog', False)
output.param('outputFileName', 'mcprod.mdst.root')

main.add_module(output)

process(main)

# Print call statistics
print (statistics)
