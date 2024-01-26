#include "pch.h"
#include "MyPageCppWinRT.h"
#if __has_include("MyPageCppWinRT.g.cpp")
#include "MyPageCppWinRT.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::UICppWinRT::implementation
{
    MyPageCppWinRT::MyPageCppWinRT()
    {
        m_byteArray = std::vector<uint8_t>(1024 * 1024 * 10);
        Unloaded({ get_weak(), &MyPageCppWinRT::MyPageCppWinRT_Unloaded });
    }

    MyPageCppWinRT::~MyPageCppWinRT()
    {
        OutputDebugStringW(L"~MyPageCppWinRT \n");
    }

    void MyPageCppWinRT::MyPageCppWinRT_Unloaded(Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        OutputDebugStringW(L"Unloaded MyPageCppWinRT \n");
    }
}
