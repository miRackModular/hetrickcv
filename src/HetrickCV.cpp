#include "HetrickCV.hpp"


// The pluginInstance-wide instance of the Plugin class
Plugin *pluginInstance;

void init(rack::Plugin *p) {
	pluginInstance = p;

	p->addModel(modelTwoToFour);
	p->addModel(modelAnalogToDigital);
	p->addModel(modelASR);
	p->addModel(modelBitshift);
	p->addModel(modelBoolean3);
	p->addModel(modelComparator);
	p->addModel(modelContrast);
	p->addModel(modelCrackle);
	p->addModel(modelDelta);
	p->addModel(modelDigitalToAnalog);
	p->addModel(modelDust);
	p->addModel(modelExponent);
	p->addModel(modelFlipFlop);
	p->addModel(modelFlipPan);
	p->addModel(modelGateJunction);
	p->addModel(modelLogicCombine);
	p->addModel(modelMinMax);
	p->addModel(modelRandomGates);
	p->addModel(modelRotator);
	p->addModel(modelScanner);
	p->addModel(modelWaveshape);
	p->addModel(modelBlankPanel);
	// Any other pluginInstance initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables within this file or the individual module files to reduce startup times of Rack.
}
