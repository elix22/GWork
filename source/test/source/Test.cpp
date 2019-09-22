/*
 *  Gwork
 *  Copyright (c) 2010 Facepunch Studios
 *  Copyright (c) 2013-2018 Billy Quith
 *  See license in Gwork.h
 */

#include <Gwork/Test/TestAPI.h>
#include <Gwork/Test/TestReflect.h>
#include <Gwork/Platform.h>

namespace Gwk {
namespace Test {
    
TestFrame* CreateTests(Gwk::Controls::Base *parent)
{
    return new TestFrame(parent);
}

GWK_CONTROL_CONSTRUCTOR(TestFrame)
{
    Dock(Position::Fill);
    
    // tabs to hold categories
    m_testTabs = new Controls::TabControl(this);
    m_testTabs->Dock(Position::Fill);
    
    // status bar
    m_statusBar = new Controls::StatusBar(this);
    m_statusBar->Dock(Position::Bottom);
    
    m_testTabs->AddPage("API", new TestAPI(m_testTabs));
#if GWK_REFLECT
    m_testTabs->AddPage("Reflection", new TestReflect(m_testTabs));
#endif
}

void TestFrame::Render(Skin::Base* skin)
{
    m_frames++;
    
    if (m_fLastSecond < Platform::GetTimeInSeconds())
    {
        m_statusBar->SetText(Utility::Format("Gwork Unit Test - %i fps", m_frames*2));
        m_fLastSecond = Platform::GetTimeInSeconds() + 0.5f;
        m_frames = 0;
    }
    
    ParentClass::Render(skin);
}

GWK_CONTROL_CONSTRUCTOR(TestCategory)
{
    Dock(Position::Fill);
}

void TestCategory::OutputToLog(const String& str)
{
    if (m_textOutput)
    {
        m_textOutput->AddItem(str);
        m_textOutput->ScrollToBottom();
    }
}


void TestUnit::OutputToLog(String str)
{
    m_testCategory->OutputToLog(str);
}
    
} // namespace Test
} // namespace Gwk


