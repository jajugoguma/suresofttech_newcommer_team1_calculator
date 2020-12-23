using Prism.Ioc;
using Prism.Unity;
using System.Windows;
using Calculator.Views;
using Calculator.Infra.Service;
using System;
using System.IO;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace Calculator
{
    public partial class App : PrismApplication
    {
        protected override Window CreateShell()
        {
            AppDomain currentDomain = AppDomain.CurrentDomain;
            currentDomain.UnhandledException += new UnhandledExceptionEventHandler(UnHandlerEvent);
#if DEBUG_TEST
            return Container.Resolve<MainWindow>();
#elif DEBUG
            return Container.Resolve<CalculatorView>();
#else
            return Container.Resolve<CalculatorView>();
#endif


        }

        private void UnHandlerEvent(object sender, UnhandledExceptionEventArgs e)
        {


            string filePath = @"C:\temp";
            if (System.IO.Directory.Exists(filePath))
            {
            }
            else
            {
                System.IO.Directory.CreateDirectory(filePath);
            }


            string fileName = DateTime.Now.Ticks + ".dmp";

            string fileResult = Path.Combine(filePath, fileName);
            using (var stream = File.Create(fileResult))
            {
                var process = Process.GetCurrentProcess();
                MiniDumpWriteDump(
                    process.Handle,
                    process.Id,
                    stream.SafeFileHandle.DangerousGetHandle(),
                    MINIDUMP_TYPE.MiniDumpWithFullMemory,
                    IntPtr.Zero,
                    IntPtr.Zero,
                    IntPtr.Zero);
            }
            Process.GetCurrentProcess().Kill();
        }

        protected override void RegisterTypes(IContainerRegistry containerRegistry)
        {
            containerRegistry.RegisterSingleton<IRepository, Repository>();
        }

        #region dll
        public static class MINIDUMP_TYPE
        {
            public const int MiniDumpNormal = 0x00000000;
            public const int MiniDumpWithDataSegs = 0x00000001;
            public const int MiniDumpWithFullMemory = 0x00000002;
            public const int MiniDumpWithHandleData = 0x00000004;
            public const int MiniDumpFilterMemory = 0x00000008;
            public const int MiniDumpScanMemory = 0x00000010;
            public const int MiniDumpWithUnloadedModules = 0x00000020;
            public const int MiniDumpWithIndirectlyReferencedMemory = 0x00000040;
            public const int MiniDumpFilterModulePaths = 0x00000080;
            public const int MiniDumpWithProcessThreadData = 0x00000100;
            public const int MiniDumpWithPrivateReadWriteMemory = 0x00000200;
            public const int MiniDumpWithoutOptionalData = 0x00000400;
            public const int MiniDumpWithFullMemoryInfo = 0x00000800;
            public const int MiniDumpWithThreadInfo = 0x00001000;
            public const int MiniDumpWithCodeSegs = 0x00002000;
        }

        [DllImport("dbghelp.dll")]
        public static extern bool MiniDumpWriteDump(IntPtr hProcess,
        Int32 ProcessId,
        IntPtr hFile,
        int DumpType,
        IntPtr ExceptionParam,
        IntPtr UserStreamParam,
        IntPtr CallackParam);
        #endregion

    }
}
