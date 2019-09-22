/*
 *  Gwork
 *  Copyright (c) 2010 Facepunch Studios
 *  Copyright (c) 2013-17 Billy Quith
 *  See license in Gwork.h
 */

#include <Gwork/Test/TestReflect.h>
#include <Gwork/Controls/DockedTabControl.h>
#include <Gwork/Controls/WindowControl.h>
#include <Gwork/Controls/CollapsibleList.h>
#include <Gwork/Controls/Layout/Position.h>
#include <Gwork/Platform.h>
#include <Gwork/Reflection.h>

namespace Gwk {
namespace Test {

GWK_DECLARE_TEST(ReflectAPIButton);
GWK_DECLARE_TEST(ReflectLuaButton);

GWK_CONTROL_CONSTRUCTOR(TestReflect)
{
    m_lastControl = nullptr;
    
    Reflect::Declare();

    Dock(Position::Fill);
    
    Controls::CollapsibleList* apiList = new Controls::CollapsibleList( this );
    GetLeft()->GetTabControl()->AddPage( "Tests", apiList );
    GetLeft()->SetWidth( 150 );

    // Where to put the demo controls.
    auto center = new Controls::Layout::Center(this);
    center->Dock(Position::Fill);
    
    m_textOutput = new Controls::ListBox(GetBottom());
    GetBottom()->GetTabControl()->AddPage("Output", m_textOutput);
    GetBottom()->SetHeight(140);


#define ADD_TEST(NAME) \
    { \
        Controls::Button *button = cat->Add(#NAME); \
        button->SetName(#NAME); \
        TestUnit *test = Gwk::Test::RegisterTest_##NAME(center); \
        test->SetTestCategory(this); \
        test->Hide(); \
        button->onPress.Add( this, &TestReflect::OnCategorySelect, test );\
    }

    // Create Controls using Gwork Ponder reflection API.
    {
        Controls::CollapsibleCategory* cat = apiList->Add("Ponder");
        ADD_TEST(ReflectAPIButton);
//        ADD_TEST(Label);
//        ADD_TEST(LabelMultiline);
    }

    // Create Controls using Lua via Ponder.
    {
        Controls::CollapsibleCategory* cat = apiList->Add("Lua");
        ADD_TEST(ReflectLuaButton);
    }

//    {
//        Controls::CollapsibleCategory* cat = apiList->Add("Non-Interactive");
//        ADD_TEST(ProgressBar);
//        ADD_TEST(GroupBox);
//        ADD_TEST(ImagePanel);
//        ADD_TEST(StatusBar);
//    }
//    {
//        Controls::CollapsibleCategory* cat = apiList->Add("Controls");
//        ADD_TEST(ComboBox);
//        ADD_TEST(TextBox);
//        ADD_TEST(ListBox);
//        ADD_TEST(CrossSplitter);
//        ADD_TEST(RadioButton);
//        ADD_TEST(Checkbox);
//        ADD_TEST(Numeric);
//        ADD_TEST(Slider);
//        ADD_TEST(MenuStrip);
//    }
//    {
//        Controls::CollapsibleCategory* cat = apiList->Add("Containers");
//        ADD_TEST(Window);
//        ADD_TEST(TreeControl);
//        ADD_TEST(Properties);
//        ADD_TEST(TabControl);
//        ADD_TEST(ScrollControl);
//        ADD_TEST(PageControl);
//    }
//    {
//        Controls::CollapsibleCategory* cat = apiList->Add("Non-Standard");
//        ADD_TEST(CollapsibleList);
//        ADD_TEST(ColorPicker);
//    }
    
#undef ADD_TEST
}

void TestReflect::OnCategorySelect(Gwk::Event::Info info)
{
    if (m_lastControl)
        m_lastControl->Hide();  // hide last

    info.Packet->Control->Show();
    m_lastControl = info.Packet->Control;
}

}}
