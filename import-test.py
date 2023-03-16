import rnbo

rnbo.init(48000, 64)

rnbo.printInfo()

# midiEvent note and velocity
rnbo.midiEvent(100, 1)
outVec = rnbo.process()


rnbo.setParamValueById("poly/overblow", 0.7)

print( rnbo.getParamValueById("poly/overblow") )

outVec = rnbo.process()

print( [i for i in outVec] )