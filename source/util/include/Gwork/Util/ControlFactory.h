/*
 *  Gwork
 *  Copyright (c) 2010 Facepunch Studios
 *  Copyright (c) 2013-17 Billy Quith
 *  See license in Gwork.h
 */

#pragma once

#include <Gwork/Gwork.h>
#include <Gwork/Controls.h>
#include <Gwork/Align.h>

namespace Gwk
{
    namespace ControlFactory
    {
        class Base;
        
        typedef std::list<ControlFactory::Base*> List;
        
        void InitialiseControls();

        List&                 GetList();
        ControlFactory::Base* Find(const Gwk::String& name);
        Controls::Base*       Clone(Controls::Base* ent, ControlFactory::Base* factory);
        
        class Property
        {
        public:

            typedef std::list<Property*> List;

            // For serialisation.
            virtual Gwk::String Name() const = 0;
            
            // Help.
            virtual Gwk::String Description() const = 0;

            // For the property editor.
            virtual Gwk::String GetValueAsString(Gwk::Controls::Base* ctrl) = 0;
            virtual void SetValueFromString(Gwk::Controls::Base* ctrl, const Gwk::String& str) = 0;

            virtual size_t OptionCount() const
            {
                return 0;
            }

            virtual Gwk::String OptionGet(int i)
            {
                return "";
            }

            virtual size_t NumCount() const
            {
                return 0;
            }

            virtual Gwk::String NumName(size_t i) const
            {
                return "unknown";
            }

            virtual float NumGet(Gwk::Controls::Base* ctrl, int i)
            {
                return 0.0f;
            }

            virtual void NumSet(Gwk::Controls::Base* ctrl, int i, float f)
            {
            }

            inline void NumSet(Gwk::Controls::Base* ctrl, const Gwk::String& str, float f)
            {
                for (size_t i = 0; i < NumCount(); i++)
                {
                    if (NumName(i) == str)
                    {
                        NumSet(ctrl, i, f);
                        break;
                    }
                }
            }

        };


        /// Base class for ControlFactorys.
        //
        class Base
        {
        public:

            Base();

            virtual Gwk::String Name() const = 0;
            virtual Gwk::String ParentFactory() const = 0;

            virtual Gwk::Controls::Base* CreateInstance(Gwk::Controls::Base* parent) = 0;

            Base* GetBaseFactory();
            void  AddProperty(Property* prop);

            Property* GetProperty(const Gwk::String& name);
            void      SetControlValue(Gwk::Controls::Base* ctrl, const Gwk::String& name,
                                      const Gwk::String& str);

            const Property::List& Properties()
            {
                return m_properties;
            }

            /// Called when the control is drag and dropped onto the parent, even
            /// when just moving in the designer
            virtual void AddChild(Gwk::Controls::Base* ctrl,
                                  Gwk::Controls::Base* child,
                                  const Gwk::Point& pos);

            /// Called when creating the control - param might be empty
            virtual void AddChild(Gwk::Controls::Base* ctrl,
                                  Gwk::Controls::Base* child,
                                  int iPage = 0);

            /// Called when a child is clicked on in an editor
            virtual bool ChildTouched(Gwk::Controls::Base* ctrl,
                                      Gwk::Controls::Base* childControl)
            {
                return false;
            }

            //
            /// If a control is parented to a control with multiple sections, or
            /// pages these functions are used to store which page they're on - on the
            /// child control
            //
            virtual void SetParentPage(Gwk::Controls::Base* ctrl, int i);
            virtual int  GetParentPage(Gwk::Controls::Base* ctrl);

        protected:

            Property::List m_properties;
        };


    } // ControlFactory

} // Gwork

