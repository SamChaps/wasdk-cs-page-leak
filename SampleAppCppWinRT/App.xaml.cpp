#include "pch.h"
#include "App.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;


namespace winrt::SampleAppCppWinRT::implementation
{
    App::App()
    {
#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
        UnhandledException([](IInspectable const&, UnhandledExceptionEventArgs const& e)
            {
                if (IsDebuggerPresent())
                {
                    auto errorMessage = e.Message();
                    __debugbreak();
                }
            });
#endif
    }

    Windows::Foundation::IAsyncAction App::OnLaunched([[maybe_unused]] LaunchActivatedEventArgs const& e)
    {
        if (m_launched)
        {
            co_return;
        }

        m_launched = true;

        m_mainWindow = Window();
        m_mainWindow.Title(L"MainWindow");
        m_mainWindow.Content(MainPage());
        m_mainWindow.Activate();
    }
}
