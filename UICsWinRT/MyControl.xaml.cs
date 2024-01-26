using Microsoft.UI.Xaml.Controls;
using System.Diagnostics;

namespace UICsWinRT
{
    public sealed partial class MyUserControl : UserControl
    {
        public MyUserControl()
        {
            InitializeComponent();
            Unloaded += MyUserControl_Unloaded;
        }

        private void MyUserControl_Unloaded(object sender, Microsoft.UI.Xaml.RoutedEventArgs e)
        {
            Debug.WriteLine($"Unloaded {nameof(MyUserControl)}");
        }

        ~MyUserControl()
        {
            Debug.WriteLine($"~{nameof(MyUserControl)}");
        }
    }
}
