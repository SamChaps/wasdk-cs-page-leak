using Microsoft.UI.Xaml;
using System;
using System.Threading.Tasks;

namespace SampleApp
{
    public partial class App : Application
    {
        private bool Launched { get; set; }

        private DispatcherTimer GcTimer { get; set; }

        private Window MainWindow { get; set; }

        public App()
        {
            InitializeComponent();

            GcTimer = new DispatcherTimer();
            GcTimer.Tick += GcTimer_Tick;
            GcTimer.Interval = TimeSpan.FromSeconds(1);
            GcTimer.Start();
        }

        private void GcTimer_Tick(object sender, object e)
        {
            GC.Collect();
            GC.WaitForPendingFinalizers();
            GC.Collect();
        }

        protected override void OnLaunched(Microsoft.UI.Xaml.LaunchActivatedEventArgs args)
        {
            if (Launched)
            {
                return;
            }

            Launched = true;

            MainWindow = new Window();
            MainWindow.Title = "MainWindow";
            MainWindow.Content = new MainPage();
            MainWindow.Activate();
        }
    }
}
