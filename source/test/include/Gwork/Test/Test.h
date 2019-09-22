/*
 *  Gwork
 *  Copyright (c) 2011 Facepunch Studios
 *  Copyright (c) 2013-2018 Billy Quith
 *  See license in Gwork.h
 */


#pragma once
#ifndef GWK_TEST_TEST_H
#define GWK_TEST_TEST_H

#include <Gwork/Align.h>
#include <Gwork/Utility.h>
#include <Gwork/Controls/ListBox.h>
#include <Gwork/Controls/DockBase.h>
#include <Gwork/Controls/StatusBar.h>
#include <Gwork/Controls/TabControl.h>
#include <Gwork/Controls/Canvas.h>


namespace Gwk {
    namespace Test {
        
        //
        /// Frame into which all tests go.
        //
        class TestFrame : public Gwk::Controls::DockBase
        {
        public:
            GWK_CONTROL(TestFrame, Gwk::Controls::DockBase);
            
            //void PrintText(const Gwk::String& str);
            
            void Render(Gwk::Skin::Base* skin) override;
            
        private:
            
            void OnCategorySelect(Gwk::Event::Info info);
            
            Gwk::Controls::TabControl*  m_testTabs;
            Gwk::Controls::StatusBar*   m_statusBar;
            unsigned int                m_frames;
            float                       m_fLastSecond;
        };
        
        
        //
        /// Tab page into which test category goes.
        //
        class TestCategory : public Gwk::Controls::DockBase
        {
        public:
            GWK_CONTROL(TestCategory, Gwk::Controls::DockBase);
            
            void OutputToLog(const Gwk::String& str);
            
        protected:
            
            Gwk::Controls::ListBox* m_textOutput;  // (optional) log
        };
        
        
        //
        /// Individual test. All tests derive from this.
        //
        class TestUnit : public Gwk::Controls::Base
        {
        public:
            
            GWK_CONTROL_INLINE(TestUnit, Gwk::Controls::Base)
            ,   m_testCategory(nullptr)
            {}
            
            void SetTestCategory(TestCategory* t)
            {
                m_testCategory = t;
            }
            
            void OutputToLog(Gwk::String str);
            
            void Layout(Gwk::Skin::Base* skin) override
            {
                if (GetDock() != Gwk::Position::None)
                    return;
                
                SizeToChildren(true, true);
            }
            
            TestCategory* m_testCategory;
        };
        
        TestFrame* CreateTests(Gwk::Controls::Base *parent);
        
    }
}

#define GWK_DECLARE_TEST(NAME) \
    Gwk::Test::TestUnit* RegisterTest_##NAME(Gwk::Controls::Base*);

#define GWK_REGISTER_TEST(NAME) \
    extern Gwk::Test::TestUnit* RegisterTest_##NAME(Gwk::Controls::Base *parent) { return new Gwk::Test::NAME(parent); }

#if GWK_REFLECT && defined(GWK_SAMPLE)
    // Include the implementation of Ponder dependencies so we can link successfully
#   include <ponder/classbuilder.hpp>
#   define PONDER_USES_RUNTIME_IMPL
#   include <ponder/uses/runtime.hpp>
#   define PONDER_USES_LUA_IMPL
#   include <ponder/uses/lua.hpp>
#   undef GWK_SAMPLE
#endif

#endif // ifndef GWK_TEST_TEST_H
