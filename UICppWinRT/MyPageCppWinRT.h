#pragma once

#include "MyPageCppWinRT.g.h"

#include <vector>

namespace winrt::UICppWinRT::implementation
{
    struct MyPageCppWinRT : MyPageCppWinRTT<MyPageCppWinRT>
    {
        MyPageCppWinRT();
        ~MyPageCppWinRT();

        void MyPageCppWinRT_Unloaded(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

    private:
        std::vector<uint8_t> m_byteArray;
    };
}

namespace winrt::UICppWinRT::factory_implementation
{
    struct MyPageCppWinRT : MyPageCppWinRTT<MyPageCppWinRT, implementation::MyPageCppWinRT>
    {
    };
}
