/*
 *  GWEN
 *  Copyright (c) 2010 Facepunch Studios
 *  See license in Gwen.h
 */

#pragma once
#ifndef GWEN_CONTROLS_PROPERTIES_H
#define GWEN_CONTROLS_PROPERTIES_H

#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Controls/Property/BaseProperty.h"
#include "Gwen/Controls/Property/Text.h"
#include "Gwen/Controls/SplitterBar.h"
#include "Gwen/Gwen.h"
#include "Gwen/Skin.h"


namespace Gwen
{
    namespace Controls
    {
        class PropertyRow;

        class GWEN_EXPORT Properties : public Base
        {
        public:

            GWEN_CONTROL(Properties, Base);

            virtual void PostLayout(Gwen::Skin::Base* skin) override;

            PropertyRow* Add(const String& text, const String& value = "");
            PropertyRow* Add(const String& text, Property::Base* pProp,
                             const String& value = "");
            PropertyRow* Find(const String& text);

            virtual int GetSplitWidth();

            virtual void Clear();

        protected:

            virtual void OnSplitterMoved(Controls::Base* control);

            Controls::SplitterBar*  m_SplitterBar;

        };


        class GWEN_EXPORT PropertyRow : public Base
        {
        public:

            GWEN_CONTROL(PropertyRow, Base);

            virtual Label* GetLabel()
            {
                return m_Label;
            }

            virtual void            SetProperty(Property::Base* prop);
            virtual Property::Base* GetProperty()
            {
                return m_Property;
            }

            virtual void Layout(Gwen::Skin::Base* skin) override;
            virtual void Render(Gwen::Skin::Base* skin) override;

            virtual bool IsEditing()
            {
                return m_Property && m_Property->IsEditing();
            }

            virtual bool IsHovered() override
            {
                return ParentClass::IsHovered() || (m_Property && m_Property->IsHovered());
            }

            virtual void OnEditingChanged();
            virtual void OnHoverChanged();

            Event::Caller onChange;

        protected:

            void OnPropertyValueChanged(Gwen::Controls::Base* control);

            Label*          m_Label;
            Property::Base* m_Property;

            bool m_bLastEditing;
            bool m_bLastHover;

        };


    }
}
#endif // ifndef GWEN_CONTROLS_PROPERTIES_H