
#include "GwenUtil/ControlFactory.h"
#include "Gwen/Controls.h"


namespace Gwen
{
    namespace ControlFactory
    {
        using namespace Gwen;

        namespace Properties
        {
            class Min : public ControlFactory::Property
            {
                GWEN_CONTROL_FACTORY_PROPERTY(Min, "The minimum value");

                String GetValueAsString(Controls::Base* ctrl) override
                {
                    return Gwen::Utility::Format("%f", (int)gwen_cast<Controls::Slider>(
                                                     ctrl)->GetMin());
                }

                void SetValueFromString(Controls::Base* ctrl, const String& str) override
                {
                    float val;

                    if (sscanf(str.c_str(), "%f", &val) != 1)
                        return;

                    if (val == gwen_cast<Controls::Slider>(ctrl)->GetMin())
                        return;

                    gwen_cast<Controls::Slider>(ctrl)->SetRange(val, gwen_cast<Controls::Slider>(
                                                                    ctrl)->GetMax());
                }

            };


            class Max : public ControlFactory::Property
            {
                GWEN_CONTROL_FACTORY_PROPERTY(Max, "The max value");

                String GetValueAsString(Controls::Base* ctrl) override
                {
                    return Gwen::Utility::Format("%f", (int)gwen_cast<Controls::Slider>(
                                                     ctrl)->GetMax());
                }

                void SetValueFromString(Controls::Base* ctrl, const String& str) override
                {
                    float val;

                    if (sscanf(str.c_str(), "%f", &val) != 1)
                        return;

                    if (val == gwen_cast<Controls::Slider>(ctrl)->GetMax())
                        return;

                    gwen_cast<Controls::Slider>(ctrl)->SetRange(gwen_cast<Controls::Slider>(
                                                                    ctrl)->GetMin(), val);
                }

            };


        }

        class HorizontalSlider_Factory : public Gwen::ControlFactory::Base
        {
        public:

            GWEN_CONTROL_FACTORY_FOR(HorizontalSlider, Base)
            {
                AddProperty(new Properties::Min());
                AddProperty(new Properties::Max());
            }

            virtual Gwen::Controls::Base* CreateInstance(Gwen::Controls::Base* parent) override
            {
                Gwen::Controls::HorizontalSlider* pControl =
                    new Gwen::Controls::HorizontalSlider(parent);
                pControl->SetSize(100, 20);
                pControl->SetRange(0, 1);
                return pControl;
            }

        };


        GWEN_CONTROL_FACTORY(HorizontalSlider_Factory);

    }
}