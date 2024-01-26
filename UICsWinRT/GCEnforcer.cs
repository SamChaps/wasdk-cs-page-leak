using Microsoft.UI.Xaml;
using System;

namespace UICsWinRT
{
    public sealed class GCEnforcer
    {
        private DispatcherTimer GcTimer { get; set; }

        public GCEnforcer()
        {
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
    }
}
