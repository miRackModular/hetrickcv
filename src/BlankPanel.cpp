#include "HetrickCV.hpp"

/*
┌───────────────┐
│               │
│               │
│               │
│               │
│    blank.     │
│               │
│               │
│               │
└───────────────┘
 */

#define NUM_PANELS 5

struct BlankPanel : Module
{
	enum ParamIds
	{
		NUM_PARAMS
	};
	enum InputIds
	{
		NUM_INPUTS
	};
	enum OutputIds
	{
		NUM_OUTPUTS
    };

    enum LightIds
    {
        NUM_LIGHTS
	};

    int panel = 0;

	BlankPanel() 
	{
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	void process(const ProcessArgs &args) override {}

	void onReset() override
    {
        panel = 0;
	}
    void onRandomize() override
    {
        panel = round(random::uniform() * (NUM_PANELS - 1.0f));
    }

    json_t *dataToJson() override
    {
		json_t *rootJ = json_object();
        json_object_set_new(rootJ, "panel", json_integer(panel));
		return rootJ;
	}
    void dataFromJson(json_t *rootJ) override
    {
		json_t *panelJ = json_object_get(rootJ, "panel");
		if (panelJ)
            panel = json_integer_value(panelJ);
	}
};


struct BlankPanelWidget : ModuleWidget
{
	int curPanel = -1;

    BlankPanelWidget(BlankPanel *module)
	{
		setModule(module);
		box.size = Vec(6 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

		addChild(createWidget<ScrewSilver>(Vec(15, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 30, 0)));
		addChild(createWidget<ScrewSilver>(Vec(15, 365)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 30, 365)));
	}
    
    void step() override
	{
		auto blank = dynamic_cast<BlankPanel*>(module);
		
		if(blank && curPanel != blank->panel)
		{
			curPanel = blank->panel;

			if (curPanel == 1)
				setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Blanks/BlankPanel7.svg")));
			else if (curPanel == 2)
				setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Blanks/BlankPanel2.svg")));
			else if (curPanel == 3)
				setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Blanks/BlankPanel8.svg")));
			else if (curPanel == 4)
				setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Blanks/BlankPanel1.svg")));
			else
				setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Blanks/BlankPanel3.svg")));
		}

		ModuleWidget::step();
	}

    struct Panel1Item : MenuItem
	{
		BlankPanel *blank;
		void onAction(const event::Action &e) override { blank->panel = 0; }
		void step() override {
			rightText = (blank->panel == 0) ? "✔" : "";
			MenuItem::step();
		}
	};

	struct Panel2Item : MenuItem
	{
		BlankPanel *blank;
		void onAction(const event::Action &e) override { blank->panel = 1; }
		void step() override {
			rightText = (blank->panel == 1) ? "✔" : "";
			MenuItem::step();
		}
	};

	struct Panel3Item : MenuItem
	{
		BlankPanel *blank;
		void onAction(const event::Action &e) override { blank->panel = 2; }
		void step() override {
			rightText = (blank->panel == 2) ? "✔" : "";
			MenuItem::step();
		}
	};

	struct Panel4Item : MenuItem
	{
		BlankPanel *blank;
		void onAction(const event::Action &e) override { blank->panel = 3; }
		void step() override {
			rightText = (blank->panel == 3) ? "✔" : "";
			MenuItem::step();
		}
	};

	struct Panel5Item : MenuItem
	{
		BlankPanel *blank;
		void onAction(const event::Action &e) override { blank->panel = 4; }
		void step() override {
			rightText = (blank->panel == 4) ? "✔" : "";
			MenuItem::step();
		}
	};

	void appendContextMenu(Menu *menu) override
	{
		BlankPanel *blank = dynamic_cast<BlankPanel*>(module);
		assert(blank);

		if(blank)
		{
			menu->addChild(construct<MenuEntry>());
		    menu->addChild(construct<MenuLabel>(&MenuLabel::text, "Panel Art"));
			menu->addChild(construct<Panel1Item>(&Panel1Item::text, "Sideways Logo", &Panel1Item::blank, blank));
		    menu->addChild(construct<Panel2Item>(&Panel2Item::text, "Bleeding Edge", &Panel2Item::blank, blank));
		    menu->addChild(construct<Panel3Item>(&Panel3Item::text, "Hetrick Stack", &Panel3Item::blank, blank));
		    menu->addChild(construct<Panel4Item>(&Panel4Item::text, "Simple CV",     &Panel4Item::blank, blank));
		    menu->addChild(construct<Panel5Item>(&Panel5Item::text, "Plain Jane",    &Panel5Item::blank, blank));
		}
	}
};

Model *modelBlankPanel = createModel<BlankPanel, BlankPanelWidget>("BlankPanel");
