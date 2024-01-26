using Microsoft.UI.Xaml.Controls;
using System.Diagnostics;

namespace UICsWinRT
{
    public sealed partial class MyPage : Page
    {
        byte[] ByteArray { get; set; }

        public MyPage()
        {
            InitializeComponent();
            Unloaded += MyPage_Unloaded;

            // Reserve 10 MB
            ByteArray = new byte[1024 * 1024 * 10];
        }

        private void MyPage_Unloaded(object sender, Microsoft.UI.Xaml.RoutedEventArgs e)
        {
            Debug.WriteLine($"Unloaded {nameof(MyPage)}");
        }

        ~MyPage()
        {
            Debug.WriteLine($"~{nameof(MyPage)}");
        }
    }
}
