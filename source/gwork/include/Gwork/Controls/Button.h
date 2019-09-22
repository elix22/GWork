/*
 *  Gwork
 *  Copyright (c) 2010 Facepunch Studios
 *  Copyright (c) 2013-2018 Billy Quith
 *  See license in Gwork.h
 */

#pragma once
#ifndef GWK_CONTROLS_BUTTON_H
#define GWK_CONTROLS_BUTTON_H

#include <Gwork/Controls/Label.h>

namespace Gwk
{
    namespace Controls
    {
        class ImagePanel;

        class GWK_EXPORT Button : public Label
        {
        public:

            GWK_CONTROL(Button, Label);

            void Render(Skin::Base* skin) override;
            void OnMouseClickLeft(int x, int y, bool bDown) override;
            void OnMouseClickRight(int x, int y, bool bDown) override;
            void OnMouseDoubleClickLeft(int x, int y) override;
            bool OnKeySpace(bool bDown) override;

            virtual void OnPress(Event::Info);
            virtual void OnRightPress(Event::Info);

            void AcceleratePressed() override;

            //! Is the button currently being pressed?
            virtual bool IsDepressed() const
            {
                return m_bDepressed;
            }

            virtual void SetDepressed(bool b);

            //
            /// Buttons can be toggle type, which means that it is
            /// toggled on and off. Its toggle status is in IsDepressed.
            //
            virtual void SetIsToggle(bool b)
            {
                m_bToggle = b;
            }

            virtual bool IsToggle() const
            {
                return m_bToggle;
            }

            virtual bool GetToggleState() const
            {
                return m_bToggleStatus;
            }

            virtual void SetToggleState(bool b);
            virtual void Toggle()
            {
                SetToggleState(!GetToggleState());
            }

            virtual void SetImage(const String& strName, bool bCenter = false);

            void SizeToContents() override;
            void PostLayout(Skin::Base* skin) override;
            void UpdateColors() override;

            virtual void SetImageAlpha(float fMultiply);

            void DoAction() override
            {
                Event::Info info(this);
                OnPress(info);
            }

            virtual void SetAction(Event::Handler* object,
                                   Event::Listener::EventListener function,
                                   const Gwk::Event::Packet& packet) override;

        public:

            // TODO - It is inefficient to store all of these for every control when not used.
            Gwk::Event::Listener onPress;
            Gwk::Event::Listener onRightPress;
            Gwk::Event::Listener onDown;
            Gwk::Event::Listener onUp;
            Gwk::Event::Listener onDoubleClick;
            Gwk::Event::Listener onToggle;
            Gwk::Event::Listener onToggleOn;
            Gwk::Event::Listener onToggleOff;

        protected:

            ImagePanel*     m_image;    ///< Optional image to be displayed on button.

            bool m_bDepressed;          ///< Is button currently being pressed?
            bool m_bToggle;             ///< Is this a toggling button, i.e. on or off.
            bool m_bToggleStatus;

            bool m_bCenterImage;        ///< Centre the image in the button?
        };


    }
}
#endif // ifndef GWK_CONTROLS_BUTTON_H
