using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using System.Threading.Tasks;
using System.Collections.Generic;
using System;
using System.Threading;
using System.Diagnostics;

using CSharp = UICsWinRT;
using CppWinRT = UICppWinRT;

namespace SampleApp
{
    public sealed partial class MainPage : Page
    {
        private List<Window> ActiveWindows { get; set; } = new List<Window>();

        public MainPage()
        {
            InitializeComponent();
        }

        private async void CreateCSWindowOnNewThreadClicked(object sender, RoutedEventArgs e)
        {
            await CreateWindowOnNewThreadThread<CSharp.MyPage>();
        }

        private async void CreateAndClose50CSWindowOnNewThreadClicked(object sender, RoutedEventArgs e)
        {
            await CreateAndClose50WindowOnNewThread<CSharp.MyPage>();
        }

        private async void CreateCppWindowOnNewThreadClicked(object sender, RoutedEventArgs e)
        {
            await CreateWindowOnNewThreadThread<CppWinRT.MyPageCppWinRT>();
        }

        private async void CreateAndClose50CppWindowOnNewThreadClicked(object sender, RoutedEventArgs e)
        {
            await CreateAndClose50WindowOnNewThread<CppWinRT.MyPageCppWinRT>();
        }

        private void CreateCSWindowOnMainThreadClicked(object sender, RoutedEventArgs e)
        {
            CreateWindowOnMainThread<CSharp.MyPage>();
        }

        private async void CreateAndClose50CSWindowOnMainThreadClicked(object sender, RoutedEventArgs e)
        {
            await CreateAndClose50WindowOnMainThread<CSharp.MyPage>();
        }

        private async Task CreateWindowOnNewThreadThread<T>() where T : Page, new()
        {
            var window = await CreateNewWindowOnNewThread<T>();
            ActiveWindows.Add(window);
            window.Closed += Window_Closed;
        }

        private async Task CreateAndClose50WindowOnNewThread<T>() where T : Page, new()
        {
            var windows = new List<Window>();

            for (int i = 0; i < 50; i++)
            {
                var window = await CreateNewWindowOnNewThread<T>();
                windows.Add(window);
                window.DispatcherQueue.ShutdownStarting += (sender, args) =>
                {
                    // This will run when the window is closed on the thread.  Xaml will still be running at this point.
                    // The app will need to have manually set window content to null on this thread and removed event handlers, etc
                    // to ensure we don't have memory leaks.
                    int threadId = Thread.CurrentThread.ManagedThreadId;
                    Debug.WriteLine($"==> {threadId} ShutdownStarting");

                    // After we get this deferral, the DispatcherQueue shutdown will not continue until we call Complete.
                    var deferral = args.GetDeferral();
                    var t = sender.CreateTimer();

                    // Give things a chance to wind down.
                    t.Interval = TimeSpan.FromSeconds(5);
                    t.Tick += (timer, obj) =>
                    {
                        t.Stop();
                        t = null;

                        GC.Collect();
                        GC.WaitForPendingFinalizers();

                        Debug.WriteLine($"==> {threadId} ShutdownStarting Done");
                        deferral.Complete();
                    };
                    t.Start();
                };
            }

            await Task.Delay(1000);

            foreach (var window in windows)
            {
                window.DispatcherQueue.TryEnqueue(() =>
                {
                    window.Content = null;
                    window.Close();
                });


            }

            windows.Clear();

        }

        private void CreateWindowOnMainThread<T>() where T : Page, new()
        {
            var window = CreateNewWindow<T>();
            ActiveWindows.Add(window);
            window.Closed += Window_Closed;        
        }

        private async Task CreateAndClose50WindowOnMainThread<T>() where T : Page, new()
        {
            var windows = new List<Window>();
            for (int i = 0; i < 50; i++)
            {
                var window = CreateNewWindow<T>();
                windows.Add(window);
            }

            await Task.Delay(1000);

            foreach (var window in windows)
            {
                window.DispatcherQueue.TryEnqueue(() =>
                {
                    window.Content = null;
                    window.Close();
                });
            }

            windows.Clear();
        }

        private async Task<Window> CreateNewWindowOnNewThread<T>() where T : Page, new()
        {
            var tcs = new TaskCompletionSource<Window>();
            var thread = new Thread(() =>
            {
                Debug.WriteLine($"Started with thread {Thread.CurrentThread.ManagedThreadId}.");

                App.Start((_) =>
                {
                    var window = CreateNewWindow<T>();
                    tcs.SetResult(window);
                });

                Debug.WriteLine($"Finished with thread {Thread.CurrentThread.ManagedThreadId}.");
            });

            thread.Start();

            return await tcs.Task;
        }

        private Window CreateNewWindow<T>() where T : Page, new()
        {
            var window = new Window();
            window.Title = "SecondaryWindow";
            window.Content = new T();
            window.Activate();
            return window;
        }

        private void Window_Closed(object sender, WindowEventArgs args)
        {
            var window = (Window)sender;
            ActiveWindows.Remove(window);
            window.Content = null;
            window.Closed -= Window_Closed;
        }
    }
}
