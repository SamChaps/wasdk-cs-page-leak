#include "pch.h"
#include "MainPage.xaml.h"
#if __has_include("MainPage.g.cpp")
#include "MainPage.g.cpp"
#endif

#include <ppltasks.h>
#include <pplawait.h>
#include <winrt/Windows.Foundation.Collections.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::SampleAppCppWinRT::implementation
{
    MainPage::MainPage()
    {
        m_launcher = UICsWinRT::GCEnforcer();
    }

    Windows::Foundation::IAsyncAction MainPage::CreateCsWindowOnNewThreadClicked(Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        auto window = co_await CreateNewCsWindowOnNewThread();
        auto token = window.Closed({ this, &MainPage::WindowClosed });
        m_windows.push_back(window);
        m_tokens.push_back(token);
    }

    Windows::Foundation::IAsyncAction MainPage::CreateCppWindowOnNewThreadClicked(Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        auto window = co_await CreateNewCppWindowOnNewThread();
        auto token = window.Closed({ this, &MainPage::WindowClosed });
        m_windows.push_back(window);
        m_tokens.push_back(token);
    }

    void MainPage::CreateCsWindowOnMainThreadClicked(Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        auto window = CreateNewCsWindow();
        auto token = window.Closed({ this, &MainPage::WindowClosed });
        m_windows.push_back(window);
        m_tokens.push_back(token);
    }

    Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Window> MainPage::CreateNewCsWindowOnNewThread()
    {
        auto windowCreationEvent = concurrency::task_completion_event<Window>();
        auto task = concurrency::create_task(windowCreationEvent);

        auto thread = std::thread([=]()
            {
                winrt::init_apartment(winrt::apartment_type::single_threaded);

                Microsoft::UI::Xaml::Application::Start([=](auto&&)
                    {
                        auto window = CreateNewCsWindow();
                        windowCreationEvent.set(window);
                    });
            });

        thread.detach();

        auto window = co_await task;
        co_return window;
    }

    Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Window> MainPage::CreateNewCppWindowOnNewThread()
    {
        auto windowCreationEvent = concurrency::task_completion_event<Window>();
        auto task = concurrency::create_task(windowCreationEvent);

        auto thread = std::thread([=]()
            {
                winrt::init_apartment(winrt::apartment_type::single_threaded);

                Microsoft::UI::Xaml::Application::Start([=](auto&&)
                    {
                        auto window = CreateNewCppWindow();
                        windowCreationEvent.set(window);
                    });
            });

        thread.detach();

        auto window = co_await task;
        co_return window;
    }


    Microsoft::UI::Xaml::Window MainPage::CreateNewCsWindow()
    {
        auto window = Microsoft::UI::Xaml::Window();
        window.Title(L"SecondaryWindow");
        window.Content(UICsWinRT::MyPage());
        window.Activate();
        return window;
    }


    Microsoft::UI::Xaml::Window MainPage::CreateNewCppWindow()
    {
        auto window = Microsoft::UI::Xaml::Window();
        window.Title(L"SecondaryWindow");
        window.Content(UICppWinRT::MyPageCppWinRT());
        window.Activate();
        return window;
    }

    void MainPage::WindowClosed(IInspectable const& sender, WindowEventArgs const&)
    {
        auto window = sender.try_as<Microsoft::UI::Xaml::Window>();

        auto it = std::find(m_windows.begin(), m_windows.end(), window);
        size_t pos = std::distance(m_windows.begin(), it);
        m_windows.erase(it);
        auto token = m_tokens.at(pos);
        m_tokens.erase(m_tokens.begin() + pos);

        window.Content(nullptr);
        window.Closed(token);
    }
}
