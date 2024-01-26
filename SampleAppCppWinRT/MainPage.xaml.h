#pragma once

#include "MainPage.g.h"

#include <vector>
#include <map>

namespace winrt::SampleAppCppWinRT::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        Windows::Foundation::IAsyncAction CreateCsWindowOnNewThreadClicked(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        Windows::Foundation::IAsyncAction CreateCppWindowOnNewThreadClicked(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void CreateCsWindowOnMainThreadClicked(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

    private:
        void WindowClosed(IInspectable const& sender, Microsoft::UI::Xaml::WindowEventArgs const& e);

        Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Window> CreateNewCsWindowOnNewThread();
        Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Window> CreateNewCppWindowOnNewThread();
        Microsoft::UI::Xaml::Window CreateNewCsWindow();
        Microsoft::UI::Xaml::Window CreateNewCppWindow();

        winrt::UICsWinRT::GCEnforcer m_launcher{ nullptr };
        std::vector<Microsoft::UI::Xaml::Window> m_windows;
        std::vector<event_token> m_tokens;
    };
}

namespace winrt::SampleAppCppWinRT::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
