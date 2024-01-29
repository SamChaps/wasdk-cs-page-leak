# wasdk-cs-views-leak
Windows App SDK sample apps demonstrating a leak when C# XAML pages are assigned and unassigned from Window.Content when Window was created on a new thread.

![image](https://github.com/SamChaps/wasdk-cs-page-leak/assets/16784153/e492c44b-28f8-4413-a72c-2efb7e531f84)

## Description
- We force garbage collection and finalizers to run to quickly hit C# objects finalizers.
- We expect C# XAML pages to get finalized once the Window.Content is set to null.
- When creating a Window on the main thread, this always happens quickly.
- When creating a Window on a new thread, this almost never happens for C# pages.
- However, C++/WinRT pages always destroyed even if the Window was created on a new thread.
