#pragma once

#include "App.xaml.g.h"
#include "winrt/UICsWinRT.h"

namespace winrt::SampleAppCppWinRT::implementation
{
    struct App : AppT<App>
    {
        App();

        Windows::Foundation::IAsyncAction OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

    private:
        winrt::Microsoft::UI::Xaml::Window m_mainWindow{ nullptr };
        bool m_launched{ false };
    };
}
